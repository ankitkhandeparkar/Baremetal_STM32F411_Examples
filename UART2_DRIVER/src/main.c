#include "UART.h"
#include "stm32f4xx.h"

#define Baudrate 115200UL
#define Clock 16000000UL // Using internal default clock 16MHz

int main(void)
{
    UART2_Init(Clock, Baudrate);
    while (1)
    {
        UART_read_write();
        // UART_write('H');
        // UART_write('i');
        // UART_write('\n');
    }
    return 0;
}