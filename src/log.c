
#include "log.h"
#include "usart.h"

void log_raw(char * string) {
    usart_put(string);
}
void log_error(char * string) {
    usart_put("ERROR: ");
    usart_put(string);
    usart_put("\n");
}
void log_info(char * string) {
    usart_put(string);
    usart_put("\n");
}

void log_pair(char * string, _Accum d) {
    usart_put(string);
    usart_send_double((double) d);
    usart_put(" ");
}
