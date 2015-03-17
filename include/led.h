#ifndef _LED_H
#define _LED_H

#include <avr/io.h>

void set_led(char state);
void flash_led(int n, int delay);

#endif
