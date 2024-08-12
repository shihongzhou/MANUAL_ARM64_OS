#ifndef PAN_OS_PRINTK__H
#define PAN_OS_PRINTK__H

#include "lib/string.h"
#include "lib/stdarg.h"

int printk(const char * fmt, ...);
void init_printk_done(void);
#endif

