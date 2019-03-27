#ifndef _TPM_H_
#define _TPM_H_

#define TPM_FID 0x8400eded

#define is_tpm_fid(_fid) ((_fid) == TPM_FID)

uintptr_t tpm_smc_handler(void *handle);
void init_tpm();

#endif
