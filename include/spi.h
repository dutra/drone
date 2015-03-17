#ifndef _SPI_H
#define _SPI_H

#include <inttypes.h>

typedef enum {
    SPI_MODE0,
    SPI_MODE1,
    SPI_MODE2,
    SPI_MODE3
} SpiMode;

void spi_init(SpiMode spi_mode);
uint8_t spi_transmit(uint8_t byte);


#endif
