#include "LED.h"
#include "stm32f4xx.h"

void LED_init(void)
{
    // Enable Clock for GPIO C on AHB1
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    // Set Pin 13 to General purpose output mode
    GPIOC->MODER |= GPIO_MODER_MODER13_0;
    GPIOC->MODER &= ~(GPIO_MODER_MODER13_1);
}

void LED_set(void)
{
    GPIOC->BSRR = GPIO_BSRR_BS13;
}

void LED_reset(void)
{
    GPIOC->BSRR = GPIO_BSRR_BR13;
}

void LED_toggle(void)
{
    GPIOC->ODR ^= GPIO_ODR_OD13;
}