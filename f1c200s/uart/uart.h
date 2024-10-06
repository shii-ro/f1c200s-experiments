#include <stdint.h>
#include "f1c200s.h"

typedef struct
{
    union
    {
        volatile uint32_t RBR;              // 0x00 UART Receive Buffer Register
        volatile uint32_t THR;              // 0x00 UART Transmit Holding Register
        volatile uint32_t DLL;              // 0x00 UART Divisor Latch LOW Register
    };
    union
    {
        volatile uint32_t DLH;              // 0x04 UART Divisor Latch HIGH Register
        volatile uint32_t IER;              // 0x04 UART Interrupt Enable Register
    };
    union
    {
        volatile uint32_t IIR;              // 0x08 UART Interrupt Identity Register
        volatile uint32_t FCR;              // 0x08 UART FIFO Control Register
    };
    volatile uint32_t LCR;                  // 0x0C UART Line Control Register
    volatile uint32_t MCR;                  // 0x10 UART Modem Control Register
    volatile uint32_t LSR;                  // 0x14 UART Line Status Register
    volatile uint32_t MSR;                  // 0x18 UART Modem Status Register
    volatile uint32_t SCH;                  // 0x1C UART Scratch Register
    volatile uint32_t reserved_0[22];       // Gap from 0x20 to 0x7C
    volatile uint32_t USR;                  // 0x7C UART Status Register
    volatile uint32_t TFL;                  // 0x80 UART Transmit FIFO Level
    volatile uint32_t RFL;                  // 0x84 UART Receive FIFO Level
    volatile uint32_t HSK;                  // 0x88 UART DMA Handshake Config Register
    volatile uint32_t reserved_1[6];        // Gap from 0x8C to 0xA4
    volatile uint32_t HALT;                 // 0xA4 UART Halt TX Register
    volatile uint32_t reserved_2[2];        // Gap from 0xA8 to 0xB0
    volatile uint32_t DBG_DLL;              // 0xB0 UART Debug DLL Register
    volatile uint32_t DBG_DLH;              // 0xB4 UART Debug DLH Register
} UART_TypeDef;

#define UART0 ((UART_TypeDef *) F1C200S_UART0_BASE)
#define UART1 ((UART_TypeDef *) F1C200S_UART1_BASE)
#define UART2 ((UART_TypeDef *) F1C200S_UART2_BASE)

// UART Line Control Register Bits
#define UART_LCR_DLS_5BITS     0x00
#define UART_LCR_DLS_6BITS     0x01
#define UART_LCR_DLS_7BITS     0x02
#define UART_LCR_DLS_8BITS     0x03
#define UART_LCR_STOP_1BIT     0x00
#define UART_LCR_STOP_2BITS    0x04
#define UART_LCR_PEN           0x08
#define UART_LCR_EPS           0x10
#define UART_LCR_BREAK_CTRL    0x40
#define UART_LCR_DLAB          0x80

// UART FIFO Control Register Bits
#define UART_FCR_FIFO_EN        0x01
#define UART_FCR_RX_FIFO_RST    0x02
#define UART_FCR_TX_FIFO_RST    0x04
#define UART_FCR_RX_TRIG_1BYTE  0x00
#define UART_FCR_RX_TRIG_4BYTE  0x40
#define UART_FCR_RX_TRIG_8BYTE  0x80
#define UART_FCR_RX_TRIG_14BYTE 0xC0

// UART Line Status Register Bits
#define UART_LSR_DR            (1 << 0)
#define UART_LSR_OE            (1 << 1)
#define UART_LSR_PE            (1 << 2)
#define UART_LSR_FE            (1 << 3)
#define UART_LSR_BI            (1 << 4)
#define UART_LSR_THRE          (1 << 5)
#define UART_LSR_TEMT          (1 << 6)
#define UART_LSR_PFE           (1 << 7)

// UART Status Register Bits
#define UART_STATUS_BUSY 0x01   // UART Busy Bit
#define UART_STATUS_TFNF 0x02   // UART Transmit FIFO Not Full
#define UART_STATUS_TFE  0x04   // UART Transmit FIFO Empty
#define UART_STATUS_RFNE 0x08   // UART Receiver FIFO Not Empty
#define UART_STATUS_RFF  0x08   // UART Receiver FIFO Full

typedef enum
{
    LENGTH_5_BITS,
    LENGTH_6_BITS,
    LENGTH_7_BITS,
    LENGTH_8_BITS,
}UART_DataLength;

typedef enum
{
    STOP_1_BIT,
    STOP_1_5BIT,
    STOP_2_BIT = 1,
}UART_StopBits;

typedef enum
{
    PARITY_NONE,
    PARITY_EVEN,
    PARITY_ODD,
}UART_Parity;

typedef enum
{
    FIFO_DISABLED,
    FIFO_ENABLED,
} UART_FIFOState;

// Function Prototypes
void UART_Init(UART_TypeDef* uart);
void UART_SetBaudRate(UART_TypeDef *uart, uint32_t baudrate);
void UART_SetLineControl(UART_TypeDef *uart, UART_DataLength data_length, UART_StopBits stop_bits, UART_Parity parity);
void UART_SetFIFO(UART_TypeDef *uart, UART_FIFOState fifo_state);
void UART_PutChar(UART_TypeDef *uart, char c);
void UART_PutString(UART_TypeDef *uart, const char *s);
char UART_GetChar(UART_TypeDef *uart);
uint32_t UART_GetStatus(UART_TypeDef *uart);