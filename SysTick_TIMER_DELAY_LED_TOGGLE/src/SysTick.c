#include "LED.h"
#include "stm32f4xx.h"

// The delay should be in milliseconds
void SysTick_init(unsigned long clock, unsigned long delay)
{
    SysTick->LOAD = (unsigned long)(clock * (delay * 0.001)) - 1;
    SysTick->VAL = 0;
    // Enable SysTick Timer and set clock source as AHB
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;
}