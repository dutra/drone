

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
    imu_read_gyro();

//    read_byte(whoami);
    return 0;
}

void imu_gyro_init() {
        spi_write_byte(CS_G_BIT, CTRL_REG1_G, 0x0F); // Normal mode, enable all axis
        spi_write_byte(CS_G_BIT, CTRL_REG2_G, 0x00); // high cutoff frequency
        spi_write_byte(CS_G_BIT, CTRL_REG3_G, 0x00); // no interrupts
        spi_write_byte(CS_G_BIT, CTRL_REG4_G, 0x00); // scale = 245 dps
        spi_write_byte(CS_G_BIT, CTRL_REG5_G, 0x00); //
}

void imu_read_gyro() {
    uint8_t tmp_l, tmp_h;
    int16_t gx = 0;

    tmp_l = spi_read_byte(CS_G_BIT, OUT_X_L_G);
    tmp_h = spi_read_byte(CS_G_BIT, OUT_X_H_G);

    gx = (tmp_h << 8) | tmp_l;

    read_byte(tmp_h);



}
