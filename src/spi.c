#include <avr/io.h>
#include <inttypes.h>
#include "spi.h"


void spi_init(SpiMode spi_mode) {
    DDRB |= (1<<MOSI_BIT) | (1<<SCK_BIT) | (1<<SS_BIT);
    DDRB &= ~(1<<MISO_BIT);

    /* SPCR (SPI Control Register)
    SPCR[7:0]: SPIE SPE DORD MSTR CPOL CPHA SPR1 SPR0
            SPIE: SPI Interrupt Enable
            SPE:  SPI Enable
            DORD: Data Order. MSB first when 1.
            MSTR: Master/Slave Select. Master when 1.
            CPOL: Clock Polarity. Clock is high when idle if CPOL 1.
            CPHA: Clock Phase. CPHA 0 means sample on leading clock edge,
                        while CPHA 1 means sample on trailing clock edge.
            SPR[1:0]: SPI Clock Rate Select.
    */
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

    // For writing, set MSB low
    // For reading, set MSB high
    // For a multiple byte transmission, set bit 6 high
    SPDR = byte;
    while (!(SPSR & (1<<SPIF))) ; // wait
    return SPDR;
}

void spi_write_byte(uint8_t cs_pin, uint8_t sub_address, uint8_t byte) {

    PORTA &= ~(1<<cs_pin);

    // For writing, MSB should be low
    // For single byte, bit 6 should be low
    spi_transmit(sub_address & 0x3F);
    spi_transmit(byte);

    PORTA |= (1<<cs_pin);

}


uint8_t spi_read_byte(uint8_t cs_pin, uint8_t sub_address) {
    uint8_t tmp;

    spi_read_bytes(cs_pin, sub_address, &tmp, 1);

    return tmp;
}

void spi_read_bytes(uint8_t cs_pin, uint8_t sub_address, uint8_t *dest, uint8_t count) {

    PORTA &= ~(1<<cs_pin);

    if (count > 1)
        spi_transmit(0xC0 | (sub_address & 0x3F));
    else
        spi_transmit(0x80 | (sub_address & 0x3F));

    for (int i=0; i<count; i++)
        dest[i] = spi_transmit(0x00);

    PORTA |= (1<<cs_pin);

}
