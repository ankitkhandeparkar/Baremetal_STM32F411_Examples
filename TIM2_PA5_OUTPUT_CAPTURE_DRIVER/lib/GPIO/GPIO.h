#ifndef GPIO_H
#define GPIO_H
#include "stm32f4xx.h"
#include <stdbool.h>

// PORT MODE
#define INPUT_MODE ((uint32_t)0x00)
#define OUTPUT_MODE ((uint32_t)0x01)
#define ALTERNATE_FUNCTION_MODE ((uint32_t)0x02)
#define ANALOG_MODE ((uint32_t)0x03)

// OUTPUT TYPE
#define OUTPUT_PUSH_PULL 0
#define OUTPUT_OPEN_DRAIN 1

// SPEED
#define LOW_SPEED ((uint32_t)0X00)
#define MEDIUM_SPEED ((uint32_t)0X01)
#define FAST_SPEED ((uint32_t)0X02)
#define HIGH_SPEED ((uint32_t)0X03)

// PULL-UP / PULL-DOWN
#define NO_PU_PD ((uint32_t)0X00)
#define PULL_UP ((uint32_t)0X01)
#define PULL_DOWN ((uint32_t)0X02)

// GPIO CLOCK ENABLE
#define GPIOA_CLOCK_ENABLE (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN)
#define GPIOB_CLOCK_ENABLE (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN)
#define GPIOC_CLOCK_ENABLE (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN)
#define GPIOD_CLOCK_ENABLE (RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN)
#define GPIOE_CLOCK_ENABLE (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN)
#define GPIOH_CLOCK_ENABLE (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN)

// PIN STATE
#define LOW 0
#define HIGH 1

extern const uint32_t PIN_POS[];

typedef struct
{
    GPIO_TypeDef *port;
    uint32_t pin;
    uint32_t mode;
    bool type;
    uint32_t speed;
    uint32_t pull;
} GPIO_TYPE;

void gpio_pin_mode(GPIO_TypeDef *gpio, uint32_t pin, uint32_t mode);
void gpio_pin_output_type(GPIO_TypeDef *gpio, uint32_t pin, bool output_type);
void gpio_pin_output_speed(GPIO_TypeDef *gpio, uint32_t pin, uint32_t speed);
void gpio_pull_up_pull_down(GPIO_TypeDef *gpio, uint32_t pin, uint32_t pupdr);
void gpio_init(GPIO_TYPE gpio_type);
void gpio_pin_write(GPIO_TypeDef *gpio, uint32_t pin, bool state);
void gpio_pin_toggle(GPIO_TypeDef *gpio, uint32_t pin);

#endif /* GPIO_H */
