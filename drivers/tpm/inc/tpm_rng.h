/*
 *
 * Copyright (c) 2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _TPM_RNG_H
#define _TPM_RNG_H

#include "Implementation.h"
#include "tpm_structures.h"

/* Internal function used to get random values. */
int tpm_get_rng(void* buf, size_t len);

#pragma pack (1)

typedef struct {
	tpm2_command_header header;
	union {
	UINT16 bytesRequested;
	TPM2B_DIGEST bytes;
	};
} tpm2_command_get_random;

typedef struct {
	tpm2_command_header header;
	TPM2B bytes;
} tpm2_command_stir_random;

#pragma pack (0)

#endif /* _TPM_RNG_H */
