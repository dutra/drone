#include "config.h"

#include <avr/io.h>
#include <util/delay.h>
#include "motors.h"
#include "led.h"

int main (void) {

  init_motors();
  test_motor(MOTOR_TOP_LEFT);


  while(1) {
    set_led(1);
    _delay_ms(1000);
    set_led(0);
    _delay_ms(1000);
  }

  return 0;
}
