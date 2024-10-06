MEMORY
{
    ram : ORIGIN = 0x2000, LENGTH = 32K
}

SECTIONS
{
    .text.startup : {
        *(.text.startup)
    } > ram

    .text : {
        *(.text*)
    } > ram

    .rodata : {
        *(.rodata*)
    } > ram

    .data : {
        *(.data*)
    } > ram

    .bss : {
        *(.bss*)
    } > ram

    /* Define stack top. Adjust the address as needed for your specific MCU */
    _stack_top = ORIGIN(ram) + LENGTH(ram);
}