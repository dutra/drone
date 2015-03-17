#include <avr/io.h>
#include <inttypes.h>
#include "spi.h"


void spi_init(SpiMode spi_mode) {
    DDRB |= (1<<MOSI_BIT) | (1<<SCK_BIT) | (1<<SS_BIT);
    DDRB &= ~(1<<MISO_BIT);
    SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);

    switch(spi_mode) {
        case SPI_MODE0:
            SPCR &= ~((1<<CPOL) |  (1<<CPHA));
            break;
        case SPI_MODE1:
            SPCR |= (1<<CPHA);
            SPCR &= ~(1<<CPOL);
            break;
        case SPI_MODE2:
            SPCR &= ~(1<<CPHA);
            SPCR |= (1<<CPOL);
            break;
        case SPI_MODE3:
            SPCR |= (1<<CPOL) | (1<<CPHA);
            break;
    }


}
uint8_t spi_transmit(uint8_t byte) {
    SPDR = byte;
    while (!(SPSR & (1<<SPIF))) ; // wait
    return SPDR;
}
