#ifndef _UTIL_H
#define _UTIL_H
#include <avr/io.h>
#include <inttypes.h>


#define INPUT 0
#define OUTPUT 1
#define LOW 0
#define HIGH 1
#define DISABLE 0
#define ENABLE 1

void setPort(volatile uint8_t *port, uint8_t pos, uint8_t state);
void setReg(volatile uint8_t *reg, uint8_t pos, uint8_t state);
void delay_ms(int time);


#endif
