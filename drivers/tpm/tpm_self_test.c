#include <string.h>
#include <common/debug.h> 
#include <endian.h>

#include "inc/tpm_priv.h"
#include "inc/tpm_cmd.h"

void
tpm_cmd_self_test(void *buf) {
	tpm2_command_header *rsp = (tpm2_command_header *) buf;

	INFO("TPM: SelfTest request.\n");

	rsp->responseCode = htobe32(TPM_RC_SUCCESS);
	rsp->responseSize = htobe32(sizeof(tpm2_command_header));
}
