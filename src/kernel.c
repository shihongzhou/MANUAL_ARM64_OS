#include "uart.h"

void kernel_main(void)
{
	uart_init();
	uart_send_string("Welcome PanOS!\r\n");

	while (1) {
		uart_send(uart_recv());
	}
}
