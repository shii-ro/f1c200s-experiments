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
	GPIO_Port PORTA;
	GPIO_Port PORTB;
	GPIO_Port PORTC;
	GPIO_Port PORTD;
	GPIO_Port PORTE;
	GPIO_Port PORTF;
} GPIO_TypeDef;

// Generic GPIO modes
typedef enum
{
	GPIO_MODE_INPUT = 0x0,	// 0000
	GPIO_MODE_OUTPUT = 0x1, // 0001
	GPIO_MODE_AF2 = 0x2,	// 0010
	GPIO_MODE_AF3 = 0x3,	// 0011
	GPIO_MODE_AF4 = 0x4,	// 0100
	GPIO_MODE_AF5 = 0x5,	// 0101
	GPIO_MODE_AF6 = 0x6,	// 0110
	GPIO_MODE_AF7 = 0x7,	// 0111
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

#define GPIO_PIN_SET(port, pin) ((port)->DATA |= (1 << (pin)))
#define GPIO_PIN_CLEAR(port, pin) ((port)->DATA &= ~(1 << (pin)))

#define GPIO ((GPIO_TypeDef *)F1C200S_PIO_BASE)
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