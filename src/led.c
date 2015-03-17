#include "led.h"
#include "config.h"
#include <util/delay.h>
#include "util.h"

void flash_led(int n, int delay) {
    for(int i = 0; i < n; i++) {
        set_led(1);
        delay_ms(delay);
        set_led(0);
        delay_ms(delay);
    }
}

void set_led(char state) {
    setPort(&DDRA, DDA0, OUTPUT);
  switch(state) {
  case 0:
  setPort(&PORTA, PORTA0, LOW);
    break;
  case 1:
  setPort(&PORTA, PORTA0, HIGH);
    break;
  }
}
