/*
 * Copyright (c) 2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _TPM_CMD_H_
#define _TPM_CMD_H_

typedef void (*tpm_cmd_handler)(void *);

void tpm_cmd_unimplemented(void *buf);
void tpm_cmd_getcap(void *buf);
void tpm_cmd_pcr_extend(void *buf);

#endif	/* _TPM_CMD_H_ */
