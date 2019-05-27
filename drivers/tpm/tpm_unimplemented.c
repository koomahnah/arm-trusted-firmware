/*
 * Copyright (c) 2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>
#include <common/debug.h> 
#include <endian.h>

#include "inc/tpm_priv.h"
#include "inc/tpm_crb.h"
#include "inc/tpm_cmd.h"

void
tpm_cmd_unimplemented(void *buf) {
	tpm2_command_header *header = (tpm2_command_header *) buf;
	TPM_CC commandCode = be32toh(header->commandCode);

	ERROR("TPM: Request for an unimplemented command 0x%x.\n", commandCode);

	/* Purge buffer to make space for response. */
	memset (buf, 0, TPM_CRB_DATA_BUFFER_SIZE);

	header->tag = htobe16(TPM_ST_NO_SESSIONS);
	header->paramSize = htobe32(sizeof(tpm2_command_header));
	header->responseCode = htobe32(TPM_RC_COMMAND_CODE);
}
