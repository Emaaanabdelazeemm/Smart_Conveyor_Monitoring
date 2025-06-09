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


static uint8 CHANNEL;

void PWM_Init(const uint8 channel)
{

    CHANNEL = channel;

    Rcc_Enable(RCC_TIM2  );
    Rcc_Enable(RCC_GPIOA);


    uint32 timer_clock = TIMER_CLOCK_FREQ / (PWM_PRESCALER + 1);
    uint32 arr = (timer_clock / PWM_FREQUENCY) - 1;

    TIM2->PSC = PWM_PRESCALER;
    TIM2->ARR = arr;
    TIM2->CCR1 = 0;

    if (channel == 1) {
        GPIOA_MODER &= ~(0x03 << 0);     // Clear mode
        GPIOA_MODER |=  (GPIO_AF  << 0);     // Set AF mode

        // Set AFRL
        // you can change the default AF1 depending on which channel
        GPIOA_AFRL &= ~(0xf << (channel-1)*4);    // Clear
        GPIOA_AFRL |=  (0x1 << (channel-1)*4);
        TIM2->CCMR1 &= ~TIM_CCMR1_OC1M;
        TIM2->CCMR1 |= (PWM_MODE << TIM_CCMR1_OC1M_Pos);
        TIM2->CCMR1 |= TIM_CCMR1_OC1PE;
        TIM2->CCER  |= TIM_CCER_CC1E;
    }
    else if (channel == 2) {
        GPIOA_MODER &= ~(0x03 << 0);
        GPIOA_MODER |=  (GPIO_AF  << 0);

        GPIOA_AFRL &= ~(0xf << (channel-1)*4);
        GPIOA_AFRL |=  (0x1 << (channel-1)*4);
        TIM2->CCMR1 &= ~TIM_CCMR1_OC2M;
        TIM2->CCMR1 |= (PWM_MODE << TIM_CCMR1_OC2M_Pos);
        TIM2->CCMR1 |= TIM_CCMR1_OC2PE;
        TIM2->CCER  |= TIM_CCER_CC2E;
    }else if (channel == 3) {
        // Configure PB10 for TIM2_CH3
        Rcc_Enable(RCC_GPIOB);  // Enable GPIOB clock

        GPIOB_MODER &= ~(0x03 << (10 * 2));
        GPIOB_MODER |=  (GPIO_AF << (10 * 2));

        GPIOB_AFRH  &= ~(0xF << ((10 - 8) * 4));
        GPIOB_AFRH  |=  (0x1 << ((10 - 8) * 4)); // AF1
        TIM2->CCMR2 &= ~TIM_CCMR2_OC3M;
        TIM2->CCMR2 |= (PWM_MODE << TIM_CCMR2_OC3M_Pos);
        TIM2->CCMR2 |= TIM_CCMR2_OC3PE;
        TIM2->CCER  |= TIM_CCER_CC3E;
    }
    else if (channel == 4) {
        // Configure PB11 for TIM2_CH4
        Rcc_Enable(RCC_GPIOB);  // Enable GPIOB clock

        GPIOB_MODER &= ~(0x03 << (11 * 2));
        GPIOB_MODER |=  (GPIO_AF << (11 * 2));

        GPIOB_AFRH  &= ~(0xF << ((11 - 8) * 4));
        GPIOB_AFRH  |=  (0x1 << ((11 - 8) * 4)); // AF1
        TIM2->CCMR2 &= ~TIM_CCMR2_OC4M;
        TIM2->CCMR2 |= (PWM_MODE << TIM_CCMR2_OC4M_Pos);
        TIM2->CCMR2 |= TIM_CCMR2_OC4PE;
        TIM2->CCER  |= TIM_CCER_CC4E;
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
    }
    else if (CHANNEL == 2) {
        TIM2->CCR2 = ccr_value;
    }
    else if (CHANNEL == 3) {
        TIM2->CCR3 = ccr_value;
    }
    else if (CHANNEL == 4) {
        TIM2->CCR4 = ccr_value;
    }
}

void PWM_Start(void) {
    TIM2->CR1 |= TIM_CR1_CEN;
}

void PWM_Stop(void) {
    TIM2->CR1 &= ~TIM_CR1_CEN;
}








