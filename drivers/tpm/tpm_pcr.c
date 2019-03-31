/*
 * Copyright (c) 2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <endian.h>
#include <string.h>
#include <common/debug.h>

#include <mbedtls/md.h>
#include <mbedtls/oid.h>
#include <mbedtls/platform.h>

#include "inc/tpm_pcr.h"
#include "inc/tpm_cmd.h"

TPM_PCR_SHA256_BANK PCRS_SHA256_BANK[IMPLEMENTATION_PCR];
TPM_PCR_SHA1_BANK   PCRS_SHA1_BANK[IMPLEMENTATION_PCR];
static uint32_t pcrUpdateCounter = 0;

/* 
 * Process PCR selection.
 * If selection is incorrect the command will fail
 * with the response code returned from this function.
 */
static TPM_RC
tpm_pcr_read_bank(TPMS_PCR_SELECTION *selection, TPM2B_DIGEST *response, uint32_t *response_size, uint32_t *digest_count) {
	TPM_ALG_ID hash;

	hash = be16toh(selection->hash);

	/* Validate input. */
	if (hash != TPM_ALG_SHA256 && hash != TPM_ALG_SHA1)
		return TPM_RC_HASH;

	/* We only support 24 PCRs. */
	if (selection->sizeofSelect > 3)
		return TPM_RC_VALUE;

	response_size = 0;

	for (uint8_t i = 0; i < selection->sizeofSelect; i++) {
		uint8_t pcr_mask = selection->pcrSelect[i];

		for (uint8_t j = 0; j < 8; j++)
			if ((pcr_mask & (1 << j)) == 1) {
				if (hash == TPM_ALG_SHA256) {
					response->t.size = htobe16(SHA256_DIGEST_SIZE);
					memcpy(response->t.buffer, PCRS_SHA256_BANK[8*i + j], SHA256_DIGEST_SIZE);
					response = (TPM2B_DIGEST*)(((uint8_t*)response) + sizeof(uint16_t) + SHA256_DIGEST_SIZE);
					(*response_size) += sizeof(uint16_t) + SHA256_DIGEST_SIZE;
					(*digest_count)++;
				} else {
					response->t.size = htobe16(SHA1_DIGEST_SIZE);
					memcpy(response->t.buffer, PCRS_SHA1_BANK[8*i + j], SHA1_DIGEST_SIZE);
					response = (TPM2B_DIGEST*)(((uint8_t*)response) + sizeof(uint16_t) + SHA1_DIGEST_SIZE);
					(*response_size) += sizeof(uint16_t) + SHA1_DIGEST_SIZE;
					(*digest_count)++;
				}
			}
	}

	return TPM_RC_SUCCESS;
}

void
tpm_cmd_pcr_read(void *buf) {
	tpm2_response_pcr_read *resp = (tpm2_response_pcr_read*)buf;
	uint8_t *raw_command = (uint8_t*)buf;
	uint32_t *digest_count;
	uint32_t response_size;
	TPMS_PCR_SELECTION *selection;
	TPM_RC rc;

	/* 
	 * Move the pcrSelection structure 4 bytes forward.
	 * The pcrUpdateCounter needs to be put in before pcrSelection in response.
	 * TODO: If there is not enough space to do entire request, we will simply trim it later.
	 */
	memmove(buf + sizeof(tpm2_command_header) + sizeof(uint32_t),
		buf + sizeof(tpm2_command_header),
		resp->header.commandSize - sizeof(tpm2_command_header));
	resp->pcrUpdateCounter = htobe32(pcrUpdateCounter);

	/* 
	 * Move pointer to where the hash will be put.
	 * Reserve 4 bytes for the count of returned digests.
	 */
	raw_command += resp->header.commandSize + sizeof(uint32_t);
	digest_count = (uint32_t*)raw_command;
	raw_command += sizeof(uint32_t);
	selection = &resp->pcrSelection.pcrSelections[0];
	response_size = 0;
	resp->header.responseSize = htobe32(be32toh(resp->header.responseSize) + 2*sizeof(uint32_t));

	for (uint32_t i = 0; i < resp->pcrSelection.count; i++) {
		rc = tpm_pcr_read_bank(selection, (TPM2B_DIGEST*)raw_command, &response_size, digest_count);
		if (rc != TPM_RC_SUCCESS)
			goto fail;

		raw_command += response_size;
		resp->header.responseSize = htobe32(be32toh(resp->header.responseSize) + response_size);
		selection = (TPMS_PCR_SELECTION*)(((uint8_t*)selection) +
				sizeof(TPMI_ALG_HASH) +
				sizeof(uint8_t) +
				selection->sizeofSelect * sizeof(uint8_t)
				);
	}

	*digest_count = htobe32(*digest_count);

	resp->header.tag = htobe16(TPM_ST_NO_SESSIONS);
	resp->header.responseCode = htobe32(TPM_RC_SUCCESS);
	return;
fail:
	resp->header.tag = htobe16(TPM_ST_NO_SESSIONS);
	resp->header.responseSize = htobe32(sizeof(tpm2_command_header));
	resp->header.responseCode = htobe32(rc);
}

void
tpm_pcr_extend_bank(TPM_ALG_ID digest_id, void *data, TPMI_DH_PCR handle) {
	mbedtls_md_context_t ctx;

	mbedtls_md_init(&ctx);

	if (digest_id == TPM_ALG_SHA256) {
		mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(MBEDTLS_MD_SHA256), 0);
		mbedtls_md_starts(&ctx);
		mbedtls_md_update(&ctx, PCRS_SHA256_BANK[handle], SHA256_DIGEST_SIZE);
		mbedtls_md_update(&ctx, data, SHA256_DIGEST_SIZE);
		mbedtls_md_finish(&ctx, PCRS_SHA256_BANK[handle]);
	} else {
		mbedtls_md_starts(&ctx);
		mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(MBEDTLS_MD_SHA1), 0);
		mbedtls_md_update(&ctx, PCRS_SHA1_BANK[handle], SHA1_DIGEST_SIZE);
		mbedtls_md_update(&ctx, data, SHA1_DIGEST_SIZE);
		mbedtls_md_finish(&ctx, PCRS_SHA1_BANK[handle]);
	}

}

void
tpm_cmd_pcr_extend(void *buf) {
	tpm2_command_pcr_extend *cmd = (tpm2_command_pcr_extend*)buf;
	TPML_DIGEST_VALUES *digestList;
	TPMT_HA *digest;
	TPM_ALG_ID digest_id;
	uint32_t op_count;
	TPMI_DH_PCR pcrHandle;

	pcrHandle = be32toh(cmd->pcrHandle);
	digestList = (TPML_DIGEST_VALUES*)(((uint8_t*)buf) +
		sizeof(tpm2_command_header) +
		sizeof(TPMI_DH_PCR) +
		sizeof(uint32_t) +
		be32toh(cmd->AuthorizationSize));
	op_count = be32toh(digestList->count);

	INFO("TPM: extend_pcr op_count: %x, pcrHandle: %x\n", op_count, pcrHandle);

	/* 
	 * Validate input parameters.
	 * We only support SHA256.
	 */
	digest = &digestList->digests[0];
	for (uint32_t i = 0; i < op_count; i++) {
		digest_id = be16toh(digest->hashAlg);
		if (digest_id != TPM_ALG_SHA256 &&
		    digest_id != TPM_ALG_SHA1) {
			INFO("TPM: unsupported Hash algorithm: 0x%x\n", be16toh(digest->hashAlg));
			cmd->header.responseCode = htobe32(TPM_RC_HASH);
			goto end;
		}
		if (digest_id == TPM_ALG_SHA256)
			digest = (TPMT_HA*)(((uint8_t*)digest) + sizeof(TPM_ALG_ID) + SHA256_DIGEST_SIZE);
		else
			digest = (TPMT_HA*)(((uint8_t*)digest) + sizeof(TPM_ALG_ID) + SHA1_DIGEST_SIZE);
	}

	/* 
	 * Invalid PCR handle.
	 * XXX: Chack expected RC with standard.
	 */
	if (pcrHandle >= IMPLEMENTATION_PCR) {
		cmd->header.responseCode = htobe32(TPM_RC_VALUE);
		goto end;
	}
	
	cmd->header.responseCode = htobe32(TPM_RC_SUCCESS);

	/* Do nothing if no handle was specified */
	if (pcrHandle == TPM_RH_NULL)
		goto end;

	digest = &digestList->digests[0];
	for (uint32_t i = 0; i < op_count; i++) {
		digest_id = be16toh(digest->hashAlg);

		tpm_pcr_extend_bank(digest_id, &digest->digest, pcrHandle); 

		if (digest_id == TPM_ALG_SHA256)
			digest = (TPMT_HA*)(((uint8_t*)digest) + sizeof(TPM_ALG_ID) + SHA256_DIGEST_SIZE);
		else
			digest = (TPMT_HA*)(((uint8_t*)digest) + sizeof(TPM_ALG_ID) + SHA1_DIGEST_SIZE);
	}

	pcrUpdateCounter++;

end:
	cmd->header.tag = htobe16(TPM_ST_NO_SESSIONS);
	cmd->header.responseSize = htobe32(sizeof(tpm2_command_header));
}
