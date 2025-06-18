//
// Created by DELL on 6/5/2025.
//
#include "Timer.h"
#include "Timer_Private.h"
#include "../RCC/RCC.h"
#include "../GPIO/GPIO.h"
#include <../LIB/Std_Types.h>
#include "../LIB/Utils.h"
#include "../LIB/Bit_Operations.h"

static uint32 last_capture = 0;

void TIM_Init(uint8 channel)
{
    /* 1. Enable timer clock */
    Rcc_Enable(RCC_TIM2);

    /* 2. Configure GPIO for timer input */
    Gpio_Init(GPIO_A, 0, GPIO_AF, GPIO_NO_PULL_DOWN); // PA0 as AF for TIM2_CH1

    /* 3. Configure timer base */
    TIM2_CR1 = 0x00;       // Disable timer
    TIM2_PSC = 15;         // 16MHz/16 = 1MHz (1µs resolution)
    TIM2_ARR = 0xFFFFFFFF; // Maximum count value (32 bit)


    /* 4. Configure input capture */
    if(channel == TIM_CH1) {

        TIM2_CCER |= (1 << 0);       // Set CC1E=1 (enable capture)>>> to store the counter value in TIMx_CCR1

        // Set Channel 1 to capture from TI1 (e.g., PA0 for TIM2)
        TIM2_CCMR1 &= ~(0x03U << 0);       // Clear CC1S bits
        TIM2_CCMR1 |= (TIM_IC1_SEL_TI1 << 0);  // CC1S=01 (TI1 selected)

        // Set rising edge detection for Channel 1
        TIM2_CCER &= ~(0x0AU);  // Clear CC1P (Bit 1) and CC1NP (Bit 3)
        TIM2_CCER |= TIM_IC_EDGE_RISING;  // Not strictly needed (just 0x00)


    }
    if(channel == TIM_CH2) {

        TIM2_CCER |= (1 << 0);       // Set CC1E=1 (enable capture)>>> to store the counter value in TIMx_CCR1

        // Set Channel 1 to capture from TI1 (e.g., PA0 for TIM2)
        TIM2_CCMR1 &= ~(0x03U << 8);       // Clear CC1S bits
        TIM2_CCMR1 |= (TIM_IC1_SEL_TI1 << 8);  // CC1S=01 (TI1 selected)

        // Set rising edge detection for Channel 1
        TIM2_CCER &= ~(0x0AU << 4);  // Clear CC1P (Bit 1) and CC1NP (Bit 3)
        TIM2_CCER |= (TIM_IC_EDGE_RISING << 4);  // Not strictly needed (just 0x00)


    }


    /* 5. Enable timer */
    TIM2_CR1 |= (1 << 0);  // Counter enable
}

uint32 TIM_GetCaptureValue(void)
{
    if(TIM2_SR & (1 << 1)) // Check capture flag for channel 1
    {
        uint32 pulse_width;
        uint32 current_capture = TIM2_CCR1;
        if (current_capture < last_capture) {
            pulse_width =  (TIM2_ARR - last_capture) + current_capture + 1 ;
        }
        else {
            pulse_width = current_capture - last_capture;
        }
        last_capture = current_capture;
        TIM2_SR &= ~(1 << 1); // Clear flag
        return pulse_width;    // Returns microseconds
    }
    return 0;
}

float TIM_GetSpeed(void)
{
    uint32 pulse_width = TIM_GetCaptureValue();
    if(pulse_width == 0) return 0.0f;

    // Calculate speed: (distance per pulse) / (time per pulse)
    return 1 / (pulse_width * 1e-6f); // m/s
}
