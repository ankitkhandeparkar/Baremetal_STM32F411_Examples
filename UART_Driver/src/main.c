/***********************************
 *
 *   Author : Ankit Khandeparkar
 *
 ***********************************/

#include "UART.h"
#include "stm32f4xx.h"

int main(void)
{
    uart_init(UART2, INTERNAL_CLOCK, BAUD9600, TX_ENABLE, RX_ENABLE);

    while (1)
    {
        uart_rx_tx();
        // send('h');
        // send('i');
        // send('\n');
        // for (volatile uint32_t i = 0; i < 1000000; i++)
        // ;
    }

    return 0;
}