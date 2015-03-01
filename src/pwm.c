#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

typedef enum {
  FULL,
  HALF,
  OFF,
  CUT
} MotorState;

void set_speed(char n, MotorState state);
void set_led(char state);

int main (void) {

  set_speed(0, FULL);
  _delay_ms(2000);
 
  set_speed(0, OFF);
  _delay_ms(4000);

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

void set_speed(char n, MotorState state) {
  if(n > 3 || n < 0) {
    return;
  }

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
