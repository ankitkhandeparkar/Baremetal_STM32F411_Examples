#ifndef STM32_GPIO_H
#define STM32_GPIO_H

#define PERIPH_BASE 0x40000000UL
#define AHB1_OFFSET 0X00020000UL
#define AHB1_BASE PERIPH_BASE + AHB1_OFFSET

#define GPIOC_OFFSET 0X00000800UL
#define GPIOC AHB1_BASE + GPIOC_OFFSET

#define RCC_OFFSET 0X00003800UL
#define RCC_BASE AHB1_BASE + RCC_OFFSET

#define RCC_AHB1ENR_OFFSET 0X30UL
#define RCC_AHB1ENR *(volatile unsigned int *)(RCC_BASE + RCC_AHB1ENR_OFFSET)
#define GPIOCEN 1U << 2

#define GPIOC_MODER_OFFSET 0X00UL
#define GPIOC_MODER *(volatile unsigned int *)(GPIOC + GPIOC_MODER_OFFSET)

#define GPIOC_ODR_OFFSET 0X14UL
#define GPIOC_ODR *(volatile unsigned int *)(GPIOC + GPIOC_ODR_OFFSET)

#define LED_PIN 1U << 13

#endif /* STM32_GPIO_H */
