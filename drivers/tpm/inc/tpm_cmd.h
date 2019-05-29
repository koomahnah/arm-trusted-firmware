/*
 * Copyright (c) 2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _TPM_CMD_H_
#define _TPM_CMD_H_

#include "TPM_Types.h"

typedef void (*tpm_cmd_handler)(void *);

void tpm_cmd_unimplemented(void *buf);
void tpm_cmd_getcap(void *buf);
void tpm_cmd_pcr_extend(void *buf);
void tpm_cmd_pcr_read(void *buf);
void tpm_cmd_self_test(void *buf);

struct tpm_command {
	tpm_cmd_handler handler;
	/*
	 * Indicates whether this command
	 * can be executed in single smc call.
	 */
	int long_cmd;
	TPMA_CC attributes;
};

extern const struct tpm_command tpm_command_table[];
extern const int tpm_cmd_count;


#endif	/* _TPM_CMD_H_ */
