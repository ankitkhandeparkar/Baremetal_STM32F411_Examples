#include "LED.h"
#include "Systick.h"
#include "stm32f4xx.h"
#define clock 16000000UL // Clock Frequency of the AHB
#define delay 500UL      // Delay in milliseconds

int main(void)
{
    LED_init();                 // Initialize LED of the microcontroller PC13
    SysTick_init(clock, delay); // Initialize the SysTick Timer with clock and delay(milliseconds)

    while (1)
    {
        if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)
        {
            LED_toggle();
        }
    }

    return 0;
}