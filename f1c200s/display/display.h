#ifndef DISPLAY_H_
#define DISPLAY_H_ 

#include <stdint.h>
#include "f1c200s.h"

// The TCON module is timing controller of display output interface.
typedef struct 
{
    volatile uint32_t CTRL;         // 0x00 TCON Control Register
    volatile uint32_t INT_0;        // 0x04 TCON Interrupt Register 0
    volatile uint32_t INT_1;        // 0x08 TCON Interrupt Register 1
    volatile uint32_t FRM_CTRL;     // 0x10 TCON FRM Control Register
    volatile uint32_t FRM_SEED0_R;  // 0x14 TCON FRM Seed0 Red Register
    volatile uint32_t FRM_SEED0_G;  // 0x18 TCON FRM Seed0 Green Register
    volatile uint32_t FRM_SEED0_B;  // 0x1C TCON FRM Seed0 Blue Register
    volatile uint32_t FRM_SEED1_R;  // 0x20 TCON FRM Seed1 Red Register
    volatile uint32_t FRM_SEED1_G;  // 0x24 TCON FRM Seed1 Green Register
    volatile uint32_t FRM_SEED1_B;  // 0x28 TCON FRM Seed1 Blue Register
    volatile uint32_t FRM_TBL_0;    // 0x2C TCON FRM Table Register 0
    volatile uint32_t FRM_TBL_1;    // 0x30 TCON FRM Table Register 1
    volatile uint32_t FRM_TBL_2;    // 0x34 TCON FRM Table Register 2
    volatile uint32_t FRM_TBL_3;    // 0x38 TCON FRM Table Register 3
} TCON_TypeDef;

#define TCON_CTRL_MODULE_EN          (1 << 31)
#define TCON_CTRL_IO_MAP_SEL         (1 << 0)

#define TCON_INT_0_LINE_TRG_1        (1 << 12)  // Triggered when SY1 match the current TCON1 scan line
#define TCON_INT_0_LINE_TRG_0        (1 << 13)  // Triggered when SY0 match the current TCON0 scan line
#define TCON_INT_0_VBI_TCON1         (1 << 14)  // TCON1 vertical blanking interrupt. Asserted during vertical no-display period every frame
#define TCON_INT_0_VBI_TCON0         (1 << 15)  // TCON0 vertical blanking interrupt. Asserted during vertical no-display period every frame.
#define TCON_INT_0_LINE_TRG1_IE      (1 << 28)  // TCON1 line trigger interrupt enable
#define TCON_INT_0_LINE_TRG0_IE      (1 << 29)  // TCON0 line trigger interrupt enable
#define TCON_INT_0_VBI_TCON1_IE      (1 << 30)  // TCON1 vertical blanking interrupt Enable
#define TCON_INT_0_VBI_TCON0_IE      (1 << 31)  // TCON0 vertical blanking interrupt Enable

#define TCON_INT_1_SY1_MASK     0x7FF           // Scan line for TCON1 line trigger(including inactive lines). Setting it for the specified line for trigger0
#define TCON_INT_1_SY0_MASK     (0x7FF << 16)   // Scan line for TCON0 line trigger(including inactive lines). Setting it for the specified line for trigger0

#define TCON_FRM_CTRL_TEST_MODE_MASK          0x3
#define TCON_FRM_CTRL_TEST_MODE_FRM           0x0
#define TCON_FRM_CTRL_TEST_MODE_HALF_5_6_FRM  0x1
#define TCON_FRM_CTRL_TEST_MODE_HALF_8_FRM    0x2
#define TCON_FRM_CTRL_TEST_MODE_HALF_8_5_6    0x3
#define TCON_FRM_CTRL_TCON0_FRM_MODE_B        (1 << 4)
#define TCON_FRM_CTRL_TCON0_FRM_MODE_G        (1 << 5)
#define TCON_FRM_CTRL_TCON0_FRM_MODE_R        (1 << 6)
#define TCON_FRM_CTRL_TCON0_FRM_MEN           (1 << 31)

#define TCON_FRM_SEED0_R_MASK 0xFFFFFF  // avoid, set it to 0
#define TCON_FRM_SEED0_G_MASK 0xFFFFFF  // avoid, set it to 0
#define TCON_FRM_SEED0_B_MASK 0xFFFFFF  // avoid, set it to 0

#define TCON_FRM_SEED1_R_MASK 0xFFFFFF  // avoid, set it to 0
#define TCON_FRM_SEED1_G_MASK 0xFFFFFF  // avoid, set it to 0
#define TCON_FRM_SEED1_B_MASK 0xFFFFFF  // avoid, set it to 0

#define TCON_FRM_TBL_0_MASK   0x7FFFFFFF //  Recommend set as 0x01010000
#define TCON_FRM_TBL_1_MASK   0x7FFFFFFF //  Recommend set as 0x15151111
#define TCON_FRM_TBL_2_MASK   0x7FFFFFFF //  Recommend set as 0x57575555
#define TCON_FRM_TBL_3_MASK   0x7FFFFFFF //  Recommend set as 0x7F7F7777


// TCON0 control LCD timing, output LCD signal and data
typedef struct 
{
    volatile uint32_t CTRL;             // 0x40 TCON0 Control Register
    volatile uint32_t CLK_CTRL;         // 0x44 TCON0 Clock Control Register
    volatile uint32_t BASIC_TIMING_0;   // 0x48 TCON0 Basic Timing Register 0
    volatile uint32_t BASIC_TIMING_1;   // 0x4C TCON0 Basic Timing Register 1
    volatile uint32_t BASIC_TIMING_2;   // 0x50 TCON0 Basic Timing Register 2
    volatile uint32_t BASIC_TIMING_3;   // 0x54 TCON0 Basic Timing Register 3
    volatile uint32_t HV_TIMING;        // 0x58 TCON0 HV Timing Register
    volatile uint32_t CPU_IF;           // 0x60 TCON0 HV Timing Register
    volatile uint32_t CPU_WR;           // 0x64 TCON0 CPU Mode Write Register
    volatile uint32_t CPU_RD;           // 0x68 TCON0 CPU Mode Read Register
    volatile uint32_t CPU_RD_NX;        // 0x6C TCON0 CPU Mode Read NX Register
    volatile uint32_t reserved_0[6];    //
    volatile uint32_t IO_CTRL_0;        // 0x88 TCON0 IO Control Register 0
    volatile uint32_t IO_CTRL_1;        // 0x8C TCON0 IO Control Register 1
} TCON0_TypeDef;

// TCON1 control TV timing, output TV control signal and data to TVE module.
typedef struct 
{
    volatile uint32_t CTRL;             // 0x90
    volatile uint32_t BASIC_TIMING_0;   // 0x94   
    volatile uint32_t BASIC_TIMING_1;   // 0x98
    volatile uint32_t BASIC_TIMING_2;   // 0x9C
    volatile uint32_t BASIC_TIMING_3;   // 0xA0
    volatile uint32_t BASIC_TIMING_4;   // 0xA4
    volatile uint32_t BASIC_TIMING_5;   // 0xA8
    volatile uint32_t reserved_0[11];   // 
    volatile uint32_t IO_CTRL_0;        // 0xF0
    volatile uint32_t IO_CTRL_1;        // 0xF4
    volatile uint32_t DEBUG_INFO;       // 0xF0   
} TCON1_TypeDef;

#define TCON    ((TCON_TypeDef *) F1C200S_TCON_BASE)
#define TCON0   ((TCON0_TypeDef *) F1C200S_TCON_BASE + 0x40)
#define TCON1   ((TCON1_TypeDef *) F1C200S_TCON_BASE + 0x90)

void DISPLAY_Init();

#endif