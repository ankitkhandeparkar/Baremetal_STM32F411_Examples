#include "GPIO.h"
#include "stm32f4xx.h"

int main(void)
{
    GPIO_TYPE led;
    led.port = GPIOC;
    led.pin = 13;
    led.mode = OUTPUT_MODE;
    led.type = 0;
    led.speed = LOW_SPEED;
    led.pull = 0;

    gpio_init(led);

    while (1)
    {
        gpio_pin_toggle(led.port, led.pin);
        for (volatile int i = 0; i < 1000000; i++)
            ;
    }

    return 0;
}