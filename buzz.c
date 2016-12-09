#include "config.h"
#include "global.h"

#define FREQ_TICK_H 0xFB
#define FREQ_TICK_L 0xF4

#define FREQ_TONE_H 0xFD
#define FREQ_TONE_L 0xF4

volatile uint8_t _freq_h = 0;
volatile uint8_t _freq_l = 0;


/* 节拍器中断 */
void timer_tick() __interrupt 1
{
    static uint16_t tick_count = 0;
    static uint8_t tone_count = 1;

    TR0 = 0;

    if (++tick_count >= g_tick_need) {
        //printf("ticked\n");
        tick_count = 0;
        if (++tone_count < g_beat) {
            _freq_h = FREQ_TICK_H;
            _freq_l = FREQ_TICK_L;
        } else {
            tone_count = 0;
            _freq_h = FREQ_TONE_H;
            _freq_l = FREQ_TONE_L;
        }
        TR1 = 1;
    }

    TR0 = 1;
}

/* 喇叭高频脉冲信号中断 */
void timer_buzz() __interrupt 3
{
    static uint8_t  buzz_count = 0;

    BUZZ = BUZZ ? 0 : 1;
    TH1 = _freq_h;
    TL1 = _freq_l;

    if (++buzz_count == 20) {
        buzz_count = 0;
        TR1 = 0;
    }
}

void buzz_init()
{
    BUZZ = 1;

    g_tick_need = ((float)60 / g_speed) * 4000; /* 4000 = 1000000 / 250 */

    TMOD = 0x12;

    /*
     * 计时器1使用 250us 中断, 250 * 11.0596 / 12
     */
    TH0 = 0x24;
    TL0 = 0x24;
    _freq_h = FREQ_TICK_H;
    _freq_l = FREQ_TICK_L;

    EA = 1;
    ET0 = 1;
    ET1 = 1;

    TR0 = 1;
    TR1 = 1;
}
