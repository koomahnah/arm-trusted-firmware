#ifndef _TPM_STRUCTURES_H_
#define _TPM_STRUCTURES_H_

#include <stdint.h>

#pragma pack (1)

typedef struct {
  TPM_ST tag;
  uint32_t paramSize;
  union {
  TPM_CC commandCode;
  TPM_RC responseCode;
  };
} tpm2_command_header;

#pragma pack()

#endif	/* _TPM_STRUCTURES_H_ */
