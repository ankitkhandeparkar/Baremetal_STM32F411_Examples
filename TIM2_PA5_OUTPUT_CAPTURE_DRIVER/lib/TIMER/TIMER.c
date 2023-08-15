/***********************************
 *
 *   Author : Ankit Khandeparkar
 *
 ***********************************/

#include "TIMER.h"
#include "GPIO.h"
#include "stm32f4xx.h"

void tim2_pa5_output_capture(void)
{
    // Set GPIO to alternate function
    GPIO_TYPE pa5;

    pa5.port = GPIOA;
    pa5.pin = 5;
    pa5.mode = ALTERNATE_FUNCTION_MODE;
    pa5.type = 0;
    pa5.speed = 0;
    pa5.pull = 0;

    gpio_init(pa5);

    GPIOA->AFR[0] |= GPIO_AFRL_AFRL5_0;

    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    TIM2->PSC = 1600 - 1;

    TIM2->ARR = 10000 - 1;

    TIM2->CNT = 0;

    TIM2->CCMR1 |= (TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1);

    TIM2->CCER |= TIM_CCER_CC1E;

    TIM2->CR1 |= TIM_CR1_CEN;
}

void tim3_pa6_input_capture(void)
{
    // Set GPIO to alternate function
    GPIO_TYPE pa6;

    pa6.port = GPIOA;
    pa6.pin = 6;
    pa6.mode = ALTERNATE_FUNCTION_MODE;
    pa6.type = 0;
    pa6.speed = 0;
    pa6.pull = 0;

    gpio_init(pa6);

    GPIOA->AFR[0] |= GPIO_AFRL_AFRL6_1;

    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    TIM3->PSC = 1600 - 1;

    TIM3->CCMR1 |= TIM_CCMR1_CC1S_0;

    TIM3->CCER |= TIM_CCER_CC1E;

    TIM3->CR1 |= TIM_CR1_CEN;
}