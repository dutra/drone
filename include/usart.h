
#ifndef _USART_H
#define _USART_H

#include <inttypes.h>

void usart_init();
void usart_send (uint8_t byte);
void usart_send_int (int16_t n);

void usart_put (char * string);


#endif
