/*
 * Copyright (c) 2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _TPM_PCR_H
#define _TPM_PCR_H

#include "Implementation.h"
#include "tpm_structures.h"

typedef uint8_t TPM_PCR_SHA256_BANK[SHA256_DIGEST_SIZE];
typedef uint8_t TPM_PCR_SHA1_BANK[SHA1_DIGEST_SIZE];

extern TPM_PCR_SHA256_BANK PCRS_SHA256_BANK[IMPLEMENTATION_PCR];
extern TPM_PCR_SHA1_BANK PCRS_SHA1_BANK[IMPLEMENTATION_PCR];

#pragma pack (1)

typedef struct {
	tpm2_command_header header;
	TPMI_DH_PCR pcrHandle;
	uint32_t AuthorizationSize;
	TPMS_AUTH_COMMAND AuthSessionPcr;
	TPML_DIGEST_VALUES digests;
} tpm2_command_pcr_extend;

typedef struct {
	tpm2_command_header header;
	uint32_t pcrUpdateCounter;
	TPML_PCR_SELECTION pcrSelection;
} tpm2_response_pcr_read;

#pragma pack (0)

#endif	/* _TPM_PCR_H */
