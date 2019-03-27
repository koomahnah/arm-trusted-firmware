#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

#include <arch_helpers.h>
#include <smccc_helpers.h>
#include <common/debug.h>
#include <drivers/tpm.h>

#include "inc/tpm_priv.h"
#include "inc/tpm_crb.h"
#include "inc/tpm_cmd_table.h" 

static ptp_crb_registers *crb_regs = (ptp_crb_registers*) TPM_CRB_BASE;

static void
tpm_handle_cmd(void *buf) {
	tpm2_command_header *header = (tpm2_command_header *) buf;

	if (header->commandCode < TPM_CC_FIRST ||
	    header->commandCode > TPM_CC_LAST) {
		INFO("TPM: Command code is incorrect.\n");
		tpm_cmd_unimplemented(buf);
	} else {
		tpm_command_table[header->commandCode - TPM_CC_FIRST].handler(buf);
	}

	/*
	 * Command has been processed, buf is assumed to contain a valid response.
	 * Set proper bits to inform client that we are done here.
	 */
	crb_regs->CrbControlStart = 0;
}

/* Define pointer types used to access CRB registers on PTP */
void init_tpm() {

	memset(crb_regs, 0, sizeof(crb_regs));

	crb_regs->CrbControlCommandSize = TPM_CRB_DATA_BUFFER_SIZE;

	/* 
	 * We don't really implement localities ATM.
	 * Just tell the client that they can get
	 * whatever locality they want instantly.
	 */
	crb_regs->LocalityStatus = 1;
}

uintptr_t tpm_smc_handler(void *handle) {
	
	tpm_handle_cmd(crb_regs->CrbDataBuffer);

	SMC_RET1(handle, SMC_OK);
}
