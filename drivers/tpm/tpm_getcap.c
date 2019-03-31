/*
 * Copyright (c) 2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>
#include <common/debug.h> 
#include <endian.h>

#include "inc/tpm_priv.h"
#include "inc/tpm_getcap.h"
#include "inc/tpm_cmd.h"

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
	case TPM_CAP_PP_COMMANDS:
	case TPM_CAP_AUDIT_COMMANDS:
		tpm_cmd_unimplemented(buf);
		break;
	case TPM_CAP_PCRS:
		tpm_getcap_pcrs(property, propertyCount, buf);
		break;
	case TPM_CAP_TPM_PROPERTIES:
	case TPM_CAP_PCR_PROPERTIES:
	case TPM_CAP_ECC_CURVES:
	case TPM_CAP_AUTH_POLICIES:
		tpm_cmd_unimplemented(buf);
		break;
	}
}
