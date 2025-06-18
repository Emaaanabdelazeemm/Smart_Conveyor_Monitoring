
#include "../LIB/Std_Types.h"
#include "../GPIO/GPIO.h"
#include "ADC.h"
#include"ADC_Private.h"
#include "../RCC/RCC.h"
#include"ADC_Config.h"

void ADC_INIT(uint8 PORT , uint8 PIN , uint8 CHANNEL) {
    Gpio_Init(PORT, PIN , GPIO_ANALOG , GPIO_NO_PULL_DOWN);

    Rcc_Enable(RCC_ADC1);

    // ADC PRESCALER
    ADC_COMMON->CCR &= ~(0x3 << 16);  // Clear prescaler bits
    ADC_COMMON->CCR |=  (ADC_PRESCALER << 16);  // Set to ÷2 (fastest)


    //ADC RESOLUTION
    ADC1->CR1 &= ~(0x3 << 24);
    ADC1->CR1 |=  (ADC_RESOLUTION  << 24);

    // Enable ADC by set ADON bit in ADC_CR2
    ADC1->CR2 = 0;
    ADC1->CR2 |= (1 << 0);

    //  continous =1 , single =0
    ADC1->CR2 &= ~(1 << CONT_BIT_POS);   // Single conversion mode
    ADC1->CR2 |= (1 << EOC_BIT_POS);   // flag after each


    // sampling rate
    if (CHANNEL <= 9) {
        ADC1->SMPR2 &= ~(0x7 << (CHANNEL * 3));
        ADC1->SMPR2 |=  (SAMPLING_RATE << (CHANNEL * 3));

    } else {
        ADC1->SMPR1 &= ~(0x7 << ((CHANNEL - 10) * 3));
        ADC1->SMPR1 |=  (SAMPLING_RATE << ((CHANNEL - 10) * 3));
    }

    // length in ADC_SQR1 register
    ADC1->SQR1 &= ~(0xF << LENGTH_BIT_POS);
    ADC1->SQR1 |= (ONE_CONVERSION << LENGTH_BIT_POS);

    // Set channel in SQ1
    ADC1->SQR3 &= ~0x1F;
    ADC1->SQR3 |= CHANNEL;
}

uint16 ADC_CONVERSION() {

    ADC1->CR2 |= (1 << 30);            // SWSTART = 1 to begin conversion

    while (!(ADC1->SR & (1 << 1)));    // // Wait for EOC

    return ADC1->DR;                   // Read result and automatically clear EOC
}

