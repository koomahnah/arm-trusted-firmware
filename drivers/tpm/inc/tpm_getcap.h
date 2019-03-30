#ifndef _TPM_GETCAP_H
#define _TPM_GETCAP_H

#include "tpm_priv.h"

#pragma pack (1)

typedef struct {
	tpm2_command_header header;
	TPM_CAP  capability;
	uint32_t property;
	uint32_t propertyCount;
} tpm2_command_getcap;

#endif	/* _TPM_GETCAP_H */
