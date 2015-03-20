#include "config.h"

#include <inttypes.h>

#include "led.h"
#include "imu.h"
#include "usart.h"




int main (void) {

    flash_led(3, 200);

    usart_init();

    usart_send('a');
    usart_send('\r');
    usart_send('\n');

//    if(imu_init()) {
//        flash_led(1, 500);
//    }

    flash_led(3, 200);

  while(1) {

  }

  return 0;
}
