#include "uart.h"
#include "../f1c200s.h"
#include "../gpio/gpio.h"
#include "../ccu/ccu.h"

void UART_Init(UART_TypeDef *uart)
{
    // Enable UART clock
    if (uart == UART0)
    {
        CCU->BUS_CLK_GATING_2 |= CCU_BUS_CLK_GATING_2_UART0;
        CCU->BUS_SOFT_RST_2   |= CCU_BUS_SOFT_RST_2_UART0;

        GPIO_SetMode(GPIO_PORTF, GPIO_PIN_2, GPIO_MODE_AF5); 
        GPIO_SetMode(GPIO_PORTF, GPIO_PIN_4, GPIO_MODE_AF5); 
    }
    else if (uart == UART1)
    {
        CCU->BUS_CLK_GATING_2 |= CCU_BUS_CLK_GATING_2_UART1;
        CCU->BUS_SOFT_RST_2   |= CCU_BUS_SOFT_RST_2_UART1;

        GPIO_SetMode(GPIO_PORTA, GPIO_PIN_2, PA2_MODE_UART1_RX);
        GPIO_SetMode(GPIO_PORTA, GPIO_PIN_3, PA3_MODE_UART1_TX);
    }
    else if (uart == UART2)
    {
        CCU->BUS_CLK_GATING_2 |= CCU_BUS_CLK_GATING_2_UART2;
        CCU->BUS_SOFT_RST_2   |= CCU_BUS_SOFT_RST_2_UART2;

        GPIO_SetMode(GPIO_PORTE, GPIO_PIN_0, GPIO_MODE_AF5); 
        GPIO_SetMode(GPIO_PORTE, GPIO_PIN_1, GPIO_MODE_AF5); 
    }
}

void UART_SetBaudRate(UART_TypeDef *uart, uint32_t baudrate)
{
    uart->LCR |= UART_LCR_DLAB;

    uint16_t divisor = 28;
    uint8_t divisor_high = divisor >> 8;
    uint8_t divisor_low = divisor & 0xFF;

    uart->DLH = divisor_high;
    uart->DLL = divisor_low;

    uart->LCR &= ~UART_LCR_DLAB;
}

void UART_SetLineControl(UART_TypeDef *uart, UART_DataLength data_length, UART_StopBits stop_bits, UART_Parity parity)
{
    uart->LCR &= ~0x3;          // Clear Data Legth bits
    uart->LCR |= data_length;

    uart->LCR &= ~UART_LCR_STOP_2BITS; // Cleat Stop Bits
    uart->LCR |= (1 << stop_bits);

    if (parity != PARITY_NONE)
    {
        uart->LCR |= UART_LCR_PEN;
        uart->LCR &= ~(1 << 4);
        uart->LCR |= (parity & 0x1) << 4;
    }
    else
    {
        uart->LCR &= ~UART_LCR_PEN;
    }
}

void UART_SetFIFO(UART_TypeDef *uart, UART_FIFOState fifo_state)
{
    uart->FCR &= ~0x1;
    uart->FCR |= fifo_state;
}

void UART_PutChar(UART_TypeDef *uart, char c)
{   
    while (!(uart->LSR & UART_LSR_TEMT));
    uart->THR = c; 
}

void UART_PutString(UART_TypeDef *uart, const char *s)
{
    while (*s) // Continue until we reach the null terminator
    {
        while (!(uart->LSR & UART_LSR_TEMT));
        uart->THR = *(s++); 
    }
}

uint32_t UART_GetStatus(UART_TypeDef *uart)
{
    return uart->USR;
}
