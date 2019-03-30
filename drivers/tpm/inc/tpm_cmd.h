#ifndef _TPM_CMD_H_
#define _TPM_CMD_H_

typedef void (*tpm_cmd_handler)(void *);

void tpm_cmd_unimplemented(void *buf);
void tpm_cmd_getcap(void *buf);

#endif	/* _TPM_CMD_H_ */
