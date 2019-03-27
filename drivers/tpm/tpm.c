#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

#include <arch_helpers.h>
#include <smccc_helpers.h>
#include <common/debug.h>
#include <drivers/tpm.h>

#include "tpm_priv.h"

/* Define pointer types used to access CRB registers on PTP */
void init_tpm() {
  ptp_crb_registers *crb_regs = (ptp_crb_registers *) 0x7ddf0000;
  printf("%s: entry\n", __func__);
  crb_regs->LocalityStatus = 1;
}

uintptr_t tpm_smc_handler(void *handle) {
  ptp_crb_registers *crb_regs = (ptp_crb_registers *) 0x7ddf0000;
	printf("%s: input buffer:\n", __func__);
	for (int i = 0; i < 0x100; i++) {
		printf("%02x ", crb_regs->CrbDataBuffer[i]);
		if (i % 16 == 15)
			printf("\n");
	}
	printf("\n");

	SMC_RET1(handle, SMC_OK);
}
