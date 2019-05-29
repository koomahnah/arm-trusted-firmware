/*
 * Copyright (c) 2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <endian.h>

#include <arch_helpers.h>
#include <smccc_helpers.h>
#include <common/debug.h>
#include <drivers/tpm.h>
#include <drivers/auth/mbedtls/mbedtls_common.h>

#include "inc/tpm_priv.h"
#include "inc/tpm_crb.h"
#include "inc/tpm_cmd.h"
#include "inc/tpm_pcr.h"

static ptp_crb_registers *crb_regs = (ptp_crb_registers*) TPM_CRB_BASE;

static void
tpm_handle_cmd(void *buf) {
	tpm2_command_header *header = (tpm2_command_header *) buf;
	TPM_CC commandCode = be32toh(header->commandCode);

	INFO("TPM command_code: %x, %x\n", commandCode, commandCode - TPM_CC_FIRST);

	if (commandCode < TPM_CC_FIRST ||
	    commandCode > TPM_CC_LAST) {
		ERROR("TPM: Command code is incorrect.\n");
		tpm_cmd_unimplemented(buf);
	} else {
		tpm_command_table[commandCode - TPM_CC_FIRST].handler(buf);
	}

	/*
	 * Command has been processed, buf is assumed to contain a valid response.
	 * Set proper bits to inform client that we are done here.
	 */
	crb_regs->CrbControlStart = 0;

	INFO("TPM: Response size: %u\n", be32toh(header->paramSize));

	/* Dump response. */
	if (be32toh(header->paramSize) < 64) {
		INFO("TPM: Dumping response.\n");
		for (int i = 0; i < be32toh(header->paramSize); i++)
			printf("%02x", ((char*)buf)[i]);
		printf("\n");
	}
}

/* Define pointer types used to access CRB registers on PTP */
void init_tpm() {

	memset(crb_regs, 0, sizeof(crb_regs));
	memset(PCRS_SHA256_BANK, 0, sizeof(PCRS_SHA256_BANK));
	memset(PCRS_SHA1_BANK, 0, sizeof(PCRS_SHA1_BANK));

	crb_regs->CrbControlResponseSize = TPM_CRB_DATA_BUFFER_SIZE;
	crb_regs->CrbControlCommandSize = TPM_CRB_DATA_BUFFER_SIZE;
	crb_regs->CrbControlCommandAddress = (uint64_t) crb_regs->CrbDataBuffer;
	crb_regs->CrbControlResponseAddress = (uint64_t) crb_regs->CrbDataBuffer;


	/* 
	 * We don't really implement localities ATM.
	 * Just tell the client that they can get
	 * whatever locality they want instantly.
	 */
	crb_regs->LocalityStatus = 1;

	mbedtls_init();

}

uintptr_t tpm_smc_handler(void *handle) {
	
	tpm_handle_cmd(crb_regs->CrbDataBuffer);

	SMC_RET1(handle, SMC_OK);
}
