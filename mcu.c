#include "config.h"

void putchar(char c)
{
    serial_putc(c);
}


void mcu_delay_10us()
{
    __asm
        NOP
        NOP
        NOP
        NOP
        NOP
        NOP
    __endasm;
}

void mcu_delay(uint16_t ms)
{
    uint16_t i;
    uint8_t j;

    for (i = 0; i < ms; i++) {
        for ( j = 0; j < 110; j++) ;
    }
}
