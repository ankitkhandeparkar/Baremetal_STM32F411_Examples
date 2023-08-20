#include "GPIO.h"
#include "stm32f4xx.h"

const uint32_t PIN_POS[] = {
    // PIN0  PIN1  PIN2  PIN3  PIN4  PIN5  PIN6  PIN7 PIN8
    0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x10,
    // PIN9  PIN10 PIN11 PIN12 PIN13 PIN14 PIN15
    0x12, 0x14, 0x16, 0x18, 0x1A, 0x1C, 0x1E};

void gpio_pin_mode(GPIO_TypeDef *gpio, uint32_t pin, uint32_t mode)
{
    switch (mode)
    {
    case INPUT_MODE:
        gpio->MODER &= ~((1 << PIN_POS[pin]) | (1 << (PIN_POS[pin] + 1)));
        break;
    case OUTPUT_MODE:
        gpio->MODER |= (1 << PIN_POS[pin]);
        gpio->MODER &= ~(1 << (PIN_POS[pin] + 1));
        break;
    case ALTERNATE_FUNCTION_MODE:
        gpio->MODER &= ~(1 << PIN_POS[pin]);
        gpio->MODER |= (1 << (PIN_POS[pin] + 1));
        break;
    case ANALOG_MODE:
        gpio->MODER |= ((1 << PIN_POS[pin]) | 1 << (PIN_POS[pin] + 1));
        break;

    default:
        gpio->MODER &= ~((1 << PIN_POS[pin]) | (1 << (PIN_POS[pin] + 1)));
        break;
    }
}

void gpio_pin_output_type(GPIO_TypeDef *gpio, uint32_t pin, bool output_type)
{
    if (output_type) // boolean HIGH ( open-drain )
    {
        gpio->OTYPER |= (1 << pin);
    }
    else // boolean LOW ( push-pull )
    {
        gpio->OTYPER &= ~(1 << pin);
    }
}

void gpio_pin_output_speed(GPIO_TypeDef *gpio, uint32_t pin, uint32_t speed)
{
    switch (speed)
    {
    case LOW_SPEED:
        gpio->OSPEEDR &= ~(1 << PIN_POS[pin] | (1 << (PIN_POS[pin] + 1)));
        break;
    case MEDIUM_SPEED:
        gpio->OSPEEDR |= (1 << PIN_POS[pin]);
        gpio->OSPEEDR &= ~(1 << (PIN_POS[pin] + 1));
        break;
    case FAST_SPEED:
        gpio->OSPEEDR &= ~(1 << PIN_POS[pin]);
        gpio->OSPEEDR |= (1 << (PIN_POS[pin] + 1));
        break;
    case HIGH_SPEED:
        gpio->OSPEEDR |= ((1 << PIN_POS[pin]) | (1 << (PIN_POS[pin] + 1)));
        break;

    default:
        gpio->OSPEEDR &= ~(1 << PIN_POS[pin] | (1 << (PIN_POS[pin] + 1)));
        break;
    }
}

void gpio_pull_up_pull_down(GPIO_TypeDef *gpio, uint32_t pin, uint32_t pupdr)
{
    switch (pupdr)
    {
    case NO_PU_PD:
        gpio->PUPDR &= ~((1 << PIN_POS[pin]) | (1 << (PIN_POS[pin] + 1)));
        break;

    case PULL_UP:
        gpio->PUPDR |= (1 << PIN_POS[pin]);
        gpio->PUPDR &= ~(1 << (PIN_POS[pin] + 1));
        break;

    case PULL_DOWN:
        gpio->PUPDR &= ~(1 << PIN_POS[pin]);
        gpio->PUPDR |= (1 << (PIN_POS[pin] + 1));
        break;

    default:
        gpio->PUPDR &= ~((1 << PIN_POS[pin]) | (1 << (PIN_POS[pin] + 1)));
        break;
    }
}

void gpio_init(GPIO_TYPE gpio_type)
{
    if (gpio_type.port == GPIOA)
        GPIOA_CLOCK_ENABLE;

    if (gpio_type.port == GPIOB)
        GPIOB_CLOCK_ENABLE;

    if (gpio_type.port == GPIOC)
        GPIOC_CLOCK_ENABLE;

    if (gpio_type.port == GPIOD)
        GPIOD_CLOCK_ENABLE;

    if (gpio_type.port == GPIOE)
        GPIOE_CLOCK_ENABLE;

    if (gpio_type.port == GPIOH)
        GPIOH_CLOCK_ENABLE;

    gpio_pin_mode(gpio_type.port, gpio_type.pin, gpio_type.mode);

    if (gpio_type.mode == OUTPUT_MODE)
    {
        gpio_pin_output_type(gpio_type.port, gpio_type.pin, gpio_type.type);

        gpio_pin_output_speed(gpio_type.port, gpio_type.pin, gpio_type.speed);
    }

    if (gpio_type.mode == INPUT_MODE)
    {
        gpio_pull_up_pull_down(gpio_type.port, gpio_type.pin, gpio_type.pull);
    }
}

void gpio_pin_write(GPIO_TypeDef *gpio, uint32_t pin, bool state)
{
    if (state) // boolean HIGH
    {
        gpio->BSRR = (1 << pin); // Set pin
    }
    else // boolean LOW
    {
        gpio->BSRR = (1 << (pin + 16)); // Reset pin
    }
}

void gpio_pin_toggle(GPIO_TypeDef *gpio, uint32_t pin)
{
    gpio->ODR ^= (1 << pin);
}
