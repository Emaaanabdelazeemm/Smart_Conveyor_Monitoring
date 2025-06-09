//
// Created by DELL on 6/6/2025.
//

#ifndef TIMER_PRIVATE_H
#define TIMER_PRIVATE_H
#include "../LIB/Std_Types.h"

/* Timer 2 base address and registers */
#define TIM2_BASE       0x40000000
#define TIM2_CR1        REG32(TIM2_BASE + 0x00)
#define TIM2_CCMR1      REG32(TIM2_BASE + 0x18)
#define TIM2_CCER       REG32(TIM2_BASE + 0x20)
#define TIM2_CNT        REG32(TIM2_BASE + 0x24)
#define TIM2_PSC        REG32(TIM2_BASE + 0x28)
#define TIM2_ARR        REG32(TIM2_BASE + 0x2C)
#define TIM2_CCR1       REG32(TIM2_BASE + 0x34)
#define TIM2_CCR2       REG32(TIM2_BASE + 0x38)
#define TIM2_SR         REG32(TIM2_BASE + 0x10)

/* Timer 3 base address and registers */
#define TIM3_BASE       0x40000400
#define TIM3_CR1        REG32(TIM3_BASE + 0x00)
#define TIM3_CCMR1      REG32(TIM3_BASE + 0x18)
#define TIM3_CCER       REG32(TIM3_BASE + 0x20)
#define TIM3_CNT        REG32(TIM3_BASE + 0x24)
#define TIM3_PSC        REG32(TIM3_BASE + 0x28)
#define TIM3_ARR        REG32(TIM3_BASE + 0x2C)
#define TIM3_CCR1       REG32(TIM3_BASE + 0x34)
#define TIM3_CCR2       REG32(TIM3_BASE + 0x38)
#define TIM3_SR         REG32(TIM3_BASE + 0x10)

// Input capture channel selection (CC1S bits in TIMx_CCMR1)
#define TIM_IC1_SEL_TI1     (0x01U)  // CC1S=01: TI1 (e.g., PA0 for TIM2)
#define TIM_IC1_SEL_TI2     (0x02U)  // CC1S=10: TI2 (e.g., PA1 for TIM2)

// Input capture edge selection (CC1P/CC1NP bits in TIMx_CCER)
#define TIM_IC_EDGE_RISING  (0x00U)  // CC1P=0, CC1NP=0 (rising edge)
#define TIM_IC_EDGE_FALLING (0x02U)  // CC1P=1, CC1NP=0 (falling edge)
#define TIM_IC_EDGE_BOTH    (0x0AU)  // CC1P=1, CC1NP=1 (both edges)

#endif //TIMER_PRIVATE_H
