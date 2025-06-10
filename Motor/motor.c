#include "motor.h"
#include <stdio.h>
#include "../RCC/RCC.h"
#include "../GPIO/Gpio.h"
#include "../PWM/PWM.h"


/*
 * channel TIM2_CH1 --> PA0
 * channel TIM2_CH2 --> PA1
 */

#define motor_IN1_PIN 14
#define motor_IN2_PIN 15


void Init_Motor(const uint8 channel, const uint16 duty_cycle_percent)
{
    PWM_Init(2);
    PWM_SetDutyCycle(duty_cycle_percent);
}




void Set_Motor_Speed(const uint16 duty_cycle_percent)
{
    PWM_SetDutyCycle(duty_cycle_percent);
}




