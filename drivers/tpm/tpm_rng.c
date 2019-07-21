/*
 *
 * Copyright (c) 2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <endian.h>
#include <string.h>
#include <common/debug.h>

#include <mbedtls/platform.h>
#include <mbedtls/entropy.h>
#include <mbedtls/ctr_drbg.h>

#include "inc/tpm_rng.h"
#include "inc/tpm_cmd.h"

static bool initialized = false;

static mbedtls_ctr_drbg_context rng_ctx;
static mbedtls_entropy_context entropy_ctx;

int
tpm_rng_init() {
	int rc;
	const char *seed = "BAD IDEA";

	mbedtls_ctr_drbg_init(&rng_ctx);
	mbedtls_entropy_init(&entropy_ctx);

	rc = mbedtls_ctr_drbg_seed(&rng_ctx, mbedtls_entropy_func, &entropy_ctx, (const unsigned char*)seed, strlen(seed));
	if (rc != 0)
		INFO("Failed to initialize RNG: %d\n", rc);
	
	return (rc);
}

void
tpm_cmd_getrandom(void* buf) {
	tpm2_command_get_random *cmd = (tpm2_command_get_random*)buf;
	size_t size = 0;
	int rc;

	if (!initialized) {
		if (tpm_rng_init() != 0) {
			cmd->header.responseCode = htobe32(TPM_RC_FAILURE);
			goto end;
		}
		initialized = true;
	}

	size = be16toh(cmd->bytesRequested);
	if (size == 0) {
		INFO("%s: empty request\n", __func__);
		cmd->header.responseCode = htobe32(TPM_RC_VALUE);
		goto end;
	}

	rc = mbedtls_ctr_drbg_random(&rng_ctx, cmd->bytes.b.buffer, size);
	if (rc != 0) {
		size = 0;
		INFO("RNG failed with %d\n", rc);
		cmd->header.responseCode = htobe32(TPM_RC_FAILURE);
		goto end;
	}
	cmd->header.responseCode = htobe32(TPM_RC_SUCCESS);
	cmd->bytes.b.size = htobe16(size);
	/* Byte array size. */
	size += sizeof(uint16_t);
	
end:
	cmd->header.tag = htobe16(TPM_ST_NO_SESSIONS);
	cmd->header.responseSize = htobe32(sizeof(tpm2_command_header) + size);
}

void
tpm_cmd_stirrandom(void* buf) {
	tpm2_command_stir_random *cmd = (tpm2_command_stir_random*)buf;
	int rc = 0;

	if (!initialized) {
		if (tpm_rng_init() != 0) {
			cmd->header.responseCode = htobe32(TPM_RC_FAILURE);
			goto end;
		}
		initialized = true;
	}

	rc = mbedtls_ctr_drbg_reseed(&rng_ctx, cmd->bytes.buffer, be16toh(cmd->bytes.size));
	if (rc != 0) {
		cmd->header.responseCode = htobe32(TPM_RC_FAILURE);
		INFO("Reseed failed with: %d\n", rc);
	}

	cmd->header.responseCode = htobe32(TPM_RC_SUCCESS);

end:
	cmd->header.tag = htobe16(TPM_ST_NO_SESSIONS);
	cmd->header.responseSize = htobe32(sizeof(tpm2_command_header));
}
