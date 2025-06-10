//
// Created by dell on 6/6/2025.
//

#ifndef PWM_PRIVATE_H
#define PWM_PRIVATE_H
#include "../LIB/Std_Types.h"

#define TIM1_BASE   0x40010000UL
#define TIM2_BASE   0x40000000UL
#define TIM3_BASE   0x40000400UL
#define TIM4_BASE   0x40000800UL
#define TIM5_BASE   0x40000C00UL

typedef struct {
    volatile uint32 CR1;      // 0x00
    volatile uint32 CR2;      // 0x04
    volatile uint32 SMCR;     // 0x08
    volatile uint32 DIER;     // 0x0C
    volatile uint32 SR;       // 0x10
    volatile uint32 EGR;      // 0x14
    volatile uint32 CCMR1;    // 0x18
    volatile uint32 CCMR2;    // 0x1C
    volatile uint32 CCER;     // 0x20
    volatile uint32 CNT;      // 0x24
    volatile uint32 PSC;      // 0x28
    volatile uint32 ARR;      // 0x2C
    volatile uint32 RESERVED1; // 0x30
    volatile uint32 CCR1;     // 0x34
    volatile uint32 CCR2;     // 0x38
    volatile uint32 CCR3;     // 0x3C
    volatile uint32 CCR4;     // 0x40
    volatile uint32 BDTR;     // 0x44
    volatile uint32 DCR;      // 0x48
    volatile uint32 DMAR;     // 0x4C
} TIM_TypeDef;

// Create pointers to each timer

#define TIM1   ((TIM_TypeDef *)TIM1_BASE)
#define TIM2   ((TIM_TypeDef *)TIM2_BASE)
#define TIM3   ((TIM_TypeDef *)TIM3_BASE)
#define TIM4   ((TIM_TypeDef *)TIM4_BASE)
#define TIM5   ((TIM_TypeDef *)TIM5_BASE)


#endif //PWM_PRIVATE_H
