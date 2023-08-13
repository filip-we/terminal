#if CFG_TUSB_MCU == OPT_MCU_LPC43XX || CFG_TUSB_MCU == OPT_MCU_LPC18XX || CFG_TUSB_MCU == OPT_MCU_MIMXRT10XX
  #define CFG_TUSB_RHPORT0_MODE       (OPT_MODE_HOST | OPT_MODE_HIGH_SPEED)
#else
  #define CFG_TUSB_RHPORT0_MODE       OPT_MODE_HOST
#endif

#define CFG_TUSB_MEM_SECTION
#define CFG_TUSB_MEM_ALIGN          __attribute__ ((aligned(4)))

#define CFG_TUH_DEVICE_MAX              1

#define CFG_TUH_HUB                     1
#define CFG_TUH_CDC                     0
#define CFG_TUH_HID                     4
#define CFG_TUH_MSC                     0
#define CFG_TUH_VENDOR                  0

#define CFG_TUH_ENUMERATION_BUFSIZE     256
#define CFG_TUH_HID_EPIN_BUFSIZE        128
#define CFG_TUH_HID_EPOUT_BUFSIZE       128
