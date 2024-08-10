#ifndef PAN_OS_PRINTK__H
#define PAN_OS_PRINTK__H

#include "lib/string.h"
#include "lib/stdarg.h"

int vsprintf(char *buf, const char *fmt, va_list args);
int printk(const char * fmt, ...);
#endif

