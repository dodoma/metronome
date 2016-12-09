#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <at89x52.h>
#include <string.h>             /* strcmp */
#include <stdio.h>              /* printf */
#include <stdint.h>             /* uint32_t */
#include <stdbool.h>            /* bool */
#include <serial.h>

#define KEY_SPEED_UP   P3_4
#define KEY_SPEED_DOWN P3_5
#define KEY_BEAT_MORE  P3_6
#define KEY_BEAT_LESS  P3_7
#define KEY_ALL_OFF    0xF0
#define KEY_STATU      (P3 & KEY_ALL_OFF)

#define LED_A P1
#define LED_B P2

#define BUZZ P0_4

#endif
