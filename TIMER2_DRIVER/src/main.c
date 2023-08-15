#include "GPIO.h"
#include "TIMER.h"
#include "UART.h"
#include "stm32f4xx.h"

void led_pin_init(void)
{
    GPIO_TYPE portc;

    portc.port = GPIOC;
    portc.pin = 13;
    portc.mode = OUTPUT_MODE;
    portc.type = OUTPUT_PUSH_PULL;
    portc.speed = HIGH_SPEED;
    portc.pull = NO_PU_PD;

    gpio_init(portc);
}

int main(void)
{
    led_pin_init();

    uart_init(UART2, INTERNAL_CLOCK, BAUD115200, TX_ENABLE, RX_DISABLE);

    // enable timer 2 clock on APB1 bus
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    TIM2->CNT = 0;
    TIM2->PSC = 1600 - 1;
    TIM2->ARR = 10000 - 1;

    TIM2->CR1 |= TIM_CR1_CEN;

    while (1)
    {
        while (!(TIM2->SR & TIM_SR_UIF))
        {
            LOG("Timer count is : %d\n", TIM2->CNT);
        }
        TIM2->SR &= ~(TIM_SR_UIF);
        gpio_pin_toggle(GPIOC, 13);
    }

    return 0;
}