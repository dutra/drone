
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
void log_int(int n) {
    usart_send_int(n);
}
