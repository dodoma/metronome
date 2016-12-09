#include "config.h"
#include "global.h"
#include "mcu.h"
#include "eeprom.h"

void key_init()
{
    KEY_SPEED_UP = 1;
    KEY_SPEED_DOWN = 1;
    KEY_BEAT_MORE = 1;
    KEY_BEAT_LESS = 1;
}

bool key_scan()
{
    if (KEY_STATU != KEY_ALL_OFF) {
        mcu_delay(10);
        if (KEY_STATU != KEY_ALL_OFF) {
            if (KEY_SPEED_UP == 0) {
                g_speed += 1;
            } else if (KEY_SPEED_DOWN == 0) {
                g_speed -= 1;
            } else if (KEY_BEAT_MORE == 0) {
                g_beat += 1;
            } else if (KEY_BEAT_LESS == 0) {
                g_beat -= 1;
            }

            g_speed = MCU_CLAMP(g_speed, 30, 299);
            g_beat  = MCU_CLAMP(g_beat, 1, 16);

            eepr_erase(EEPROM_ADDR);
            eepr_write(EEPROM_ADDR, &g_speed, 2);

            g_tick_need = ((float)60 / g_speed) * 4000;

            while (KEY_STATU != KEY_ALL_OFF);

            return true;
        }
    }

    return false;
}
