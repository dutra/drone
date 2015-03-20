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
void spi_write_byte(uint8_t cs_pin, uint8_t sub_address, uint8_t byte);
uint8_t spi_read_byte(uint8_t cs_pin, uint8_t sub_address);
void spi_read_bytes(uint8_t cs_pin, uint8_t sub_address, uint8_t *dest, uint8_t count);


#endif
