#include "config.h"

#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

#include "motors.h"
#include "util.h"
#include "led.h"
#include "imu.h"




int main (void) {

    flash_led(3, 200);

    if(imu_init()) {
        flash_led(1, 500);
    }

    flash_led(3, 200);

  while(1) {

  }

  return 0;
}
