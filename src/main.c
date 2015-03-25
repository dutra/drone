#include "config.h"

#include <util/delay.h>
#include <inttypes.h>
#include <stdio.h>

#include "led.h"
#include "imu.h"
#include "usart.h"
#include "log.h"
#include "motors.h"
#include <avrfix.h>

int main (void) {
    AngularSpeed as;
    Acceleration acel;

    flash_led(3, 200);

    usart_init();

    log_info("Starting drone...");

    if(imu_init() != 0)
        log_error("Could not initialize IMU");
    else
        log_info("Done initializing IMU...");



//    log_info("Starting motor...");
//    init_motors();
//    log_info("Testing TOP_LEFT motor...");
//    test_motor(MOTOR_TOP_LEFT);
//    log_info("All done");

    flash_led(3, 200);
    char tmp[64];
  while(1) {
      _delay_ms(500);

      imu_read_accel(&acel);
      log_pair("AX: ", acel.ax);
      log_pair("AY: ", acel.ay);
      log_pair("AZ: ", acel.az);
      log_raw("\n");

      imu_read_gyro(&as);
      log_pair("GX: ", as.gx);
      log_pair("GY: ", as.gy);
      log_pair("GZ: ", as.gz);
      log_raw("\n");



  }

  return 0;
}
