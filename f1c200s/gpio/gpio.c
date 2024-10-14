#include "../f1c200s.h"
#include "gpio.h"

void GPIO_Init()
{
}

void GPIO_SetMode(GPIO_Port *port, GPIO_Pin pin, GPIO_Mode mode)
{
    volatile uint32_t *cfg_reg = (volatile uint32_t *)(&port->CFG_0) + (pin / 8); // Select the correct CFG register
    uint32_t pin_pos = ((pin) % 8) * 4; // Determine the bit position for the pin in the register

    // Clear the current mode (4 bits per pin)
    *cfg_reg &= ~(0xF << pin_pos); // 0xF for 4 bits (if modes are 0-15)

    // Set the new mode (ensure mode fits in 4 bits)
    *cfg_reg |= ((mode & 0xF) << pin_pos); // Ensure that the mode value is masked correctly
}

GPIO_PinState GPIO_ReadPin(GPIO_Port *port, GPIO_Pin pin)
{
    uint32_t port_state = port->DATA;
    GPIO_PinState pin_state = (port_state >> pin) & 0x1;

    return pin_state;
}

void GPIO_WritePin(GPIO_Port *port, GPIO_Pin pin, GPIO_PinState state)
{
    if (state == GPIO_PIN_SET)
    {
        port->DATA |= (1 << pin); // Set the bit corresponding to the pin
    }
    else
    {
        port->DATA &= ~(1 << pin); // Clear the bit corresponding to the pin
    }
}

void GPIO_TogglePin(GPIO_Port *port, GPIO_Pin pin)
{
    GPIO_PinState pin_state = GPIO_ReadPin(port, pin);
    pin_state = !pin_state;

    GPIO_WritePin(port, pin, pin_state);
}

void GPIO_EnableInterrupt(GPIO_PortInt *pint, GPIO_Pin pin, GPIO_INTRMode int_mode)
{
    // CFG0 = 0  ~ 7
    // CFG1 = 8  ~ 15
    // CFG2 = 16 ~ 21
    // CFG3 = RESERVED
    uint32_t mask = 0x7 << (pin % 8);
    uint32_t offset = ((pin / 8) * 0x4);

    volatile uint32_t *cfg_reg = (volatile uint32_t *)((uintptr_t)&pint->CFG0 + offset);
    *cfg_reg = (*cfg_reg & ~mask) | (int_mode << (pin % 8));

    // enable the interrupt for the desired pin
    pint->CTRL |= (1 << pin);
}
