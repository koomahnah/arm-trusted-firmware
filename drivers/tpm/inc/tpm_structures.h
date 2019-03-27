#ifndef _TPM_STRUCTURES_H_
#define _TPM_STRUCTURES_H_

#include <stdint.h>

#pragma pack (1)

typedef struct {
  uint16_t tag;
  uint32_t paramSize;
  uint32_t commandCode;
} tpm2_command_header;

typedef struct {
  uint16_t tag;
  uint32_t paramSize;
  uint32_t responseCode;
} tpm2_response_header;

#pragma pack()

/* Command is not implemented */
#define TPM_RC_COMMAND_CODE 0x143

#define TPM_ST_NO_SESSIONS 0x8001

#endif	/* _TPM_STRUCTURES_H_ */
