
#include "usart.h"
#include <avr/io.h>


void usart_init() {

    // enable serial transmit
    UCSR0B = (1<<TXEN0);

    // 8N1
    UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);

    // baud rate 4800 for 1MHz with 0.2% error
    UBRR0L = 0x0C;
    UBRR0H = 0x0;
}
void usart_send (uint8_t byte) {
    while (! (UCSR0A & (1<<UDRE0) ) );
    UDR0 = byte;
}

void usart_put (char * string) {
    while(*string) {
        if(*string == '\n')
            usart_send('\r');
        usart_send(*string++);
    }
}
