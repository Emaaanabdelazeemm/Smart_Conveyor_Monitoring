//
// Created by dell on 6/6/2025.
//

#include "../LIB/Std_Types.h"
#include "../GPIO/GPIO.h"
#include "PWM.h"
#include"PWM_PRIVATE.h"
#include "PWM_Config.h"
#include "../RCC/RCC.h"
#include "../GPIO/GPIO.h"
#include "../LIB/Utils.h"
#include "../LIB/Bit_Operations.h"

#define GPIOA_BASE_ADDR 	0x40020000
#define GPIOA_MODER			REG32(GPIOA_BASE_ADDR + 0x00)
#define GPIOA_AFRL			REG32(GPIOA_BASE_ADDR + 0x20)

static uint8 CHANNEL;

void PWM_Init(const uint8 channel)
{

    CHANNEL = channel;

    Rcc_Enable(RCC_TIM2  );
    Rcc_Enable(RCC_GPIOA);

    GPIOA_MODER &= ~(0x03 << 0);     // Clear mode
    GPIOA_MODER |=  (GPIO_AF  << 0);     // Set AF mode

    // Set AFRL
    // you can change the default AF1 depending on which channel
    GPIOA_AFRL &= ~(0xf << (channel-1)*4);    // Clear
    GPIOA_AFRL |=  (0x1 << (channel-1)*4);
    uint32 timer_clock = TIMER_CLOCK_FREQ / (PWM_PRESCALER + 1);
    uint32 arr = (timer_clock / PWM_FREQUENCY) - 1;

    TIM2->PSC = PWM_PRESCALER;
    TIM2->ARR = arr;
    TIM2->CCR1 = 0;

    if (channel == 1) {
        TIM2->CCMR1 &= ~TIM_CCMR1_OC1M;
        TIM2->CCMR1 |= (PWM_MODE << TIM_CCMR1_OC1M_Pos);                // Set PWM mode
        TIM2->CCMR1 |= TIM_CCMR1_OC1PE;                                 // Enable preload for CCR1
        TIM2->CCER  |= TIM_CCER_CC1E;                                   // Enable output on channel 1
    }
    else if (channel == 2) {
        TIM2->CCMR1 &= ~TIM_CCMR1_OC2M;
        TIM2->CCMR1 |= (PWM_MODE << TIM_CCMR1_OC2M_Pos);                // Set PWM mode
        TIM2->CCMR1 |= TIM_CCMR1_OC2PE;                                 // Enable preload for CCR2
        TIM2->CCER  |= TIM_CCER_CC2E;                                   // Enable output on channel 2
    }



    // Enable auto-reload preload and start
    TIM2->CR1 |= TIM_CR1_ARPE;
    TIM2->EGR |= TIM_EGR_UG;
    TIM2->CR1 |= TIM_CR1_CEN;
}

void PWM_SetDutyCycle(const uint16 duty_cycle_percent) {
    uint32 arr = TIM2->ARR;
    uint32 ccr_value = (duty_cycle_percent * (arr + 1)) / 100;

    if (CHANNEL == 1) {
        TIM2->CCR1 = ccr_value;
    } else if (CHANNEL == 2) {
        TIM2->CCR2 = ccr_value;
    }
}
void PWM_Start(void) {
    TIM2->CR1 |= TIM_CR1_CEN;
}

void PWM_Stop(void) {
    TIM2->CR1 &= ~TIM_CR1_CEN;
}








