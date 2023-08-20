/***********************************
 *
 *   Author : Ankit Khandeparkar
 *
 ***********************************/
#include "GPIO.h"
#include "UART.h"
#include "clock.h"
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
    init_clock();

    uart_init(UART2, EXTERNAL_CLOCK, BAUD115200, TX_ENABLE, RX_ENABLE);

    led_pin_init();

    // enable timer 2 one second delay
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // SETUP TIMER PSC, ARR AND SET CNT = 0
    TIM2->PSC = 9600;
    TIM2->ARR = 10000;
    TIM2->CNT = 0;

    TIM2->CR1 |= TIM_CR1_CEN;

    while (1)
    {
        while (!(TIM2->SR & TIM_SR_UIF))
            ;
        TIM2->SR &= ~(TIM_SR_UIF);
        LOG("ONE SECOND DONE !\n");
        gpio_pin_toggle(GPIOC, 13);
    }

    return 0;
}