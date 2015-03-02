#include "motors.h"

#include <avr/io.h>
#include <util/delay.h>


void init_motors() {

  set_speed(0, FULL);
  _delay_ms(2000);

  set_speed(0, OFF);
  _delay_ms(2000);

}

void set_speed(char n, MotorState state) {
  if(n > 3 || n < 0) {
    return;
  }

  if(n != 0)
    return;

  // set OC0 pin as output
  DDRB |= 0x08;

  switch(state) {
  case FULL:
    OCR0 = 127;
    break;
  case HALF:
    OCR0 = 94;
    break;
  case OFF:
    OCR0 = 62;
    break;
  case CUT:
    DDRB &= 0xff - 0x08;
    break;
  }

  TCCR0 = 0x62;


}
