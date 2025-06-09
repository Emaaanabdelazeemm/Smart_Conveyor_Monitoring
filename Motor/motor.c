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
    PWM_Init(1);
    PWM_SetDutyCycle(duty_cycle_percent);
}

void Start_Motor()
{
    PWM_Start();
}

void Stop_Motor()
{
    PWM_Stop();

    Gpio_Init(GPIO_B, 10, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_WritePin(GPIO_B, 10, LOW);  // Both LOW = coast/stop

    Gpio_WritePin(GPIO_A, motor_IN1_PIN, LOW);
    Gpio_WritePin(GPIO_A, motor_IN2_PIN, LOW);  // Both LOW = coast/stop
}

void Set_Motor_Speed(const uint16 duty_cycle_percent)
{
    PWM_SetDutyCycle(duty_cycle_percent);
}




