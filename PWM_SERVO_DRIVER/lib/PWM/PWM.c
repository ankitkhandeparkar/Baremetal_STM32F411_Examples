/***********************************
 *
 *   Author : Ankit Khandeparkar
 *
 ***********************************/
#include "PWM.h"
#include "stm32f413xx.h"
#include <stdint.h>

void pwm_pa8_init(void)
{
    // enable clock to gpio A and timer1
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    // enable GPIO A pin 8 alternate function(AF1)
    GPIOA->MODER |= GPIO_MODER_MODER8_1;
    GPIOA->AFR[1] |= GPIO_AFRH_AFRH0_0;

    TIM1->PSC = 16 - 1;
    TIM1->ARR = 20000 - 1;
    TIM1->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1PE);
    TIM1->BDTR |= TIM_BDTR_MOE;
    TIM1->CCER |= TIM_CCER_CC1E;
    TIM1->CR1 |= TIM_CR1_ARPE;
    TIM1->EGR |= TIM_EGR_UG;
    TIM1->CR1 |= TIM_CR1_CEN;
}

void pwm_pa5_init(void)
{
    // enable clock to gpio A and timer2
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // enable GPIO A pin 5 alternate function(AF1)
    GPIOA->MODER |= GPIO_MODER_MODER5_1;
    GPIOA->AFR[0] |= GPIO_AFRL_AFRL5_0;

    TIM2->PSC = 17 - 1;
    TIM2->ARR = 20000 - 1;
    TIM2->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1PE);
    TIM2->BDTR &= ~TIM_BDTR_MOE;
    TIM2->CCER |= TIM_CCER_CC1E;
    TIM2->CR1 |= TIM_CR1_ARPE;
    TIM2->EGR |= TIM_EGR_UG;
    TIM2->CR1 |= TIM_CR1_CEN;
}

void servo_angle(int pin, int angle)
{
    switch (pin)
    {
    case pin8:
        TIM1->CCR1 = 5.556 * angle + 1000;
        break;

    case pin5:
        TIM2->CCR1 = 5.556 * angle + 1000;
        break;

    default:
        TIM1->CCR1 = 5.556 * angle + 1000;
        break;
    }
}