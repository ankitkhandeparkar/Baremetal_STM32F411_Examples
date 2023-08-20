/***********************************
 *
 *   Author : Ankit Khandeparkar
 *
 ***********************************/
#include "PWM.h"
#include "clock.h"
#include "stm32f4xx.h"

int main(void)
{
    init_clock();

    pwm_pa8_init();

    // enable timer 3 rcc
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // set 1 second delay
    TIM3->PSC = 14399;
    TIM3->ARR = 2800 - 1;
    TIM3->CNT = 0;
    volatile int i = 0;
    TIM3->CR1 |= TIM_CR1_CEN;
    while (1)
    {
        i = 500;
        TIM1->CCR1 = i;
        while (!(TIM3->SR & TIM_SR_UIF))
            ;
        TIM3->SR &= ~TIM_SR_UIF;
        i = 1500;
        TIM1->CCR1 = i;
        while (!(TIM3->SR & TIM_SR_UIF))
            ;
        TIM3->SR &= ~TIM_SR_UIF;
        i = 2500;
        TIM1->CCR1 = i;
        while (!(TIM3->SR & TIM_SR_UIF))
            ;
        TIM3->SR &= ~TIM_SR_UIF;
    }

    return 0;
}