#include "motor.h"
#include <stdio.h>
#include "../RCC/RCC.h"
#include "../GPIO/Gpio.h"
#include "../PWM/PWM.h"


/*
 * channel TIM1_CH1 --> PA8
 * channel TIM1_CH2 --> PA9
 */
void Init_Motor(const uint8 channel, const uint16 duty_cycle_percent)
{
    PWM_Init(channel);
    PWM_SetDutyCycle(duty_cycle_percent);
}


void Set_Motor_Speed(const uint16 duty_cycle_percent)
{
    PWM_SetDutyCycle(duty_cycle_percent);
}




