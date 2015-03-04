#include "led.h"
#include "config.h"
#include <util/delay.h>

void flash_led() {
    set_led(1);
    _delay_ms(200);
    set_led(0);
}

void set_led(char state) {
  DDRA |= 0x01;
  switch(state) {
  case 0:
    PORTA = 0x00;
    break;
  case 1:
    PORTA = 0x01;
    break;
  }
}
