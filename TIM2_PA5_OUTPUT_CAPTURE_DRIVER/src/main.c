/***********************************
 *
 *   Author : Ankit Khandeparkar
 *
 ***********************************/
#define __STDC_WANT_LIB_EXT2__ 1 // Define you want TR 24731-2:2010 extensions
#include "TIMER.h"
#include "UART.h"
#include "stm32f4xx.h"

int main(void)
{
    uart_init(UART2, INTERNAL_CLOCK, BAUD115200, TX_ENABLE, RX_ENABLE);

    tim2_pa5_output_capture();

    tim3_pa6_input_capture();

    while (1)
    {
        while (!(TIM3->SR & TIM_SR_CC1IF))
            ;

        TIM3->SR &= ~(TIM_SR_CC1IF);

        LOG("%d\n", TIM3->CCR1);
    }

    return 0;
}