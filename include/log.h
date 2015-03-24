
#ifndef _LOG_H
#define _LOG_H

#include "usart.h"

void log_raw(char * string);
void log_error(char * string);
void log_info(char * string);
void log_int(int n);
void log_double(double n);

#endif
