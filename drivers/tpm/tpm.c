#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

#include <arch_helpers.h>
#include <common/debug.h>
#pragma pack (1)

//
// Register set map as specified in PTP specification Chapter 5
//
typedef struct {
  ///
  /// Used to determine current state of Locality of the TPM.
  ///
  uint32_t                            LocalityState;             // 0
  uint8_t                             Reserved1[4];              // 4
  ///
  /// Used to gain control of the TPM by this Locality.
  ///
  uint32_t                            LocalityControl;           // 8
  ///
  /// Used to determine whether Locality has been granted or Seized.
  ///
  uint32_t                            LocalityStatus;            // 0ch
  uint8_t                             Reserved2[0x20];           // 10h
  ///
  /// Used to identify the Interface types supported by the TPM.
  ///
  uint32_t                            InterfaceId;               // 30h
  ///
  /// Vendor ID
  ///
  uint16_t                            Vid;                       // 34h
  ///
  /// Device ID
  ///
  uint16_t                            Did;                       // 36h
  ///
  /// Optional Register used in low memory environments prior to CRB_DATA_BUFFER availability.
  ///
  uint64_t                            CrbControlExtension;       // 38h
  ///
  /// Register used to initiate transactions for the CRB interface.
  ///
  uint32_t                            CrbControlRequest;         // 40h
  ///
  /// Register used by the TPM to provide status of the CRB interface.
  ///
  uint32_t                            CrbControlStatus;          // 44h
  ///
  /// Register used by software to cancel command processing.
  ///
  uint32_t                            CrbControlCancel;          // 48h
  ///
  /// Register used to indicate presence of command or response data in the CRB buffer.
  ///
  uint32_t                            CrbControlStart;           // 4Ch
  ///
  /// Register used to configure and respond to interrupts.
  ///
  uint32_t                            CrbInterruptEnable;        // 50h
  uint32_t                            CrbInterruptStatus;        // 54h
  ///
  /// Size of the Command buffer.
  ///
  uint32_t                            CrbControlCommandSize;     // 58h
  ///
  /// Command buffer start address
  ///
  uint32_t                            CrbControlCommandAddressLow;   // 5Ch
  uint32_t                            CrbControlCommandAddressHigh;  // 60h
  ///
  /// Size of the Response buffer
  ///
  uint32_t                            CrbControlResponseSize;    // 64h
  ///
  /// Address of the start of the Response buffer
  ///
  uint64_t                            CrbControlResponseAddrss;  // 68h
  uint8_t                             Reserved4[0x10];           // 70h
  ///
  /// Command/Response Data may be defined as large as 3968 (0xF80).
  ///
  uint8_t                             CrbDataBuffer[0xF80];      // 80h
} ptp_crb_registers;
#pragma pack (1)

//
// Define pointer types used to access CRB registers on PTP
//
void init_tpm() {
  ptp_crb_registers *crb_regs = (ptp_crb_registers *) 0x7ddf0000;
  printf("%s: entry\n", __func__);
  crb_regs->LocalityStatus = 1;
}

void tpm_smc_handler() {
  panic();
  printf("%s: entry\n", __func__);
}
