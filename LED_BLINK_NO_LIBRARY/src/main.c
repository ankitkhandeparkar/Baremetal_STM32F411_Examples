#include "STM32_GPIO.h"

int main(void)
{
    RCC_AHB1ENR |= GPIOCEN;

    GPIOC_MODER |= 1U << 26;
    GPIOC_MODER &= ~(1U << 27);

    while (1)
    {
        GPIOC_ODR ^= LED_PIN;
        for (volatile int i = 0; i < 1000000; i++)
            ;
    }

    return 0;
}
