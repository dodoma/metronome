#include "config.h"
#include "global.h"

__code unsigned char _table[] = {
    0xC0, 0xF9, 0xA4, 0xB0,
    0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0x88, 0x83,
    0xC6, 0xA1, 0x86, 0x8E};

void led_on()
{
    uint8_t a, b, c;

    a = g_speed % 10;
    b = (g_speed % 100 - a) / 10;
    c = g_speed / 100;           /* 处理百位 */

    LED_A = _table[b];
    LED_B = _table[a];

    if (c > 1) {
        LED_A &= 0x7F;
        LED_B &= 0x7F;
    } else if (c > 0) {
        LED_B &= 0x7F;
    }
}
