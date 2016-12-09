#ifndef __BUZZ_H__
#define __BUZZ_H__

void timer_tick() __interrupt 1;
void timer_buzz() __interrupt 3;

void buzz_init();

#endif
