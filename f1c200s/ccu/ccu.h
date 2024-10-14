#ifndef CCU_H_
#define CCU_H_

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

// PLLDDR_PAT_CTRL_REG Register Bit Positions
#define PLLDDR_PAT_CTRL_SIG_DELT_PAT_EN_POS   (31U)
#define PLLDDR_PAT_CTRL_SPR_FREQ_MODE_POS     (29U)
#define PLLDDR_PAT_CTRL_WAVE_STEP_POS         (20U)
#define PLLDDR_PAT_CTRL_FREQ_POS              (17U)
#define PLLDDR_PAT_CTRL_WAVE_BOT_POS          (0U)

// PLLDDR_PAT_CTRL_REG Masks
#define PLLDDR_PAT_CTRL_SPR_FREQ_MODE_MASK    (0x3U << PLLDDR_PAT_CTRL_SPR_FREQ_MODE_POS)   // Mask for Spread Frequency Mode
#define PLLDDR_PAT_CTRL_WAVE_STEP_MASK        (0x1FFU << PLLDDR_PAT_CTRL_WAVE_STEP_POS)     // Mask for Wave Step
#define PLLDDR_PAT_CTRL_FREQ_MASK             (0x3U << PLLDDR_PAT_CTRL_FREQ_POS)            // Mask for Frequency
#define PLLDDR_PAT_CTRL_WAVE_BOT_MASK         (0x1FFFFU << PLLDDR_PAT_CTRL_WAVE_BOT_POS)    // Mask for Wave Bottom

#define PLLDDR_DAT_CTRL_WAVE_BOT(value)       (value << PLLDDR_PAT_CTRL_WAVE_BOT_POS)  
#define PLLDDR_PAT_CTRL_WAVE_STEP(value)      (value << PLLDDR_PAT_CTRL_WAVE_STEP_POS)  
#define PLLDDR_PAT_CTRL_SIG_DELT_PAT_EN  (1U << PLLDDR_PAT_CTRL_SIG_DELT_PAT_EN_POS) 

// Option values for Spread Frequency Mode (00: DC=0, 01: DC=1, 1X: Triangular)
#define PLLDDR_PAT_CTRL_SPR_FREQ_DC_0         (0x0U << PLLDDR_PAT_CTRL_SPR_FREQ_MODE_POS)
#define PLLDDR_PAT_CTRL_SPR_FREQ_DC_1         (0x1U << PLLDDR_PAT_CTRL_SPR_FREQ_MODE_POS)
#define PLLDDR_PAT_CTRL_SPR_FREQ_TRIANGULAR   (0x2U << PLLDDR_PAT_CTRL_SPR_FREQ_MODE_POS)

// Option values for Frequency (00: 31.5KHz, 01: 32KHz, 10: 32.5KHz, 11: 33KHz)
#define PLLDDR_PAT_CTRL_FREQ_31_5KHZ          (0x0U << PLLDDR_PAT_CTRL_FREQ_POS)
#define PLLDDR_PAT_CTRL_FREQ_32KHZ            (0x1U << PLLDDR_PAT_CTRL_FREQ_POS)
#define PLLDDR_PAT_CTRL_FREQ_32_5KHZ          (0x2U << PLLDDR_PAT_CTRL_FREQ_POS)
#define PLLDDR_PAT_CTRL_FREQ_33KHZ            (0x3U << PLLDDR_PAT_CTRL_FREQ_POS)

// PLL_DDR_CTRL_REG Register Bit Positions
#define PLL_DDR_CTRL_PLL_ENABLE_POS           (31U)
#define PLL_DDR_CTRL_LOCK_POS                 (28U)
#define PLL_DDR_CTRL_SIGMA_DELTA_EN_POS       (24U)
#define PLL_DDR_CTRL_CFG_UPDATE_POS           (20U)
#define PLL_DDR_CTRL_FACTOR_N_POS             (8U)
#define PLL_DDR_CTRL_FACTOR_K_POS             (4U)
#define PLL_DDR_CTRL_FACTOR_M_POS             (0U)

// PLL_DDR_CTRL_REG Masks
#define PLL_DDR_CTRL_PLL_ENABLE_MASK          (1U << PLL_DDR_CTRL_PLL_ENABLE_POS)      // Mask for PLL Enable
#define PLL_DDR_CTRL_LOCK_MASK                (1U << PLL_DDR_CTRL_LOCK_POS)            // Mask for PLL Lock status
#define PLL_DDR_CTRL_SIGMA_DELTA_EN_MASK      (1U << PLL_DDR_CTRL_SIGMA_DELTA_EN_POS)  // Mask for Sigma-Delta Enable
#define PLL_DDR_CTRL_CFG_UPDATE_MASK          (1U << PLL_DDR_CTRL_CFG_UPDATE_POS)      // Mask for PLL DDR Configuration Update
#define PLL_DDR_CTRL_FACTOR_N_MASK            (0x1FU << PLL_DDR_CTRL_FACTOR_N_POS)     // Mask for PLL Factor N (5 bits)
#define PLL_DDR_CTRL_FACTOR_K_MASK            (0x3U << PLL_DDR_CTRL_FACTOR_K_POS)      // Mask for PLL Factor K (2 bits)
#define PLL_DDR_CTRL_FACTOR_M_MASK            (0x3U << PLL_DDR_CTRL_FACTOR_M_POS)      // Mask for PLL Factor M (2 bits)

// Option values for PLL Enable (0: Disable, 1: Enable)
#define PLL_DDR_CTRL_PLL_DISABLE              (0x0U << PLL_DDR_CTRL_PLL_ENABLE_POS)
#define PLL_DDR_CTRL_PLL_ENABLE               (0x1U << PLL_DDR_CTRL_PLL_ENABLE_POS)

// Option values for Lock Status (Read-Only: 0: Unlocked, 1: Locked)
#define PLL_DDR_CTRL_LOCK_UNLOCKED            (0x0U << PLL_DDR_CTRL_LOCK_POS)
#define PLL_DDR_CTRL_LOCK_LOCKED              (0x1U << PLL_DDR_CTRL_LOCK_POS)

// Option values for Sigma-Delta Enable (0: Disable, 1: Enable)
#define PLL_DDR_CTRL_SIGMA_DELTA_DISABLE      (0x0U << PLL_DDR_CTRL_SIGMA_DELTA_EN_POS)
#define PLL_DDR_CTRL_SIGMA_DELTA_ENABLE       (0x1U << PLL_DDR_CTRL_SIGMA_DELTA_EN_POS)

// Option values for PLL DDR Configuration Update (0: No effect, 1: Validate PLL)
#define PLL_DDR_CTRL_CFG_NO_EFFECT            (0x0U << PLL_DDR_CTRL_CFG_UPDATE_POS)
#define PLL_DDR_CTRL_CFG_UPDATE               (0x1U << PLL_DDR_CTRL_CFG_UPDATE_POS)

// Option values for PLL Factor N (12:8, Factor N = value + 1)
#define PLL_DDR_CTRL_FACTOR_N_VAL(n)          (((n) & 0x1FU) << PLL_DDR_CTRL_FACTOR_N_POS)  // N value ranges from 1 to 32

// Option values for PLL Factor K (5:4, Factor K = value + 1, range from 1 to 4)
#define PLL_DDR_CTRL_FACTOR_K_VAL(k)          (((k - 1U) & 0x3U) << PLL_DDR_CTRL_FACTOR_K_POS)  // K value ranges from 1 to 4

// Option values for PLL Factor M (1:0, Factor M = value + 1, range from 1 to 4)
#define PLL_DDR_CTRL_FACTOR_M_VAL(m)          (((m - 1U) & 0x3U) << PLL_DDR_CTR)

// BUS_CLK_GATING_REG0 Register Bit Positions
#define BUS_CLK_GATING_USB_OTG_POS        (24U)
#define BUS_CLK_GATING_SPI1_POS           (21U)
#define BUS_CLK_GATING_SPI0_POS           (20U)
#define BUS_CLK_GATING_SDRAM_POS          (14U)
#define BUS_CLK_GATING_SD1_POS            (9U)
#define BUS_CLK_GATING_SD0_POS            (8U)
#define BUS_CLK_GATING_DMA_POS            (6U)

// BUS_CLK_GATING_REG0 Masks
#define BUS_CLK_GATING_USB_OTG_MASK       (1U << BUS_CLK_GATING_USB_OTG_POS)   // Mask for USB-OTG Gating Clock
#define BUS_CLK_GATING_SPI1_MASK          (1U << BUS_CLK_GATING_SPI1_POS)      // Mask for SPI1 Gating Clock
#define BUS_CLK_GATING_SPI0_MASK          (1U << BUS_CLK_GATING_SPI0_POS)      // Mask for SPI0 Gating Clock
#define BUS_CLK_GATING_SDRAM_MASK         (1U << BUS_CLK_GATING_SDRAM_POS)     // Mask for SDRAM Gating Clock
#define BUS_CLK_GATING_SD1_MASK           (1U << BUS_CLK_GATING_SD1_POS)       // Mask for SD1 Gating Clock
#define BUS_CLK_GATING_SD0_MASK           (1U << BUS_CLK_GATING_SD0_POS)       // Mask for SD0 Gating Clock
#define BUS_CLK_GATING_DMA_MASK           (1U << BUS_CLK_GATING_DMA_POS)       // Mask for DMA Gating Clock

// Option values for Gating Clocks (0: Mask, 1: Pass)
#define BUS_CLK_GATING_MASK               (0x0U)  // Mask the clock
#define BUS_CLK_GATING_PASS               (0x1U)  // Pass the clock

// Option values for specific clocks
#define BUS_CLK_GATING_USB_OTG_MASK_VAL   (BUS_CLK_GATING_MASK << BUS_CLK_GATING_USB_OTG_POS)   // Mask USB-OTG Clock
#define BUS_CLK_GATING_USB_OTG_PASS_VAL   (BUS_CLK_GATING_PASS << BUS_CLK_GATING_USB_OTG_POS)   // Pass USB-OTG Clock

#define BUS_CLK_GATING_SPI1_MASK_VAL      (BUS_CLK_GATING_MASK << BUS_CLK_GATING_SPI1_POS)      // Mask SPI1 Clock
#define BUS_CLK_GATING_SPI1_PASS_VAL      (BUS_CLK_GATING_PASS << BUS_CLK_GATING_SPI1_POS)      // Pass SPI1 Clock

#define BUS_CLK_GATING_SPI0_MASK_VAL      (BUS_CLK_GATING_MASK << BUS_CLK_GATING_SPI0_POS)      // Mask SPI0 Clock
#define BUS_CLK_GATING_SPI0_PASS_VAL      (BUS_CLK_GATING_PASS << BUS_CLK_GATING_SPI0_POS)      // Pass SPI0 Clock

#define BUS_CLK_GATING_SDRAM_MASK_VAL     (BUS_CLK_GATING_MASK << BUS_CLK_GATING_SDRAM_POS)     // Mask SDRAM Clock
#define BUS_CLK_GATING_SDRAM_PASS_VAL     (BUS_CLK_GATING_PASS << BUS_CLK_GATING_SDRAM_POS)     // Pass SDRAM Clock

#define BUS_CLK_GATING_SD1_MASK_VAL       (BUS_CLK_GATING_MASK << BUS_CLK_GATING_SD1_POS)       // Mask SD1 Clock
#define BUS_CLK_GATING_SD1_PASS_VAL       (BUS_CLK_GATING_PASS << BUS_CLK_GATING_SD1_POS)       // Pass SD1 Clock

#define BUS_CLK_GATING_SD0_MASK_VAL       (BUS_CLK_GATING_MASK << BUS_CLK_GATING_SD0_POS)       // Mask SD0 Clock
#define BUS_CLK_GATING_SD0_PASS_VAL       (BUS_CLK_GATING_PASS << BUS_CLK_GATING_SD0_POS)       // Pass SD0 Clock

#define BUS_CLK_GATING_DMA_MASK_VAL       (BUS_CLK_GATING_MASK << BUS_CLK_GATING_DMA_POS)       // Mask DMA Clock
#define BUS_CLK_GATING_DMA_PASS_VAL       (BUS_CLK_GATING_PASS << BUS_CLK_GATING_DMA_POS)       // Pass DMA Clock

// BUS_SOFT_RST_REG0 Register Bit Positions
#define BUS_SOFT_RST_USBOTG_POS        (24U)
#define BUS_SOFT_RST_SPI1_POS          (21U)
#define BUS_SOFT_RST_SPI0_POS          (20U)
#define BUS_SOFT_RST_SDRAM_POS         (14U)
#define BUS_SOFT_RST_SD1_POS           (9U)
#define BUS_SOFT_RST_SD0_POS           (8U)
#define BUS_SOFT_RST_DMA_POS           (6U)

// BUS_SOFT_RST_REG0 Masks
#define BUS_SOFT_RST_USBOTG_MASK       (1U << BUS_SOFT_RST_USBOTG_POS)  // Mask for USB-OTG Reset
#define BUS_SOFT_RST_SPI1_MASK         (1U << BUS_SOFT_RST_SPI1_POS)     // Mask for SPI1 Reset
#define BUS_SOFT_RST_SPI0_MASK         (1U << BUS_SOFT_RST_SPI0_POS)     // Mask for SPI0 Reset
#define BUS_SOFT_RST_SDRAM_MASK        (1U << BUS_SOFT_RST_SDRAM_POS)    // Mask for SDRAM Reset
#define BUS_SOFT_RST_SD1_MASK          (1U << BUS_SOFT_RST_SD1_POS)      // Mask for SD/MMC 1 Reset
#define BUS_SOFT_RST_SD0_MASK          (1U << BUS_SOFT_RST_SD0_POS)      // Mask for SD/MMC 0 Reset
#define BUS_SOFT_RST_DMA_MASK          (1U << BUS_SOFT_RST_DMA_POS)      // Mask for DMA Reset

// Option values for Reset (0: Assert, 1: De-assert)
#define BUS_SOFT_RST_ASSERT            (0x0U)  // Assert Reset
#define BUS_SOFT_RST_DEASSERT          (0x1U)  // De-assert Reset

// Option values for specific resets
#define BUS_SOFT_RST_USBOTG_ASSERT_VAL (BUS_SOFT_RST_ASSERT << BUS_SOFT_RST_USBOTG_POS)  // Assert USB-OTG Reset
#define BUS_SOFT_RST_USBOTG_DEASSERT_VAL (BUS_SOFT_RST_DEASSERT << BUS_SOFT_RST_USBOTG_POS)  // De-assert USB-OTG Reset

#define BUS_SOFT_RST_SPI1_ASSERT_VAL   (BUS_SOFT_RST_ASSERT << BUS_SOFT_RST_SPI1_POS)    // Assert SPI1 Reset
#define BUS_SOFT_RST_SPI1_DEASSERT_VAL (BUS_SOFT_RST_DEASSERT << BUS_SOFT_RST_SPI1_POS)  // De-assert SPI1 Reset

#define BUS_SOFT_RST_SPI0_ASSERT_VAL   (BUS_SOFT_RST_ASSERT << BUS_SOFT_RST_SPI0_POS)    // Assert SPI0 Reset
#define BUS_SOFT_RST_SPI0_DEASSERT_VAL (BUS_SOFT_RST_DEASSERT << BUS_SOFT_RST_SPI0_POS)  // De-assert SPI0 Reset

#define BUS_SOFT_RST_SDRAM_ASSERT_VAL  (BUS_SOFT_RST_ASSERT << BUS_SOFT_RST_SDRAM_POS)   // Assert SDRAM Reset
#define BUS_SOFT_RST_SDRAM_DEASSERT_VAL (BUS_SOFT_RST_DEASSERT << BUS_SOFT_RST_SDRAM_POS) // De-assert SDRAM Reset

#define BUS_SOFT_RST_SD1_ASSERT_VAL    (BUS_SOFT_RST_ASSERT << BUS_SOFT_RST_SD1_POS)     // Assert SD/MMC 1 Reset
#define BUS_SOFT_RST_SD1_DEASSERT_VAL  (BUS_SOFT_RST_DEASSERT << BUS_SOFT_RST_SD1_POS)   // De-assert SD/MMC 1 Reset

#define BUS_SOFT_RST_SD0_ASSERT_VAL    (BUS_SOFT_RST_ASSERT << BUS_SOFT_RST_SD0_POS)     // Assert SD/MMC 0 Reset
#define BUS_SOFT_RST_SD0_DEASSERT_VAL  (BUS_SOFT_RST_DEASSERT << BUS_SOFT_RST_SD0_POS)   // De-assert SD/MMC 0 Reset

#define BUS_SOFT_RST_DMA_ASSERT_VAL    (BUS_SOFT_RST_ASSERT << BUS_SOFT_RST_DMA_POS)     // Assert DMA Reset
#define BUS_SOFT_RST_DMA_DEASSERT_VAL  (BUS_SOFT_RST_DEASSERT << BUS_SOFT_RST_DMA_POS)   // De-assert DMA Reset   


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

#endif