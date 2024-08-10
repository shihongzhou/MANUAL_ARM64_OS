#include "uart.h"
#include "kernel/printk.h"

void kernel_main(void)
{
	uart_init();
	printk("num is %d, char is %c ....\n", 10, 'a');
	printk("122141r1\n");
	while (1) {
		//printk("122141r1\n");
	}
}
