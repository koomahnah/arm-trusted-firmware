/*
 * Copyright (c) 2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>
#include <common/debug.h> 
#include <endian.h>
#include <assert.h>

#include "inc/tpm_priv.h"
#include "inc/tpm_getcap.h"
#include "inc/tpm_cmd.h"

static int
tpm_count_implemented()
{
#if 0
	int i, sum = 0;


	for (i = 0; i < tpm_cmd_count; i++)
		if (tpm_command_table[i].handler != tpm_cmd_unimplemented)
			sum++;

	return sum;
#endif
	return 0x5b;
}

static void
tpm_getcap_commands(uint32_t property, uint32_t propertyCount,
    tpm2_getcap_response *response)
{
	response->header.tag = htobe16(TPM_ST_NO_SESSIONS);
	int i, rsp_idx;

	INFO("TPM: GetCapability commands request\n");

#if 0
	if (propertyCount != tpm_count_implemented() || 1) {
		response->header.paramSize = htobe32(sizeof(tpm2_command_header));
		response->header.responseCode = htobe32(TPM_RC_COMMAND_CODE);
		return;
	}
#endif

	response->capabilityData.capability = htobe32(TPM_CAP_COMMANDS);
	response->capabilityData.data.command.count = htobe32(propertyCount);
	response->moreData = (property + propertyCount < tpm_cmd_count);

	property -= TPM_CC_FIRST;

	for (rsp_idx = 0, i = property; i < tpm_cmd_count && rsp_idx < propertyCount; i++)
		response->capabilityData.data.command.commandAttributes[rsp_idx++] =
			tpm_command_table[i].attributes;

	INFO("RSP_IDX: %d\n", rsp_idx);
	response->capabilityData.data.command.count = htobe32(rsp_idx);

	response->header.paramSize = htobe32(
			sizeof(tpm2_command_header) +
			sizeof(TPMI_YES_NO) +
			sizeof(TPM_CAP) +
			sizeof(UINT32) + //command.count
			rsp_idx * sizeof(TPMA_CC)); //command.commandAttributes
	response->header.responseCode = htobe32(TPM_RC_SUCCESS);
}

static void
tpm_getcap_properties(uint32_t property, uint32_t propertyCount,
    tpm2_getcap_response *response)
{

	response->header.tag = htobe16(TPM_ST_NO_SESSIONS);
	response->capabilityData.capability = htobe32(TPM_CAP_TPM_PROPERTIES);
	response->capabilityData.data.tpmProperties.count = htobe32(1);
	response->moreData = 0;

	INFO("TPM: GetCapability properties request\n");

	switch (property) {
	case TPM_PT_TOTAL_COMMANDS:
		response->capabilityData.data.tpmProperties.tpmProperty[0].property =
			htobe32(TPM_PT_TOTAL_COMMANDS);
		response->capabilityData.data.tpmProperties.tpmProperty[0].value =
			htobe32(tpm_count_implemented());
		break;
	default:
		response->header.paramSize = htobe32(sizeof(tpm2_command_header));
		response->header.responseCode = htobe32(TPM_RC_COMMAND_CODE);
		return;
	}

	response->header.paramSize = htobe32(
			sizeof(tpm2_command_header) +
			sizeof(TPMI_YES_NO) +
			sizeof(TPM_CAP) +
			sizeof(UINT32) +
			sizeof(TPMS_TAGGED_PROPERTY));
	response->header.responseCode = htobe32(TPM_RC_SUCCESS);

}

/*
 * Return PCRs description including supported hash algorithm.
 * Currently we support 24 PCRS with SHA256 only.
 */
static void
tpm_getcap_pcrs(uint32_t property, uint32_t propertyCount, tpm2_getcap_response *response) {
	TPML_PCR_SELECTION *pcrs = &response->capabilityData.data.assignedPCR;
	TPMS_PCR_SELECTION *selection;
	int count = sizeof(PCR_SUPPORTED_HASHES) / sizeof(TPM_ALG_ID);
	int selection_size = sizeof(TPMI_ALG_HASH) + sizeof(uint8_t) + 3 * sizeof(BYTE);
	

	response->header.tag = htobe16(TPM_ST_NO_SESSIONS);
	if (property != 0) {
		response->header.paramSize = htobe32(sizeof(tpm2_command_header)); 
		response->header.responseCode = htobe32(TPM_RC_VALUE);
		return;
	}

	response->header.paramSize = htobe32(
			sizeof(tpm2_command_header) +
			sizeof(TPMI_YES_NO) +
			sizeof(TPM_CAP) + 
			sizeof(UINT32) +
			count * selection_size);
	response->header.responseCode = htobe32(TPM_RC_SUCCESS);

	response->moreData = FALSE;
	response->capabilityData.capability = htobe32(TPM_CAP_PCRS);
	pcrs->count = htobe32(count);

	selection = &pcrs->pcrSelections[0];

	/* For each algorithm we support 24 PCRS. */
	while (count--) {
		selection->hash = htobe16(PCR_SUPPORTED_HASHES[count]);
		selection->sizeofSelect = 3;
		selection->pcrSelect[0] = 0xff;
		selection->pcrSelect[1] = 0xff;
		selection->pcrSelect[2] = 0xff;
		selection = (TPMS_PCR_SELECTION*)(((uint8_t*)selection) + selection_size);
	}
}

void
tpm_cmd_getcap(void *buf) {
	tpm2_command_getcap *command = (tpm2_command_getcap *) buf;
	TPM_CAP capability;
	uint32_t property, propertyCount;

	capability = be32toh(command->capability);
	property = be32toh(command->property);
	propertyCount = be32toh(command->propertyCount);

	memset(buf, 0, sizeof(tpm2_command_getcap));

	INFO("TPM: GetCapability request.\n");

	INFO("Capability: %u, ", capability);
	INFO("Property: %u, propertyCount: %u\n", property, propertyCount);

	switch (capability) {
	case TPM_CAP_ALGS:
	case TPM_CAP_HANDLES:
	case TPM_CAP_COMMANDS:
		tpm_getcap_commands(property, propertyCount, buf);
		break;
	case TPM_CAP_PP_COMMANDS:
	case TPM_CAP_AUDIT_COMMANDS:
		tpm_cmd_unimplemented(buf);
		break;
	case TPM_CAP_PCRS:
		tpm_getcap_pcrs(property, propertyCount, buf);
		break;
	case TPM_CAP_TPM_PROPERTIES:
		tpm_getcap_properties(property, propertyCount, buf);
		break;
	case TPM_CAP_PCR_PROPERTIES:
	case TPM_CAP_ECC_CURVES:
	case TPM_CAP_AUTH_POLICIES:
		tpm_cmd_unimplemented(buf);
		break;
	}
}
