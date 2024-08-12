
#include "system.h"
#include "kernel/terminal.h"
#include "kernel/printk.h"
#include "lib/string.h"

static char terminal_buffer[1024];
static uchar switch_line = 1;
uchar recv_finish = 0;
extern void trigger_alignment(void);

void process_command(char *input) {
    char *command = strtok(input, " ");
    char *args[10]; // 假设最多支持10个参数
    int i = 0;
    recv_finish = 0;

    //此时是一个简单的换行，无命令
    if(command == NULL) {
        return;
    }
    /* 第一块是命令*/
     // 解析命令参数
    while (command != NULL && i < 10) {
        args[i++] = command;
        command = strtok(NULL, " ");
    }
    args[i] = NULL; // 参数数组以NULL结尾

    // 处理不同的命令
    if (strcmp(args[0], "echo") == 0) {
        for (int j = 1; args[j] != NULL; j++) {
            printk("%s ", args[j]);
        }
        printk("\n");
    } else if (strcmp(args[0], "help") == 0) {
        printk("Supported commands: echo, help, exit\n");
    } else if (strcmp(args[0], "trigger") == 0){
        printk("trigger instruction exception \n");
        trigger_alignment();
    }
}

void shell_terminal(void)
{
    char tmp;
    char *buffer_ptr = terminal_buffer;
    
    while (1) {

        if(switch_line)
        {
            switch_line = 0;
            printk("shell>> :");
        }
        tmp = uart_recv();
        switch (tmp)
        {
            //处理回车
            case '\r':
                switch_line = 1;
                uart_send(tmp);
                uart_send('\n');
                *buffer_ptr = 0;
                recv_finish = 1;
                buffer_ptr ++;
                break;
            //处理退格
            case 0x8:
                *buffer_ptr = 0;
                if(buffer_ptr != terminal_buffer) 
                {
                    uart_send('\b');
                    uart_send(' ');
                    uart_send('\b');
                    buffer_ptr --;
                }
                break;
            //常规回显
            default:
                uart_send(tmp);
                *buffer_ptr = tmp;
                buffer_ptr ++;
                break;
        }
       
        if(recv_finish)
        {
            // 解析并执行命令
            process_command(terminal_buffer);
            buffer_ptr = terminal_buffer;
        }
    }
}
