#ifndef __MCU_H__
#define __MCU_H__

#define MCU_CLAMP(x, a, b) ( ((x) < (a)) ? (a) : ((x) > (b)) ? (b) : (x))

#define NOP __asm                               \
    nop                                         \
    __endasm

#define TRHEE_NOPS NOP;                         \
    NOP;                                        \
    NOP

void mcu_delay_10us();
void mcu_delay(uint16_t ms);

#endif
