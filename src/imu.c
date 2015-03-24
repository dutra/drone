

#include "imu.h"
#include "spi.h"
#include "config.h"
#include "util.h"

#include <inttypes.h>
#include <avr/io.h>

int8_t imu_init() {
    uint8_t whoami = 0x00;

    DDRA |= (1<<CS_G_BIT) | (1<<CS_XM_BIT);
    PORTA |= (1<<CS_G_BIT) | (1<<CS_XM_BIT);


    spi_init(SPI_MODE3);

    // read WHO_AM_I_G register
    whoami = spi_read_byte(CS_G_BIT, WHO_AM_I_G);
    if(whoami != 0xD4)
        return 1;

    // read WHO_AM_I_XM
    whoami = spi_read_byte(CS_XM_BIT, WHO_AM_I_XM);
    if(whoami != 0x49)
        return 2;

    imu_gyro_init();
    imu_accel_init();


    return 0;
}

void imu_accel_init() {
    spi_write_byte(CS_XM_BIT, CTRL_REG0_XM, 0x00);  // disable FIFO and interrupts
    spi_write_byte(CS_XM_BIT, CTRL_REG1_XM, 0x67);  // 200 Hz data rate, enable all axis
    spi_write_byte(CS_XM_BIT, CTRL_REG2_XM, 0x00);  // 2g scale
    spi_write_byte(CS_XM_BIT, CTRL_REG3_XM, 0x00);  // no interrupts
}

void imu_read_accel(Acceleration *acel) {
    uint8_t tmp_l, tmp_h;

    tmp_l = spi_read_byte(CS_XM_BIT, OUT_X_L_A);
    tmp_h = spi_read_byte(CS_XM_BIT, OUT_X_H_A);
    acel->ax = (tmp_h << 8) | tmp_l;

    tmp_l = spi_read_byte(CS_XM_BIT, OUT_Y_L_A);
    tmp_h = spi_read_byte(CS_XM_BIT, OUT_Y_H_A);
    acel->ay = (tmp_h << 8) | tmp_l;

    tmp_l = spi_read_byte(CS_XM_BIT, OUT_Z_L_A);
    tmp_h = spi_read_byte(CS_XM_BIT, OUT_Z_H_A);
    acel->az = (tmp_h << 8) | tmp_l;

}


void imu_gyro_init() {
        spi_write_byte(CS_G_BIT, CTRL_REG1_G, 0x0F); // Normal mode, enable all axis
        spi_write_byte(CS_G_BIT, CTRL_REG2_G, 0x00); // high cutoff frequency
        spi_write_byte(CS_G_BIT, CTRL_REG3_G, 0x00); // no interrupts
        spi_write_byte(CS_G_BIT, CTRL_REG4_G, 0x00); // scale = 245 dps
        spi_write_byte(CS_G_BIT, CTRL_REG5_G, 0x00); //
}

void imu_read_gyro(AngularSpeed *as) {
    uint8_t tmp_l, tmp_h;

    tmp_l = spi_read_byte(CS_G_BIT, OUT_X_L_G);
    tmp_h = spi_read_byte(CS_G_BIT, OUT_X_H_G);
    as->gx = (tmp_h << 8) | tmp_l;

    tmp_l = spi_read_byte(CS_G_BIT, OUT_Y_L_G);
    tmp_h = spi_read_byte(CS_G_BIT, OUT_Y_H_G);
    as->gy = (tmp_h << 8) | tmp_l;

    tmp_l = spi_read_byte(CS_G_BIT, OUT_Z_L_G);
    tmp_h = spi_read_byte(CS_G_BIT, OUT_Z_H_G);
    as->gz = (tmp_h << 8) | tmp_l;

}

void imu_calc_gyro(AngularSpeed *as) {
    as->gx *= 245.0/32768.0;
    as->gy *= 245.0/32768.0;
    as->gz *= 245.0/32768.0;
}

void imu_calc_accel(Acceleration *acel) {
    acel->ax *= 2.0/32768.0;
    acel->ay *= 2.0/32768.0;
    acel->az *= 2.0/32768.0;
}
