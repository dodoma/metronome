#include "config.h"
#include "mcu.h"

#include "eeprom.h"
#include "led.h"
#include "key.h"
#include "buzz.h"

uint16_t g_speed = 60;               /* 每分钟节拍数 */
uint8_t  g_beat = 4;                 /* 4/4拍 */
uint16_t g_tick_need = 4000;

void main(void)
{
    uint8_t x = 22;

    serial_init();

    eepr_read(EEPROM_ADDR, &g_speed, 2);

    led_on();
    key_init();
    buzz_init();

    while (1) {
        if (key_scan()) {
            led_on();
            // buzz_reset(); done by timer
        }
    }
}
