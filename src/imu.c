

#include "imu.h"
#include "spi.h"
#include "config.h"

#include <inttypes.h>
#include <avr/io.h>

int8_t imu_init() {
    uint8_t whoami = 0x00;

    DDRA |= (1<<CS_G_BIT) | (1<<CS_XM_BIT);
    PORTA |= (1<<CS_G_BIT) | (1<<CS_XM_BIT);


    spi_init(SPI_MODE3);

    // read WHO_AM_I_G register
    PORTA &= ~(1<<CS_G_BIT);
    spi_transmit(0x80 | (0x3F & WHO_AM_I_G));
    whoami = spi_transmit(0x00);
    PORTA |= (1<<CS_G_BIT);
    if(whoami != 0xD4)
        return 1;

    // read WHO_AM_I_XM
    PORTA &= ~(1<<CS_XM_BIT);
    spi_transmit(0x80 | (0x3F & WHO_AM_I_XM));
    whoami = spi_transmit(0x00);
    PORTA |= (1<<CS_XM_BIT);
    if(whoami != 0x49)
         return 2;

    return 0;
}
