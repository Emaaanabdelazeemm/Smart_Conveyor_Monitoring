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
#include "../GPIO/GPIO_private.h"
#include "../LIB/Utils.h"
#include "../LIB/Bit_Operations.h"

static uint8 CHANNEL;

void PWM_Init(const uint8 channel) {
    CHANNEL = channel;

    Rcc_Enable(RCC_TIM1);

    // Timer setup
    uint32 timer_clock = TIMER_CLOCK_FREQ / (PWM_PRESCALER + 1);
    uint32 arr = (timer_clock / PWM_FREQUENCY) - 1;

    TIM1->PSC = PWM_PRESCALER;
    TIM1->ARR = arr;

    // Enable GPIO and configure corresponding pin for each channel
    switch (channel) {
        case 1: // TIM1_CH1 -> PA8
            Rcc_Enable(RCC_GPIOA);
            Gpio_Init(GPIO_A, 8, GPIO_AF, GPIO_PUSH_PULL);
            GPIOA_AFRH &= ~(0xF << ((8 - 8) * 4));
           GPIOA_AFRH |=  (0x1 << ((8 - 8) * 4)); // AF1
            TIM1->CCMR1 &= ~TIM_CCMR1_OC1M;
            TIM1->CCMR1 |= (PWM_MODE << TIM_CCMR1_OC1M_Pos);
            TIM1->CCMR1 |= TIM_CCMR1_OC1PE;
            TIM1->CCER  |= TIM_CCER_CC1E;
            break;

        case 2: // TIM1_CH2 -> PA9
            Rcc_Enable(RCC_GPIOA);
            Gpio_Init(GPIO_A, 9, GPIO_AF, GPIO_PUSH_PULL);
           GPIOA_AFRH &= ~(0xF << ((9 - 8) * 4));
            GPIOA_AFRH|=  (0x1 << ((9 - 8) * 4)); // AF1
            TIM1->CCMR1 &= ~TIM_CCMR1_OC2M;
            TIM1->CCMR1 |= (PWM_MODE << TIM_CCMR1_OC2M_Pos);
            TIM1->CCMR1 |= TIM_CCMR1_OC2PE;
            TIM1->CCER  |= TIM_CCER_CC2E;
            break;

        case 3: // TIM1_CH3 -> PA10
            Rcc_Enable(RCC_GPIOA);
            Gpio_Init(GPIO_A, 10, GPIO_AF, GPIO_PUSH_PULL);
            GPIOA_AFRH &= ~(0xF << ((10 - 8) * 4));
            GPIOA_AFRH |=  (0x1 << ((10 - 8) * 4)); // AF1
            TIM1->CCMR2 &= ~TIM_CCMR2_OC3M;
            TIM1->CCMR2 |= (PWM_MODE << TIM_CCMR2_OC3M_Pos);
            TIM1->CCMR2 |= TIM_CCMR2_OC3PE;
            TIM1->CCER  |= TIM_CCER_CC3E;
            break;

        case 4: // TIM1_CH4 -> PA11
            Rcc_Enable(RCC_GPIOA);
            Gpio_Init(GPIO_A, 11, GPIO_AF, GPIO_PUSH_PULL);
            GPIOA_AFRH &= ~(0xF << ((11 - 8) * 4));
            GPIOA_AFRH |=  (0x1 << ((11 - 8) * 4)); // AF1
            TIM1->CCMR2 &= ~TIM_CCMR2_OC4M;
            TIM1->CCMR2 |= (PWM_MODE << TIM_CCMR2_OC4M_Pos);
            TIM1->CCMR2 |= TIM_CCMR2_OC4PE;
            TIM1->CCER  |= TIM_CCER_CC4E;
            break;

        default:
            // Invalid channel
            return;
    }

    // Finalize timer setup
    TIM1->CR1  |= TIM_CR1_ARPE;
    TIM1->EGR  |= TIM_EGR_UG;
    TIM1->BDTR |= (1 << 15);  // MOE (Main Output Enable)
    TIM1->CR1  |= TIM_CR1_CEN;
}

void PWM_SetDutyCycle(uint16 duty_percent) {
    uint32 arr = TIM1->ARR;
    uint32 ccr_value = (duty_percent * (arr + 1)) / 100;

    switch (CHANNEL) {
        case 1: TIM1->CCR1 = ccr_value; break;
        case 2: TIM1->CCR2 = ccr_value; break;
        case 3: TIM1->CCR3 = ccr_value; break;
        case 4: TIM1->CCR4 = ccr_value; break;
        default: break;
    }
}

//     CHANNEL = channel;
//     Rcc_Enable(RCC_TIM2  );
//     uint32 timer_clock = TIMER_CLOCK_FREQ / (PWM_PRESCALER + 1);
//     uint32 arr = (timer_clock / PWM_FREQUENCY) - 1;
//
//     TIM2->PSC = PWM_PRESCALER;
//     TIM2->ARR = arr;
//     TIM2->CCR1 = 0;
//
//     if (channel == 1) {
//
//         Rcc_Enable(RCC_GPIOA);
//         GPIOA_MODER &= ~(0x03 << 0);     // Clear mode
//         GPIOA_MODER |=  (GPIO_AF  << 0);     // Set AF mode
//
//         // Set AFRL
//         // you can change the default AF1 depending on which channel
//         GPIOA_AFRL &= ~(0xf << (channel-1)*4);    // Clear
//         GPIOA_AFRL |=  (0x1 << (channel-1)*4);
//         TIM2->CCMR1 &= ~TIM_CCMR1_OC1M;
//         TIM2->CCMR1 |= (PWM_MODE << TIM_CCMR1_OC1M_Pos);
//         TIM2->CCMR1 |= TIM_CCMR1_OC1PE;
//         TIM2->CCER  |= TIM_CCER_CC1E;
//     }
//     else if (channel == 2) {
//         Rcc_Enable(RCC_GPIOA);
//         GPIOA_MODER &= ~(0x03 << 0);
//         GPIOA_MODER |=  (GPIO_AF  << 0);
//
//         GPIOA_AFRL &= ~(0xf << (channel-1)*4);
//         GPIOA_AFRL |=  (0x1 << (channel-1)*4);
//         TIM2->CCMR1 &= ~TIM_CCMR1_OC2M;
//         TIM2->CCMR1 |= (PWM_MODE << TIM_CCMR1_OC2M_Pos);
//         TIM2->CCMR1 |= TIM_CCMR1_OC2PE;
//         TIM2->CCER  |= TIM_CCER_CC2E;
//     }else if (channel == 3) {
//         // Configure PB10 for TIM2_CH3
//
//             Rcc_Enable(RCC_GPIOA);  // Enable GPIOA clock
//
//             GPIOA_MODER &= ~(0x03 << (2 * 2));  // Clear mode for PA2
//             GPIOA_MODER |=  (GPIO_AF << (2 * 2));  // Set alternate function for PA2
//
//             GPIOA_AFRL &= ~(0xF << (2 * 4));  // Clear AF for PA2
//             GPIOA_AFRL |=  (0x1 << (2 * 4));  // Set AF1 for TIM2
//
//             TIM2->CCMR2 &= ~TIM_CCMR2_OC3M;
//             TIM2->CCMR2 |= (PWM_MODE << TIM_CCMR2_OC3M_Pos);
//             TIM2->CCMR2 |= TIM_CCMR2_OC3PE;
//             TIM2->CCER  |= TIM_CCER_CC3E;
//         }
//
//
//
//
//     // Enable auto-reload preload and start
//     TIM2->CR1 |= TIM_CR1_ARPE;
//     TIM2->EGR |= TIM_EGR_UG;
//     TIM2->CR1 |= TIM_CR1_CEN;
// }
// void PWM_SetDutyCycle(const uint16 duty_cycle_percent) {
//     uint32 arr = TIM2->ARR;
//     uint32 ccr_value = (duty_cycle_percent * (arr + 1)) / 100;
//
//     if (CHANNEL == 1) {
//         TIM2->CCR1 = ccr_value;
//     }
//     else if (CHANNEL == 2) {
//         TIM2->CCR2 = ccr_value;
//     }
//     else if (CHANNEL == 3) {
//     TIM2->CCR3 = ccr_value;
//     }
//     else if (CHANNEL == 4) {
//         TIM2->CCR4 = ccr_value;
//     }
// }
//
//
//
//
//
//
//
//
//
//
