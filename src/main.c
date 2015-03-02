#define F_CPU 1000000UL

#include <avr/io.h>
#include "motors.h"

void set_led(char state);

int main (void) {

  init_motors();

  set_speed(0, HALF);
  _delay_ms(1000);
  set_speed(0, FULL);
  _delay_ms(1000);
  set_speed(0, OFF);
  set_speed(0, CUT);

  
  while(1) {
    set_led(1);
    _delay_ms(1000);
    set_led(0);
    _delay_ms(1000);
  }
  
  return 0;
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
