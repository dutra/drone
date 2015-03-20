
#ifndef _IMU_H
#define _IMU_H

#include <inttypes.h>

// gyroscope registers
#define WHO_AM_I_G                  0x0F
#define CTRL_REG1_G                 0x20
#define CTRL_REG2_G                 0x21
#define CTRL_REG3_G                 0x22
#define CTRL_REG4_G                 0x23
#define CTRL_REG5_G                 0x24
#define STATUS_REG_G               0x27
#define OUT_X_L_G                     0x28
#define OUT_X_H_G                     0x29

// accelerometer registers
#define WHO_AM_I_XM                 0x0F



int8_t imu_init();
void imu_gyro_init();
void imu_read_gyro();

#endif
