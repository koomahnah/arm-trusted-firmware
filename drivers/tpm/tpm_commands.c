/*
 * Copyright (c) 2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "inc/tpm_cmd.h"
#include <utils_def.h>

#define TPM_CC_ATTR_UNIMPLEMENTED 0

const struct tpm_command tpm_command_table[] = {
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_NV_UndefineSpaceSpecial */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_EvictControl */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_HierarchyControl */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_NV_UndefineSpace */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* UNUSED */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_ChangeEPS */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_ChangePPS */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_Clear */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_ClearControl */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_ClockSet */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_HierarchyChangeAuth */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_NV_DefineSpace */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PCR_Allocate */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PCR_SetAuthPolicy */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PP_Commands */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_SetPrimaryPolicy */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_FieldUpgradeStart */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_ClockRateAdjust */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_CreatePrimary */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_NV_GlobalWriteLock */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_GetCommandAuditDigest */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_NV_Increment */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_NV_SetBits */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_NV_Extend */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_NV_Write */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_NV_WriteLock */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_DictionaryAttackLockReset */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_DictionaryAttackParameters */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_NV_ChangeAuth */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PCR_Event */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PCR_Reset */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_SequenceComplete */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_SetAlgorithmSet */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_SetCommandCodeAuditStatus */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_FieldUpgradeData */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_IncrementalSelfTest */
	{tpm_cmd_self_test, 0, {.val = TPM_CC_SelfTest}},	/* TPM_CC_SelfTest */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_Startup */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_Shutdown */
	{tpm_cmd_stirrandom, 0, {.val = TPM_CC_StirRandom}},	/* TPM_CC_StirRandom */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_ActivateCredential */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_Certify */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PolicyNV */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_CertifyCreation */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_Duplicate */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_GetTime */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_GetSessionAuditDigest */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_NV_Read */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_NV_ReadLock */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_ObjectChangeAuth */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PolicySecret */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_Rewrap */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_Create */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_ECDH_ZGen */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_HMAC */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_Import */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_Load */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_Quote */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_RSA_Decrypt */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* UNUSED */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_HMAC_Start */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_SequenceUpdate */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_Sign */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_Unseal */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* UNUSED */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PolicySigned */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_ContextLoad */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_ContextSave */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_ECDH_KeyGen */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_EncryptDecrypt */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_FlushContext */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* UNUSED */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_LoadExternal */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_MakeCredential */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_NV_ReadPublic */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PolicyAuthorize */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PolicyAuthValue */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PolicyCommandCode */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PolicyCounterTimer */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PolicyCpHash */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PolicyLocality */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PolicyNameHash */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PolicyOR */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PolicyTicket */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_ReadPublic */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_RSA_Encrypt */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* UNUSED */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_StartAuthSession */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_VerifySignature */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_ECC_Parameters */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_FirmwareRead */
	{tpm_cmd_getcap, 0, {.val = TPM_CC_GetCapability}},		/* TPM_CC_GetCapability */
	{tpm_cmd_getrandom, 0, {.val = TPM_CC_GetRandom}},	/* TPM_CC_GetRandom */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_GetTestResult */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_Hash */
	{tpm_cmd_pcr_read, 0, {.val = TPM_CC_PCR_Read}},	/* TPM_CC_PCR_Read */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PolicyPCR */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PolicyRestart */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_ReadClock */
	{tpm_cmd_pcr_extend, 0, {.val = TPM_CC_PCR_Extend}},	/* TPM_CC_PCR_Extend */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PCR_SetAuthValue */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_NV_Certify */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_EventSequenceComplete */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_HashSequenceStart */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PolicyPhysicalPresence */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PolicyDuplicationSelect */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PolicyGetDigest */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_TestParms */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_Commit */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PolicyPassword */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_ZGen_2Phase */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_EC_Ephemeral */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PolicyNvWritten */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PolicyTemplate */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_CreateLoaded */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_PolicyAuthorizeNV */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_EncryptDecrypt2 */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_AC_GetCapability */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}},	/* TPM_CC_AC_Send */
	{tpm_cmd_unimplemented, 0, {.val = TPM_CC_ATTR_UNIMPLEMENTED}}	/* TPM_CC_Policy_AC_SendSelect */
};

const int tpm_cmd_count = ARRAY_SIZE(tpm_command_table);
