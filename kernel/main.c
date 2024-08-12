#include "uart.h"
#include "kernel/printk.h"
#include "kernel/terminal.h"

void kernel_main(void)
{
	uart_init();
	init_printk_done();
	uart_send_string("Welcome to PanOs!\n");

	while (1) {
		shell_terminal();
	}
}
