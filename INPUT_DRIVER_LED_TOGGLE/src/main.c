#include "stm32f4xx.h"
#define GPIOAEN 1U << 0
#define GPIOCEN 1U << 2
#define BUTTON_PIN 1U << 5
#define SET_LED_PIN 1U << 13
#define RESET_LED_PIN 1U << 29
#define __IO volatile
int main(void)
{

    /* Enable clock to GPIO ports A and C */
    RCC->AHB1ENR |= GPIOAEN;
    RCC->AHB1ENR |= GPIOCEN;

    /* Set Port A pin 5 as input mode */
    GPIOA->MODER &= ~(1U << 10);
    GPIOA->MODER &= ~(1U << 11);

    /* Set Port C pin 13 as output mode */
    GPIOC->MODER |= 1U << 26;
    GPIOC->MODER &= ~(1U << 27);

    /* Set Port A pin 5 as pull-up */
    GPIOA->PUPDR |= 1U << 10;
    GPIOA->PUPDR &= ~(1U << 11);

    while (1)
    {
        /* If button is pressed the LED turns on */
        /* If button is released the LED turns off */
        if (GPIOA->IDR & BUTTON_PIN)
        {
            GPIOC->BSRR = SET_LED_PIN;
        }
        else
        {
            GPIOC->BSRR = RESET_LED_PIN;
        }
    }

    return 0;
}