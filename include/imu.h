
#ifndef _IMU_H
#define _IMU_H

#include <inttypes.h>

typedef struct {
    int16_t gx;
    int16_t gy;
    int16_t gz;
} AngularSpeed;

// gyroscope registers
#define WHO_AM_I_G                  0x0F
#define CTRL_REG1_G                 0x20
#define CTRL_REG2_G                 0x21
#define CTRL_REG3_G                 0x22
#define CTRL_REG4_G                 0x23
#define CTRL_REG5_G                 0x24
#define STATUS_REG_G               0x27
#define OUT_X_L_G                      0x28
#define OUT_X_H_G                     0x29
#define OUT_Y_L_G                      0x2A
#define OUT_Y_H_G                     0x2B
#define OUT_Z_L_G                      0x2C
#define OUT_Z_H_G                     0x2D

// accelerometer registers
#define WHO_AM_I_XM                 0x0F

int8_t imu_init();
void imu_gyro_init();
void imu_read_gyro(AngularSpeed *as);
void imu_calc_gyro(AngularSpeed *as);

#endif
