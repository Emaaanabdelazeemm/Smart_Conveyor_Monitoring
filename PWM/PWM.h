#ifndef PWM_H
#define PWM_H

// Channel Selection
#define TIM2_CH1    1   // PA0
#define TIM2_CH2    2   // PA1
#define TIM2_CH3    3
#define TIM2_CH4    4


#define TIM1_CH1    1
#define TIM1_CH2    2
#define TIM1_CH3    3
#define TIM1_CH4    4

// ================= Channel 1 (CCMR1, OC1) =================
#define TIM_CCMR1_OC1M_Pos     4U
#define TIM_CCMR1_OC1M_Msk     (0x7 << TIM_CCMR1_OC1M_Pos)
#define TIM_CCMR1_OC1M         TIM_CCMR1_OC1M_Msk
#define TIM_CCMR1_OC1PE        (1 << 3)
#define TIM_CCER_CC1E          (1 << 0)

// ================= Channel 2 (CCMR1, OC2) =================
#define TIM_CCMR1_OC2M_Pos     12
#define TIM_CCMR1_OC2M         (0x7 << TIM_CCMR1_OC2M_Pos)
#define TIM_CCMR1_OC2PE        (1 << 11)
#define TIM_CCER_CC2E          (1 << 4)

// ================= Channel 3 (CCMR2, OC3) =================
#define TIM_CCMR2_OC3M_Pos     4
#define TIM_CCMR2_OC3M         (0x7 << TIM_CCMR2_OC3M_Pos)
#define TIM_CCMR2_OC3PE        (1 << 3)
#define TIM_CCER_CC3E          (1 << 8)

// ================= Channel 4 (CCMR2, OC4) =================
#define TIM_CCMR2_OC4M_Pos     12
#define TIM_CCMR2_OC4M         (0x7 << TIM_CCMR2_OC4M_Pos)
#define TIM_CCMR2_OC4PE        (1 << 11)
#define TIM_CCER_CC4E          (1 << 12)

// ========== TIMx Control Bits ==========
// TIMx_CR1 Register Bit Definitions
#define TIM_CR1_CEN            (1 << 0)    // Counter enable
#define TIM_CR1_ARPE           (1 << 7)    // Auto-reload preload enable

// TIMx_EGR Register Bit Definitions
#define TIM_EGR_UG             (1 << 0)    // Update generation

// ========== Public API ==========

void PWM_Init(const uint8 channel);
void PWM_SetDutyCycle(const uint16 duty_cycle_percent); // 0 - 100%


#endif // PWM_H
