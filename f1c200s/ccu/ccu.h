#include <stdint.h>
#include "f1c200s.h"

typedef struct
{
    volatile uint32_t PLL_CPU_CTRL; // 0x00 PLL_CPU Control Register
    volatile uint32_t reserved_0;
    volatile uint32_t PLL_AUDIO_CTRL; // 0x08 PLL_AUDIO Control Register
    volatile uint32_t reserved_1;
    volatile uint32_t PLL_VIDEO_CTRL; // 0x10 PLL_VIDEO Control Register
    volatile uint32_t reserved_2;
    volatile uint32_t PLL_VE_CTRL; // 0x18 PLL_VE Control Register
    volatile uint32_t reserved_3;
    volatile uint32_t PLL_DDR_CTRL; // 0x20 PLL_DDR Control Register
    volatile uint32_t reserved_4;
    volatile uint32_t PLL_PERIPH_CTRL; // 0x28 PLL_PERIPH Control Register
    volatile uint32_t reserved_5[9];
    volatile uint32_t CPU_CLK_SRC; // 0x50 CPU Clock Source Register
    volatile uint32_t AHB_APB_CFG; // 0x54 AHB/APB/HCLKC Configuration Register
    volatile uint32_t reserved_6[2];
    volatile uint32_t BUS_CLK_GATING_0; // 0x60 Bus Clock Gating Register 0
    volatile uint32_t BUS_CLK_GATING_1; // 0x64 Bus Clock Gating Register 1
    volatile uint32_t BUS_CLK_GATING_2; // 0x68 Bus Clock Gating Register 2
    volatile uint32_t reserved_7[7];
    volatile uint32_t SDMMC0_CLK; // 0x88 SDMMC0 Clock Register
    volatile uint32_t SDMMC1_CLK; // 0x8C SDMMC0 Clock Register
    volatile uint32_t reserved_8[8];
    volatile uint32_t DAUDIO_CLK; // 0xB0 DAUDIO Clock Register
    volatile uint32_t OWA_CLK;    // 0xB4 OWA Clock Register
    volatile uint32_t CIR_CLK;    // 0xB8 CIR Clock Register
    volatile uint32_t reserved_9[4];
    volatile uint32_t USBPHY_CFG; // 0xCC USBPHY Clock Register
    volatile uint32_t reserved_10[12];
    volatile uint32_t DRAM_GATING; // 0x100 DRAM GATING Register
    volatile uint32_t BE_CLK;      // 0x104 BE Clock Register
    volatile uint32_t reserved_11;
    volatile uint32_t FE_CLK; // 0x10C FE Clock Register
    volatile uint32_t reserved_12[2];
    volatile uint32_t TCON_CLK; // 0x118 TCON Clock Register
    volatile uint32_t DI_CLK;   // 0x11C De-interlacer Clock Register
    volatile uint32_t TVE_CLK;  // 0x120 TVE Clock Register
    volatile uint32_t TVD_CLK;  // 0x124 TVD Clock Register
    volatile uint32_t reserved_13[3];
    volatile uint32_t CSI_CLK; // 0x134 CSI Clock Register
    volatile uint32_t reserved_14;
    volatile uint32_t VE_CLK;     // 0x13C VE Clock Register
    volatile uint32_t AC_DIG_CLK; // 0x140 Audio Codec Clock Register
    volatile uint32_t AVS_CLK;    // 0x144 AVS Clock Register
    volatile uint32_t reserved_15[46];
    volatile uint32_t PLL_STABLE0; // 0x200 PLL stable time 0
    volatile uint32_t PLL_STABLE1; // 0x204 PLL stable time 1
    volatile uint32_t reserved_16[6];
    volatile uint32_t PLL_CPU_BIAS;    // 0x220 PLL CPU Bias Register
    volatile uint32_t PLL_AUDIO_BIAS;  // 0x224 PLL Audio Bias Register
    volatile uint32_t PLL_VIDEO_BIAS;  // 0x228 PLL Video Bias Register
    volatile uint32_t PLL_VE_BIAS;     // 0x22c PLL VE Bias Register
    volatile uint32_t PLL_DDR_BIAS;    // 0x230 PLL DDR Bias Register
    volatile uint32_t PLL_PERIPH_BIAS; // 0x234 PLL PERIPH Bias Register
    volatile uint32_t reserved_17[6];
    volatile uint32_t PLL_CPU_TUNING; // 0x250 PLL CPU Tuning Register
    volatile uint32_t reserved_18[3];
    volatile uint32_t PLL_DDR_TUNING; // 0x260 PLL DDR Tuning Register
    volatile uint32_t reserved_19[8];
    volatile uint32_t PLL_AUDIO_PAT; // 0x284 PLL Audio Pattern Control Register
    volatile uint32_t PLL_VIDEO_PAT; // 0x288 PLL Video Pattern Control Register
    volatile uint32_t reserved_20;
    volatile uint32_t PLL_DDR_PAT; // 0x290 PLL DDR Pattern Control Register
    volatile uint32_t reserved_21[11];
    volatile uint32_t BUS_SOFT_RST_0; // 0x2C0 Bus Software Reset Register 0
    volatile uint32_t BUS_SOFT_RST_1; // 0x2C4 Bus Software Reset Register 1
    volatile uint32_t reserved_22[2];
    volatile uint32_t BUS_SOFT_RST_2; // 0x2D0 Bus Software Reset Register 2
} CCU_TypeDef;

#define CCU ((CCU_TypeDef *)F1C200S_CCU_BASE)

// Clock Gating Macros
#define CCU_BUS_CLK_GATING_2_UART2 (1U << 22U)
#define CCU_BUS_CLK_GATING_2_UART1 (1U << 21U)
#define CCU_BUS_CLK_GATING_2_UART0 (1U << 20U)
#define CCU_BUS_CLK_GATING_2_SPI1 (1U << 21U)
#define CCU_BUS_CLK_GATING_2_SPI0 (1U << 20U)
#define CCU_BUS_CLK_GATING_2_SD1 (1U << 9U)
#define CCU_BUS_CLK_GATING_2_SD0 (1U << 8U)
#define CCU_BUS_CLK_GATING_2_DMA (1U << 6U)

// Bus Soft Reset Macros
#define CCU_BUS_SOFT_RST_2_UART2 (1U << 22U)
#define CCU_BUS_SOFT_RST_2_UART1 (1U << 21U)
#define CCU_BUS_SOFT_RST_2_UART0 (1U << 20U)
#define CCU_BUS_SOFT_RST_2_SPI1  (1U << 21U)
#define CCU_BUS_SOFT_RST_2_SPI0  (1U << 20U)
#define CCU_BUS_SOFT_RST_2_SD1   (1U << 9U)
#define CCU_BUS_SOFT_RST_2_SD0 (1U << 8U)
#define CCU_BUS_SOFT_RST_2_DMA (1U << 6U)

// Clock Gating Macros
#define CCU_BUS_CLK_GATING_1_LCD    (1U << 4U)
#define CCU_BUS_CLK_GATING_1_DEBE   (1U << 12U)
#define CCU_BUS_CLK_GATING_1_DEFE   (1U << 14U)

// Bus Soft Reset Macros
#define CCU_BUS_SOFT_RST_1_LCD     (1U << 4U)
#define CCU_BUS_SOFT_RST_1_DEBE    (1U << 12U)
#define CCU_BUS_SOFT_RST_1_DEFE    (1U << 14U)

// Function Prototypes
void CCU_EnableBusClockGating_0(uint32_t peripheral);
void CCU_EnableBusClockGating_1(uint32_t peripheral);
void CCU_EnableBusClockGating_2(uint32_t peripheral);
void CCU_DisableBusClockGating_0(uint32_t peripheral);
void CCU_DisableBusClockGating_1(uint32_t peripheral);
void CCU_DisableBusClockGating_2(uint32_t peripheral);
void CCU_AssertBusSoftReset(uint32_t peripheral);
void CCU_DeassertBusSoftReset(uint32_t peripheral);

uint32_t CCU_GetCPUFrequency(void);