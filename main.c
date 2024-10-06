// #define ARMv5TEJ_BRANCH(offset) (0xEA000000 | ((offset) & 0x00FFFFFF)) // Unconditional branch with 24-bit offset

// struct __attribute__((packed, aligned(4))) egon_header
// {
//     uint32_t jump_instruction; // ARM branch instruction to _start 4 bytes 4
//     char magic[8];             // "eGON.BT0"                       8 bytes 12
//     uint32_t checksum;         //                                  4 bytes 16
//     uint32_t length;           //                                  4 bytes 20
//     char spl_signature[4];     // "SPL\2"                          4 bytes 24
//     uint32_t reserved_0[2];    //                                  8 bytes 32
//     uint32_t reserved_1[8];    //                                  32 bytes 64
//     uint32_t reserved_2[8];    //                                  32 bytes 96
// };

// __attribute__((section(".text.start"))) const struct egon_header eGON_header =
//     {
//         .jump_instruction = ARMv5TEJ_BRANCH(0x000160), 
//         .magic = {'e', 'G', 'O', 'N', '.', 'B', 'T', '0'},
//         .checksum = 0, // needs to calculate
//         .length = 0,   // needs to calculate
//         .spl_signature = {'S', 'P', 'L', 2},
//         .reserved_0 = {0, 0},
//         .reserved_1 = {0, 0, 0, 0, 0, 0, 0, 0},
//         .reserved_1 = {0, 0, 0, 0, 0, 0, 0, 0}
//     };
#include <stdint.h>
#include "f1c200s/uart/uart.h"
#include "f1c200s/gpio/gpio.h"
#include "f1c200s/ccu/ccu.h"

// // F1C200s register definitions
#define PA_CFG0 (*(volatile uint32_t *)0x01c20800)
#define PA_DATA (*(volatile uint32_t *)0x01c20810)

// Delay function
void delay(volatile uint32_t count)
{
    while (count--)
    {
        __asm__ volatile("nop");
    }
}

void main();

// Entry point
__attribute__((section(".text.startup")))
__attribute__((naked))
void _start(void)
{
    main();
}

void main()
{
    UART_Init(UART1);
    UART_SetBaudRate(UART1, 115200);
    UART_SetLineControl(UART1, LENGTH_8_BITS, STOP_1_BIT, PARITY_NONE);
    UART_SetFIFO(UART1, FIFO_DISABLED);

    GPIO_SetMode(&GPIO->PORTA, GPIO_PIN_0, PA0_MODE_OUTPUT);

    while (1) {
        GPIO_TogglePin(&GPIO->PORTA, GPIO_PIN_0);
        UART_PutChar(UART1, 'c');
        delay(500000);
    }
}

// // Startup code
// __attribute__((naked, noreturn)) void _reset(void)
// {
//     extern long _sbss, _ebss, _sdata, _edata, _sidata;
//     for (long *dst = &_sbss; dst < &_ebss; dst++)
//         *dst = 0;
//     for (long *dst = &_sdata, *src = &_sidata; dst < &_edata;)
//         *dst++ = *src++;

//     main(); // Call main()
//     for (;;)
//         (void)0; // Infinite loop in the case if main() returns
// }

// extern void _estack(void); // Defined in link.ld

// // 16 standard and 64  handlers
// __attribute__((section(".vectors"))) void (*const tab[64])(void) = {
//     _estack, _reset};