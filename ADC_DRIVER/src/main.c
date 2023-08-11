/***********************************
 *
 *   Author : Ankit Khandeparkar
 *
 ***********************************/

#include "UART.h"
#include "stm32f4xx.h"

int main(void)
{
    uint16_t samples[2] = {0, 0};

    uart_init(UART2, INTERNAL_CLOCK, BAUD115200, TX_ENABLE, RX_ENABLE);

    // enable clock to DMA1
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

    // enable clock to ADC
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    // configure GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= (GPIO_MODER_MODER0_0 | GPIO_MODER_MODER0_1);
    GPIOA->MODER |= (GPIO_MODER_MODER1_0 | GPIO_MODER_MODER1_1);

    // set sampling rate on both channels for better accuracy (highest possible 480 cycles)
    ADC1->SMPR2 |= (ADC_SMPR2_SMP0_0 | ADC_SMPR2_SMP0_1 | ADC_SMPR2_SMP0_2);
    ADC1->SMPR2 |= (ADC_SMPR2_SMP1_0 | ADC_SMPR2_SMP1_1 | ADC_SMPR2_SMP1_2);

    // channel sequence (channel 0, channel 1)
    ADC1->SQR3 |= (ADC_SQR3_SQ2_0);

    // channel length (2 conversions)
    ADC1->SQR1 |= ADC_SQR1_L_0;

    // scan mode for multiple channels
    ADC1->CR1 |= ADC_CR1_SCAN;

    // enable DMA
    ADC1->CR2 |= ADC_CR2_DMA;

    // DMA settings
    DMA1_Stream0->PAR = (uint32_t)(&(ADC1->DR));
    DMA1_Stream0->M0AR = (uint32_t)samples;
    DMA1_Stream0->NDTR = 2;
    DMA1_Stream0->CR |= (DMA_SxCR_MSIZE_0 | DMA_SxCR_PSIZE_0);
    DMA1_Stream0->CR |= (DMA_SxCR_MINC | DMA_SxCR_CIRC);
    DMA1_Stream0->CR |= DMA_SxCR_EN;

    // enable ADC continuous conversion mode
    ADC1->CR2 |= (ADC_CR2_CONT | ADC_CR2_ADON);

    // start conversion of the channels of ADC
    ADC1->CR2 |= ADC_CR2_SWSTART;

    while (1)
    {
        LOG("ADC value x = %d and y = %d.\n", samples[0], samples[1]);
    }

    return 0;
}