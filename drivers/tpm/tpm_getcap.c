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
			sizeof(TPMI_ALG_HASH) + 
			sizeof(UINT8) +
			3 * sizeof(BYTE));
	response->header.responseCode = htobe32(TPM_RC_SUCCESS);

	response->moreData = FALSE;
	response->capabilityData.capability = htobe32(TPM_CAP_PCRS);
	pcrs->count = htobe32(1);
	pcrs->pcrSelections[0].hash = htobe16(TPM_ALG_SHA256);
	pcrs->pcrSelections[0].sizeofSelect = 3;
	pcrs->pcrSelections[0].pcrSelect[0] = 0xff;
	pcrs->pcrSelections[0].pcrSelect[1] = 0xff;
	pcrs->pcrSelections[0].pcrSelect[2] = 0xff;

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
