//
// Created by DELL on 6/5/2025.
//

#ifndef TIMER_H
#define TIMER_H

#include "../LIB/Std_Types.h"

/* Timer channel selection */
#define TIM_CH1    1
#define TIM_CH2    2
#define TIM_CH3    3

/* Function prototypes */
void TIM_Init(uint8 channel);               // Initialize timer for input capture
uint32 TIM_GetCaptureValue(void);           // Get latest pulse width in microseconds
float TIM_GetSpeed(void);                   // Get calculated speed in m/s

#endif //TIMER_H
