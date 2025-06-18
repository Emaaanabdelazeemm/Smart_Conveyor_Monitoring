
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
    uint32 arr = (timer_clock / PWM_FREQUENCY) - 1;  // counts from 0 to ARR

    TIM1->PSC = PWM_PRESCALER;
    TIM1->ARR = arr;

    switch (channel) {
        case 1: // TIM1_CH1 -> PA8
            Rcc_Enable(RCC_GPIOA);
            Gpio_Init(GPIO_A, 8, GPIO_AF, GPIO_PUSH_PULL);
            GPIOA_AFRH &= ~(0xF << ((8 - 8) * 4));
            GPIOA_AFRH |=  (AF1 << ((8 - 8) * 4)); // AF1 for th specific pin
            TIM1->CCMR1 &= ~TIM_CCMR1_OC1M;
            TIM1->CCMR1 |= (PWM_MODE << TIM_CCMR1_OC1M_Pos);
            TIM1->CCMR1 |= TIM_CCMR1_OC1PE;  // enable the preload feature ( save the new value in buffer and use it at the start of new PWM cycle)
            TIM1->CCER  |= TIM_CCER_CC1E;  //Capture compare enable ( enable  pwm output to the pin)
            break;

        case 2: // TIM1_CH2 -> PA9
            Rcc_Enable(RCC_GPIOA);
            Gpio_Init(GPIO_A, 9, GPIO_AF, GPIO_PUSH_PULL);
           GPIOA_AFRH &= ~(0xF << ((9 - 8) * 4)); //AFRH maps from pin 8 to 15
            GPIOA_AFRH|=  (AF1 << ((9 - 8) * 4)); // AF1 = 0001 AF1 for th specific pin
            TIM1->CCMR1 &= ~TIM_CCMR1_OC2M;
            TIM1->CCMR1 |= (PWM_MODE << TIM_CCMR1_OC2M_Pos);
            TIM1->CCMR1 |= TIM_CCMR1_OC2PE;
            TIM1->CCER  |= TIM_CCER_CC2E; //Capture compare enable ( enable  pwm output to the pin)
            break;

        case 3: // TIM1_CH3 -> PA10
            Rcc_Enable(RCC_GPIOA);
            Gpio_Init(GPIO_A, 10, GPIO_AF, GPIO_PUSH_PULL);
            GPIOA_AFRH &= ~(0xF << ((10 - 8) * 4));
            GPIOA_AFRH |=  (AF1 << ((10 - 8) * 4)); // AF1 for th specific pin
            TIM1->CCMR2 &= ~TIM_CCMR2_OC3M;
            TIM1->CCMR2 |= (PWM_MODE << TIM_CCMR2_OC3M_Pos);
            TIM1->CCMR2 |= TIM_CCMR2_OC3PE;
            TIM1->CCER  |= TIM_CCER_CC3E;
            break;

        case 4: // TIM1_CH4 -> PA11
            Rcc_Enable(RCC_GPIOA);
            Gpio_Init(GPIO_A, 11, GPIO_AF, GPIO_PUSH_PULL);
            GPIOA_AFRH &= ~(0xF << ((11 - 8) * 4));
            GPIOA_AFRH |=  (AF1 << ((11 - 8) * 4)); // AF1 for th specific pin
            TIM1->CCMR2 &= ~TIM_CCMR2_OC4M;
            TIM1->CCMR2 |= (PWM_MODE << TIM_CCMR2_OC4M_Pos);
            TIM1->CCMR2 |= TIM_CCMR2_OC4PE;
            TIM1->CCER  |= TIM_CCER_CC4E;
            break;

        default:
            // Invalid channel
            return;
    }


    TIM1->CR1  |= TIM_CR1_ARPE; //  Enable auto-reload preload ( save the new value into buffer untill the end (update event happens)
    TIM1->EGR  |= TIM_EGR_UG; // force update event (loads the new values arr , prescaler.)
    TIM1->BDTR |= (1 << 15);  //main output enable (entire timer's output system)
    TIM1->CR1  |= TIM_CR1_CEN; //  Start the Timer , Makes the timer count from 0 to ARR
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


