#include "uart.h"
#include "kernel/printk.h"

void kernel_main(void)
{
	char c = 'a';
	uart_init();
	init_printk_done();

	uart_send_string("123");
	printk("num is %d, char is %c ....\n", 10, c);
	printk("122141r1\n");
	while (1) {
		//printk("122141r1\n");
	}
}
