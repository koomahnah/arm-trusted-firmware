#include <string.h>
#include <common/debug.h> 
#include <endian.h>

#include "inc/tpm_priv.h"
#include "inc/tpm_getcap.h"
#include "inc/tpm_cmd.h"

void
tpm_cmd_getcap(void *buf) {
	tpm2_command_getcap *command = (tpm2_command_getcap *) buf;
	TPM_CAP capability;

	capability = be32toh(command->capability);

	INFO("TPM: GetCapability request.\n");

	INFO("Capability: %u, ", capability);
	INFO("Property: %u, propertyCount: %u\n", be32toh(command->property), be32toh(command->propertyCount));

	switch (capability) {
	case TPM_CAP_ALGS:
	case TPM_CAP_HANDLES:
	case TPM_CAP_COMMANDS:
	case TPM_CAP_PP_COMMANDS:
	case TPM_CAP_AUDIT_COMMANDS:
	case TPM_CAP_PCRS:
	case TPM_CAP_TPM_PROPERTIES:
	case TPM_CAP_PCR_PROPERTIES:
	case TPM_CAP_ECC_CURVES:
	case TPM_CAP_AUTH_POLICIES:
		tpm_cmd_unimplemented(buf);
		return;
	}
}
