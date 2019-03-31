/*
 * Copyright (c) 2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _TPM_STRUCTURES_H_
#define _TPM_STRUCTURES_H_

#include <stdint.h>
#include "TPM_Types.h"

#pragma pack (1)

typedef struct {
  TPM_ST tag;
  union {
  uint32_t paramSize;
  uint32_t commandSize;
  uint32_t responseSize;
  };
  union {
  TPM_CC commandCode;
  TPM_RC responseCode;
  };
} tpm2_command_header;

#pragma pack()

#endif	/* _TPM_STRUCTURES_H_ */
