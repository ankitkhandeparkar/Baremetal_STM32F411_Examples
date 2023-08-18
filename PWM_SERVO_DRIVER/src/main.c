/***********************************
 *
 *   Author : Ankit Khandeparkar
 *
 ***********************************/
#include "PWM.h"
#include "stm32f4xx.h"

int main(void)
{
    pwm_pa5_init();

    while (1)
    {
        TIM2->CCR1 = 300;
        for (volatile int i = 0; i < 900000; i++)
            ;
        // servo_angle(pin5, 180);
        TIM2->CCR1 = 7000;
        for (volatile int i = 0; i < 900000; i++)
            ;
    }

    return 0;
}