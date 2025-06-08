//
// Created by dell on 6/6/2025.
//

#ifndef PWM_H
#define PWM_H
// for channel 1
#define TIM_CCMR1_OC1M_Pos 4U
#define TIM_CCMR1_OC1M_Msk (0x7 << TIM_CCMR1_OC1M_Pos)  // mask for bits 6:4
#define TIM_CCMR1_OC1M     TIM_CCMR1_OC1M_Msk
#define TIM_CCMR1_OC1PE (1 << 3)   // bit 3
#define TIM_CCER_CC1E         (1 << 0)   // Enable output for channel 1


// For Channel 2
#define TIM_CCMR1_OC2M_Pos    12
#define TIM_CCMR1_OC2M        (0xf<< TIM_CCMR1_OC2M_Pos)
#define TIM_CCMR1_OC2PE       (1 << 11)
#define TIM_CCER_CC2E         (1 << 4)   // Enable output for channel 2


// TIMx_CR1 Register Bit Definitions
#define TIM_CR1_CEN     (1 << 0)   // Counter enable
#define TIM_CR1_ARPE    (1 << 7)   // Auto-reload preload enable

// TIMx_EGR Register Bit Definitions
#define TIM_EGR_UG      (1 << 0)   // Update generation




#define TIM2_CH1	1   //PA0
#define TIM2_CH2	2   //PA1


void PWM_Init(const uint8 channel);
void PWM_SetDutyCycle(const uint16 duty_cycle_percent);      // Set duty cycle (0 to 100%)
void PWM_Start(void);                     // Start PWM signal
void PWM_Stop(void);

#endif //PWM_H
