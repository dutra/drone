
#include "util.h"
#include "config.h"
#include "led.h"
#include <util/delay.h>

void setPort(volatile uint8_t *port, uint8_t pos, uint8_t state) {
        if((state == INPUT) || (state == LOW)) {
            *port &=~(_BV(pos));
        } else if(state == OUTPUT || state == HIGH) {
            *port |= _BV(pos);
        }
}

void setReg(volatile uint8_t *reg, uint8_t pos, uint8_t state) {
        if((state == LOW) || (state == DISABLE)) {
            *reg &=~(_BV(pos));
        } else if(state == HIGH || state == ENABLE) {
            *reg |= _BV(pos);
        }
}

void delay_ms(int time) {
    while(time--) {
        _delay_ms(1);
    }
}

void read_byte(uint8_t byte) {
    for(char pos = 7; pos >= 0; pos--) {
        if(byte & (1 << pos))
            flash_led(1, 500);
        else
            _delay_ms(1000);
    }
}

void read_word(uint16_t word) {
    for(char pos = 15; pos >= 0; pos--) {
        if(word & (1 << pos))
            flash_led(1, 500);
        else
            _delay_ms(1000);
        }
}
