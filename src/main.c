#include "config.h"

#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

#include "motors.h"
#include "util.h"
#include "led.h"

#define WHO_AM_I_G 0x0F
#define MOSI 5
#define SCK 7
#define SS 4

void read_byte(uint8_t byte) {
    for(char pos = 7; pos >= 0; pos--) {
        if(byte & (1 << pos))
            flash_led(1, 500);
        else
            _delay_ms(1000);
    }
}

int main (void) {

    uint8_t whoami = 0x00;

    flash_led(3, 200);

    DDRA = 0xFF;
    PORTA = 0xFE;

    DDRB = (1<<MOSI) | (1<<SCK) | (1<<SS);
    SPCR = (1<<SPE) | (1<<MSTR) | (1<<CPOL) | (1<<CPHA) | (1<<SPR0);

    PORTA = ~((1<<6)|1);

    SPDR = (0x80 | (0x3F & 0x0F));
    while (!(SPSR & (1<<SPIF))) ; // wait

    SPDR = 0x00;
    while (!(SPSR & (1<<SPIF))) ; // wait
    whoami = SPDR;
    PORTA = 0xFE;

    read_byte(whoami);

    flash_led(3, 200);



  while(1) {

  }

  return 0;
}
