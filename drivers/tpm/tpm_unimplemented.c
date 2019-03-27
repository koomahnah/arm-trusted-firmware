#include <string.h>
#include <common/debug.h> 

#include "inc/tpm_priv.h"
#include "inc/tpm_crb.h"
#include "inc/tpm_cmd.h"

void
tpm_cmd_unimplemented(void *buf) {
	tpm2_response_header *header;

	INFO("TPM: Request for an unimplemented command.\n");

	/* Purge buffer to make space for response. */
	memset (buf, 0, TPM_CRB_DATA_BUFFER_SIZE);

	header = (tpm2_response_header*) buf;

	header->tag = TPM_ST_NO_SESSIONS;
	header->paramSize = sizeof(tpm2_response_header);
	header->responseCode = TPM_RC_COMMAND_CODE;
}
