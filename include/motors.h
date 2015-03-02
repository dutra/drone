#ifndef _MOTORS_H
#define _MOTORS_H

typedef enum {
  FULL,
  HALF,
  OFF,
  CUT
} MotorState;

void init_motors();
void set_speed(char n, MotorState state);


#endif
