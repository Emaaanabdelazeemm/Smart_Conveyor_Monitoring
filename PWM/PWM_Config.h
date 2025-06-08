//
// Created by dell on 6/6/2025.
//

#ifndef PWM_CONFIG_H
#define PWM_CONFIG_H

// Timer input clock frequency in Hz (usually APB1 or APB2 timer clock)
#define TIMER_CLOCK_FREQ 8000000UL  // 8M (adjust it on proteus too)

// Desired PWM frequency in Hz
#define PWM_FREQUENCY 1000U

// PWM resolution in bits (defines max ARR value)
// For example, 16 means timer counts up to 2^16 - 1 = 65535
#define PWM_RESOLUTION 16U

#define PWM_PRESCALER 2              // No prescaler, or calculate based on freq

#define PWM_DEFAULT_TIMER   TIM2

// #define AF1_PIN0 0
// #define AF1_PIN1  1
// #define AF1_PIN2 2
// #define AF1_PIN3 3
//
// #define DEFAULT_AF AF1_PIN0


#define PWM_MODE1 0x6
#define PWM_MODE2 0x7
#define PWM_MODE PWM_MODE1




#define PWM_DEFAULT_CHANNEL 1

#endif  // PWM_CONFIG_H


