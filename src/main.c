#include "config.h"

#include <util/delay.h>
#include <inttypes.h>

#include "led.h"
#include "imu.h"
#include "usart.h"
#include "log.h"
#include "motors.h"

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

  while(1) {
      _delay_ms(100);
      imu_read_accel(&acel);
      imu_calc_accel(&acel);
      log_raw("AX: ");
      log_double(acel.ax);
      log_raw(", AY: ");
      log_double(acel.ay);
      log_raw(", AZ: ");
      log_double(acel.az);
      log_raw("\n");

      imu_read_gyro(&as);
      imu_calc_gyro(&as);
      log_raw("GX: ");
      log_int(as.gx);
      log_raw(", GY: ");
      log_int(as.gy);
      log_raw(", GZ: ");
      log_int(as.gz);
      log_raw("\n");

  }

  return 0;
}
