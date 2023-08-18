/***********************************
 *
 *   Author : Ankit Khandeparkar
 *
 ***********************************/

#ifndef PWM_H
#define PWM_H
#include <stdint.h>

#define pin8 0x00
#define pin5 0x01

void pwm_pa8_init(void);
void pwm_pa5_init(void);
void servo_angle(int pin, int angle);

#endif /* PWM_H */
