/***********************************
 *
 *   Author : Ankit Khandeparkar
 *
 ***********************************/

#include "UART.h"
#include "stm32f4xx.h"

int main(void)
{
    volatile int adc_value_x = 0;
    volatile int adc_value_y = 0;

    uart_init(UART2, INTERNAL_CLOCK, BAUD115200, TX_ENABLE, RX_ENABLE);

    // enable clock to ADC
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    // configure GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= (GPIO_MODER_MODER0_0 | GPIO_MODER_MODER0_1);
    GPIOA->MODER |= (GPIO_MODER_MODER1_0 | GPIO_MODER_MODER1_1);

    // adc channel 0 pin PA0
    // ADC1->SQR3 |= (ADC_SQR3_SQ2_0);
    // ADC1->SQR3 &= ~(ADC_SQR3_SQ2_1 | ADC_SQR3_SQ2_2 | ADC_SQR3_SQ2_3 | ADC_SQR3_SQ2_4);
    // ADC1->SQR3 &= ~(ADC_SQR3_SQ1_0 | ADC_SQR3_SQ1_1 | ADC_SQR3_SQ1_2 | ADC_SQR3_SQ1_3 | ADC_SQR3_SQ1_4);
    ADC1->SQR3 = 0X0020;
    // channel length
    // ADC1->SQR1 |= ADC_SQR1_L_0;
    // ADC1->SQR1 &= ~(ADC_SQR1_L_1 | ADC_SQR1_L_2 | ADC_SQR1_L_3);
    ADC1->SQR1 = 0X00100000;
    // enable ADC continuous conversion mode
    ADC1->CR2 |= (ADC_CR2_CONT | ADC_CR2_ADON);

    // start conversion of the channels of ADC
    ADC1->CR2 |= ADC_CR2_SWSTART;

    while (1)
    {
        while (!(ADC1->SR & ADC_SR_EOC))
            ;
        adc_value_x = ADC1->DR;
        adc_value_y = ADC1->DR;
        LOG("ADC value x = %d and y = %d.\n", adc_value_x, adc_value_y);
    }

    return 0;
}