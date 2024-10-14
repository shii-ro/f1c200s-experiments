#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include "f1c200s.h"

/* Port Controller
The Chip has 6 ports for multi-functional input/output pins:
  PORTA : 4 in/out port
  PORTB : 4 in/out port
  PORTC : 4 in/out port
  PORTD : 22 in/out port
  PORTE : 13 in/out port
  PORTF : 6 in/out port
*/

typedef struct
{
	volatile uint32_t CFG_0;
	volatile uint32_t CFG_1;
	volatile uint32_t CFG_2;
	volatile uint32_t CFG_3;
	volatile uint32_t DATA;
	volatile uint32_t DRV_0;
	volatile uint32_t DRV_1;
	volatile uint32_t PUL_0;
	volatile uint32_t PUL_1;
} GPIO_Port;

typedef struct
{
	volatile uint32_t CFG0;			// 0x00
	volatile uint32_t CFG1;			// 0x04
	volatile uint32_t CFG2;			// 0x08
	volatile uint32_t CFG3;			// 0x0C
	volatile uint32_t CTRL;			// 0x10
	volatile uint32_t DRV0;			// 0x14
	volatile uint32_t DRV1;			// 0x18
	volatile uint32_t PUL0;			// 0x1C
	volatile uint32_t PUL1;			// 0x20
	volatile uint32_t STA;			// 0x24
	volatile uint32_t DEB;			// 0x28
} GPIO_PortInt;

typedef struct
{
	GPIO_Port PORTA;				/* 0x01C20800  */
	GPIO_Port PORTB;				/* 0x01C20824  */
	GPIO_Port PORTC;				/* 0x01C20848  */
	GPIO_Port PORTD;
	GPIO_Port PORTE;
	GPIO_Port PORTF;
	GPIO_PortInt PORTD_INT;
	GPIO_PortInt PORTE_INT;
	GPIO_PortInt PORTF_INT;
	volatile uint32_t SDR_PAD_DRV;
	volatile uint32_t SDR_PAD_PUL;
} GPIO_TypeDef;

// Generic GPIO modes
typedef enum
{
	GPIO_MODE_INPUT,
	GPIO_MODE_OUTPUT,
	GPIO_MODE_AF2,
	GPIO_MODE_AF3,
	GPIO_MODE_AF4,
	GPIO_MODE_AF5,
	GPIO_MODE_AF6,
	GPIO_MODE_AF7,
} GPIO_Mode;

typedef enum
{
	GPIO_PIN_RESET = 0U,
	GPIO_PIN_SET
} GPIO_PinState;

typedef enum
{
	GPIO_PIN_0,
	GPIO_PIN_1,
	GPIO_PIN_2,
	GPIO_PIN_3,
	GPIO_PIN_4,
	GPIO_PIN_5,
	GPIO_PIN_6,
	GPIO_PIN_7,
	GPIO_PIN_8,
	GPIO_PIN_9,
	GPIO_PIN_10,
	GPIO_PIN_11,
	GPIO_PIN_12,
	GPIO_PIN_13,
	GPIO_PIN_14,
	GPIO_PIN_15,
	GPIO_PIN_16,
	GPIO_PIN_17,
	GPIO_PIN_18,
	GPIO_PIN_19,
	GPIO_PIN_20,
	GPIO_PIN_21,
	GPIO_PIN_22,
} GPIO_Pin;

// PORTA specific modes
typedef enum
{
	PA0_MODE_INPUT = GPIO_MODE_INPUT,
	PA0_MODE_OUTPUT = GPIO_MODE_OUTPUT,
	PA0_MODE_TP_X1 = GPIO_MODE_AF2,
	// Reserved
	PA0_MODE_DA_BCLK = GPIO_MODE_AF4,
	PA0_MODE_UART1_RTS = GPIO_MODE_AF5,
	PA0_MODE_SPI1_CS = GPIO_MODE_AF6,
	PA0_MODE_DISABLED = GPIO_MODE_AF7,

	PA1_MODE_INPUT = GPIO_MODE_INPUT,
	PA1_MODE_OUTPUT = GPIO_MODE_OUTPUT,
	PA1_MODE_TP_X2 = GPIO_MODE_AF2,
	// Reserved
	PA1_MODE_DA_LRCK = GPIO_MODE_AF4,
	PA1_MODE_UART1_CTS = GPIO_MODE_AF5,
	PA1_MODE_SPI1_MOSI = GPIO_MODE_AF6,
	PA1_MODE_DISABLED = GPIO_MODE_AF7,

	PA2_MODE_INPUT = GPIO_MODE_INPUT,
	PA2_MODE_OUTPUT = GPIO_MODE_OUTPUT,
	PA2_MODE_TP_Y1 = GPIO_MODE_AF2,
	PA2_MODE_PWM0 = GPIO_MODE_AF3,
	PA2_MODE_DA_IN = GPIO_MODE_AF4,
	PA2_MODE_UART1_RX = GPIO_MODE_AF5,
	PA2_MODE_SPI1_CLK = GPIO_MODE_AF6,
	PA2_MODE_DISABLED = GPIO_MODE_AF7,

	PA3_MODE_INPUT = GPIO_MODE_INPUT,
	PA3_MODE_OUTPUT = GPIO_MODE_OUTPUT,
	PA3_MODE_UART1_TX = GPIO_MODE_AF5,
} PORTA_PinMode;

// PORTB specific modes
typedef enum
{
	PB3_MODE_INPUT = GPIO_MODE_INPUT,
	PB3_MODE_OUTPUT = GPIO_MODE_OUTPUT,
	PB3_MODE_DDR_DEF_D = GPIO_MODE_AF2,
	PB3_MODE_IR_RX = GPIO_MODE_AF3,
	PB3_MODE_DISABLED = GPIO_MODE_AF7
} PORTB_PinMode;

typedef enum
{
	INTR_POSITIVE_EDGE,
	INTR_NEGATIVE_EDGE,
	INTR_HIGH_LEVEL,
	INTR_LOW_LEVEL,
	INTR_DOUBLE_EDGE,
}GPIO_INTRMode;

#define SDR_PAD_PUL_INTERNAL_REF_EN_POS          (23U)
#define SDR_PAD_PUL_REF_CONF_FACTOR_POS          (17U)
#define SDR_PAD_PUL_SDRAM_PAD_TYPE_POS           (16U)
#define SDR_PAD_PUL_DQS_PUL_SEL_POS              (8U)
#define SDR_PAD_PUL_DQM_PUL_SEL_POS              (6U)
#define SDR_PAD_PUL_CK_PUL_SEL_POS               (2U)
#define SDR_PAD_PUL_DQ_PUL_SEL_POS               (8U)

#define SDR_PAD_PUL_REF_CONF_FACTOR_MASK         (0x3FU << SDR_PAD_PUL_REF_CONF_FACTOR_POS) // Mask for factor

#define SDR_PAD_PUL_INTERNAL_REF_EN_DISABLE      (0U << SDR_PAD_PUL_INTERNAL_REF_EN_POS)
#define SDR_PAD_PUL_INTERNAL_REF_EN_ENABLE       (1U << SDR_PAD_PUL_INTERNAL_REF_EN_POS)
#define SDR_PAD_PUL_SDRAM_PAD_TYPE_LVCMOS        (0U << SDR_PAD_PUL_SDRAM_PAD_TYPE_POS)
#define SDR_PAD_PUL_SDRAM_PAD_TYPE_SSTL2         (1U << SDR_PAD_PUL_SDRAM_PAD_TYPE_POS)
#define SDR_PAD_PUL_DQS_PUL_SEL_DISABLE          (0U << SDR_PAD_PUL_DQS_PUL_SEL_POS)
#define SDR_PAD_PUL_DQS_PUL_SEL_ENABLE           (1U << SDR_PAD_PUL_DQS_PUL_SEL_POS)
#define SDR_PAD_PUL_DQM_PUL_SEL_DISABLE          (0U << SDR_PAD_PUL_DQM_PUL_SEL_POS)
#define SDR_PAD_PUL_DQM_PUL_SEL_ENABLE           (1U << SDR_PAD_PUL_DQM_PUL_SEL_POS)
#define SDR_PAD_PUL_CK_PUL_SEL_DISABLE           (0U << SDR_PAD_PUL_CK_PUL_SEL_POS)
#define SDR_PAD_PUL_CK_PUL_SEL_ENABLE            (1U << SDR_PAD_PUL_CK_PUL_SEL_POS)
#define SDR_PAD_PUL_DQ_PUL_SEL_DISABLE           (0U << SDR_PAD_PUL_DQ_PUL_SEL_POS)
#define SDR_PAD_PUL_DQ_PUL_SEL_ENABLE            (1U << SDR_PAD_PUL_DQ_PUL_SEL_POS)

// SDR_PAD_DRV Register Bit Positions
#define SDR_PAD_DRV_ODT_MD_POS               (12U)
#define SDR_PAD_DRV_RAS_CAS_MD_POS           (10U)
#define SDR_PAD_DRV_DQS_MD_POS               (8U)
#define SDR_PAD_DRV_DQM_MD_POS               (6U)
#define SDR_PAD_DRV_DA_BA_MD_POS             (4U)
#define SDR_PAD_DRV_CK_MD_POS                (2U)
#define SDR_PAD_DRV_DQ_MD_POS                (0U)

// SDR_PAD_DRV Masks
#define SDR_PAD_DRV_ODT_MD_MASK              (0x3U << SDR_PAD_DRV_ODT_MD_POS)      // Mask for ODT multi-driving select
#define SDR_PAD_DRV_RAS_CAS_MD_MASK          (0x3U << SDR_PAD_DRV_RAS_CAS_MD_POS)  // Mask for RAS#, CAS#, SWE#, SCS#, CKE multi-driving select
#define SDR_PAD_DRV_DQS_MD_MASK              (0x3U << SDR_PAD_DRV_DQS_MD_POS)      // Mask for DQS[3:0] multi-driving select
#define SDR_PAD_DRV_DQM_MD_MASK              (0x3U << SDR_PAD_DRV_DQM_MD_POS)      // Mask for DQM[3:0] multi-driving select
#define SDR_PAD_DRV_DA_BA_MD_MASK            (0x3U << SDR_PAD_DRV_DA_BA_MD_POS)    // Mask for DA[n], BA2, BA1, BA0 multi-driving select
#define SDR_PAD_DRV_CK_MD_MASK               (0x3U << SDR_PAD_DRV_CK_MD_POS)       // Mask for CK, CK# multi-driving select
#define SDR_PAD_DRV_DQ_MD_MASK               (0x3U << SDR_PAD_DRV_DQ_MD_POS)       // Mask for DQ[n] multi-driving select

// Option values for Multi-Driving Select (00: Level 0, 01: Level 1, 10: Level 2, 11: Level 3)

// ODT Multi-Driving Select
#define SDR_PAD_DRV_ODT_MD_LEVEL_0           (0x0U << SDR_PAD_DRV_ODT_MD_POS)
#define SDR_PAD_DRV_ODT_MD_LEVEL_1           (0x1U << SDR_PAD_DRV_ODT_MD_POS)
#define SDR_PAD_DRV_ODT_MD_LEVEL_2           (0x2U << SDR_PAD_DRV_ODT_MD_POS)
#define SDR_PAD_DRV_ODT_MD_LEVEL_3           (0x3U << SDR_PAD_DRV_ODT_MD_POS)

// RAS#, CAS#, SWE#, SCS#, CKE Multi-Driving Select
#define SDR_PAD_DRV_RAS_CAS_MD_LEVEL_0       (0x0U << SDR_PAD_DRV_RAS_CAS_MD_POS)
#define SDR_PAD_DRV_RAS_CAS_MD_LEVEL_1       (0x1U << SDR_PAD_DRV_RAS_CAS_MD_POS)
#define SDR_PAD_DRV_RAS_CAS_MD_LEVEL_2       (0x2U << SDR_PAD_DRV_RAS_CAS_MD_POS)
#define SDR_PAD_DRV_RAS_CAS_MD_LEVEL_3       (0x3U << SDR_PAD_DRV_RAS_CAS_MD_POS)

// DQS[3:0] Multi-Driving Select
#define SDR_PAD_DRV_DQS_MD_LEVEL_0           (0x0U << SDR_PAD_DRV_DQS_MD_POS)
#define SDR_PAD_DRV_DQS_MD_LEVEL_1           (0x1U << SDR_PAD_DRV_DQS_MD_POS)
#define SDR_PAD_DRV_DQS_MD_LEVEL_2           (0x2U << SDR_PAD_DRV_DQS_MD_POS)
#define SDR_PAD_DRV_DQS_MD_LEVEL_3           (0x3U << SDR_PAD_DRV_DQS_MD_POS)

// DQM[3:0] Multi-Driving Select
#define SDR_PAD_DRV_DQM_MD_LEVEL_0           (0x0U << SDR_PAD_DRV_DQM_MD_POS)
#define SDR_PAD_DRV_DQM_MD_LEVEL_1           (0x1U << SDR_PAD_DRV_DQM_MD_POS)
#define SDR_PAD_DRV_DQM_MD_LEVEL_2           (0x2U << SDR_PAD_DRV_DQM_MD_POS)
#define SDR_PAD_DRV_DQM_MD_LEVEL_3           (0x3U << SDR_PAD_DRV_DQM_MD_POS)

// DA[n], BA2, BA1, BA0 Multi-Driving Select
#define SDR_PAD_DRV_DA_BA_MD_LEVEL_0         (0x0U << SDR_PAD_DRV_DA_BA_MD_POS)
#define SDR_PAD_DRV_DA_BA_MD_LEVEL_1         (0x1U << SDR_PAD_DRV_DA_BA_MD_POS)
#define SDR_PAD_DRV_DA_BA_MD_LEVEL_2         (0x2U << SDR_PAD_DRV_DA_BA_MD_POS)
#define SDR_PAD_DRV_DA_BA_MD_LEVEL_3         (0x3U << SDR_PAD_DRV_DA_BA_MD_POS)

// CK, CK# Multi-Driving Select
#define SDR_PAD_DRV_CK_MD_LEVEL_0            (0x0U << SDR_PAD_DRV_CK_MD_POS)
#define SDR_PAD_DRV_CK_MD_LEVEL_1            (0x1U << SDR_PAD_DRV_CK_MD_POS)
#define SDR_PAD_DRV_CK_MD_LEVEL_2            (0x2U << SDR_PAD_DRV_CK_MD_POS)
#define SDR_PAD_DRV_CK_MD_LEVEL_3            (0x3U << SDR_PAD_DRV_CK_MD_POS)

// DQ[n] Multi-Driving Select
#define SDR_PAD_DRV_DQ_MD_LEVEL_0            (0x0U << SDR_PAD_DRV_DQ_MD_POS)
#define SDR_PAD_DRV_DQ_MD_LEVEL_1            (0x1U << SDR_PAD_DRV_DQ_MD_POS)
#define SDR_PAD_DRV_DQ_MD_LEVEL_2            (0x2U << SDR_PAD_DRV_DQ_MD_POS)
#define SDR_PAD_DRV_DQ_MD_LEVEL_3            (0x3U << SDR_PAD_DRV_DQ_MD_POS)

#define GPIO_PIN_SET(port, pin) ((port)->DATA |= (1 << (pin)))
#define GPIO_PIN_CLEAR(port, pin) ((port)->DATA &= ~(1 << (pin)))

#define GPIO       ((GPIO_TypeDef *)F1C200S_PIO_BASE)
#define GPIO_PORTA ((GPIO_Port *) (F1C200S_PIO_BASE ))
#define GPIO_PORTB ((GPIO_Port *) (F1C200S_PIO_BASE + 0x24))
#define GPIO_PORTC ((GPIO_Port *) (F1C200S_PIO_BASE + 0x48))
#define GPIO_PORTD ((GPIO_Port *) (F1C200S_PIO_BASE + 0x6C))
#define GPIO_PORTE ((GPIO_Port *) (F1C200S_PIO_BASE + 0x90))
#define GPIO_PORTF ((GPIO_Port *) (F1C200S_PIO_BASE + 0xB4))

void GPIO_Init();
void GPIO_SetMode(GPIO_Port *port, GPIO_Pin pin, GPIO_Mode mode);
GPIO_PinState GPIO_ReadPin(GPIO_Port *port, GPIO_Pin pin);
void GPIO_WritePin(GPIO_Port *port, GPIO_Pin pin, GPIO_PinState state);
void GPIO_TogglePin(GPIO_Port *port, GPIO_Pin pin);
void GPIO_EnableInterrupt(GPIO_PortInt *pint, GPIO_Pin pin, GPIO_INTRMode int_mode);

#endif