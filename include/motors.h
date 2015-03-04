#ifndef _MOTORS_H
#define _MOTORS_H

typedef enum {
  FULL,
  HALF,
  OFF
} MotorState;

typedef enum {
    MOTOR_TOP_LEFT = 0,
    MOTOR_TOP_RIGHT = 1,
    MOTOR_BOTTOM_RIGHT = 2,
    MOTOR_BOTTOM_LEFT = 3
} MotorPosition;

void init_motor(MotorPosition p);
void init_motors();
void set_speed(MotorPosition p, MotorState state);
void cut_motors();

void test_motor(MotorPosition p);


#endif
