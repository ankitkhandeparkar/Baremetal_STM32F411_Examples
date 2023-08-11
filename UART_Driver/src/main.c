/***********************************
 *
 *   Author : Ankit Khandeparkar
 *
 ***********************************/

#include "UART.h"
#include "stm32f4xx.h"

int main(void)
{
    int print_number = 10;

    uart_init(UART2, INTERNAL_CLOCK, BAUD115200, TX_ENABLE, RX_ENABLE);

    while (1)
    {
        LOG("Hello from log function for debugging in stm32f411 series!\n");
        LOG("This is an example how to print a value %d\n", print_number);
        for (volatile uint32_t i = 0; i < 1000000; i++)
            ;
    }

    return 0;
}