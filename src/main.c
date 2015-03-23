#include "config.h"

#include <util/delay.h>
#include <inttypes.h>

#include "led.h"
#include "imu.h"
#include "usart.h"
#include "log.h"

int main (void) {
    AngularSpeed as;

    flash_led(3, 200);

    usart_init();

    log_info("Starting drone...");

    if(imu_init() != 0)
        log_error("Could not initialize IMU");
    else
        log_info("Done initializing IMU...");

    imu_read_gyro(&as);
    imu_calc_gyro(&as);
    log_raw("GX: ");
    log_int(as.gx);
    log_raw(", GY: ");
    log_int(as.gy);
    log_raw(", GZ: ");
    log_int(as.gz);
    log_raw("\n");

    flash_led(3, 200);

  while(1) {
      _delay_ms(100);
  }

  return 0;
}
