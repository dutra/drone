
#include "motors.h"
#include "led.h"
#include "config.h"

#include <avr/io.h>
#include <util/delay.h>

void init_motor(MotorPosition p) {
    switch(p) {
        case MOTOR_TOP_LEFT:
            DDRB |= 0x08;
            OCR0A = 127;
            TCCR0A |= 0x62;
            break;
        case MOTOR_TOP_RIGHT:
            break;
        case MOTOR_BOTTOM_RIGHT:
            break;
        case MOTOR_BOTTOM_LEFT:
            break;
    }
}

void init_motors() {

    flash_led(1, 500);
    init_motor(MOTOR_TOP_LEFT);
    set_speed(MOTOR_TOP_LEFT, FULL);
    // set_speed(MOTOR_TOP_RIGHT, FULL);
    // set_speed(MOTOR_BOTTOM_RIGHT, FULL);
    // set_speed(MOTOR_BOTTOM_LEFT, FULL);
    _delay_ms(3000);

    flash_led(1, 500);
    set_speed(MOTOR_TOP_LEFT, OFF);
    // set_speed(MOTOR_TOP_RIGHT, OFF);
    // set_speed(MOTOR_BOTTOM_RIGHT, OFF);
    // set_speed(MOTOR_BOTTOM_LEFT, OFF);
    _delay_ms(3000);

}

void cut_motors() {
    OCR0A = 0x0;
    TCCR0A &= 0x60;
    DDRB &= 0xFF - 0x08;

}

void set_speed(MotorPosition p, MotorState state) {

    char duty = 62;

    switch(state) {
        case FULL:
        duty = 127;
        break;
        case HALF:
        duty = 94;
        break;
        case OFF:
        duty = 62;
        break;

    }

    switch(p) {
        case MOTOR_TOP_LEFT:
            OCR0A = duty;
            break;
        case MOTOR_TOP_RIGHT:
            break;
        case MOTOR_BOTTOM_RIGHT:
            break;
        case MOTOR_BOTTOM_LEFT:
            break;
    }
}

void test_motor(MotorPosition p) {
    if(p == MOTOR_TOP_LEFT) {
        flash_led(1, 500);
        set_speed(MOTOR_TOP_LEFT, HALF);
        _delay_ms(1000);

        flash_led(1, 500);
        set_speed(MOTOR_TOP_LEFT, OFF);
        _delay_ms(1000);

        flash_led(1, 500);
        set_speed(MOTOR_TOP_LEFT, FULL);
        _delay_ms(1000);
        flash_led(1, 500);
        set_speed(MOTOR_TOP_LEFT, HALF);
        _delay_ms(1000);
        flash_led(1, 500);
        set_speed(MOTOR_TOP_LEFT, FULL);
        _delay_ms(1000);
        flash_led(1, 500);
        set_speed(MOTOR_TOP_LEFT, HALF);
        _delay_ms(1000);

        flash_led(1, 500);
        set_speed(MOTOR_TOP_LEFT, OFF);
        _delay_ms(1000);

        flash_led(1, 500);
        cut_motors();
        _delay_ms(1000);
    }

}
