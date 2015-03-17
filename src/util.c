
#include "util.h"
#include "config.h"

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
