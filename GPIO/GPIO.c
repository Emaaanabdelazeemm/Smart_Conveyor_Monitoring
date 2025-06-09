
#include <../LIB/Std_Types.h>
#include "GPIO.h"
#include "../LIB/Utils.h"
#include "../LIB/Bit_Operations.h"
#include "GPIO_Private.h"

void Gpio_Init(uint8 PortName, uint8 PinNumber, uint8 PinMode, uint8 DefaultState) {
    switch (PortName) {
        case GPIO_A:
        	GPIOA_MODER &= ~(0x03 << (PinNumber * 2));
			GPIOA_MODER |= (PinMode << (PinNumber * 2));

    	if (PinMode == GPIO_INPUT) {
    		GPIOA_PUPDR &= ~(0x03 << (PinNumber * 2));
    		GPIOA_PUPDR |= (DefaultState << (PinNumber * 2));
    	}
    	else if (PinMode == GPIO_OUTPUT) {
    		GPIOA_OTYPER &= ~(0x1 << PinNumber);
    		GPIOA_OTYPER |= (DefaultState << PinNumber);
    	}
    	else if (PinMode == GPIO_AF) {
    		// Configure Alternate Function (AF01 for TIM2_CH1)
    		if(PinNumber < 8) {
    			GPIOA_AFRL &= ~(0xF << (PinNumber * 4)); // Clear AF bits
    			GPIOA_AFRL |= (1 << (PinNumber * 4));    // AF01 for TIM2_CH1

    		} else {
    			GPIOA_AFRH &= ~(0xF << ((PinNumber-8) * 4));
    			GPIOA_AFRH |= (1 << ((PinNumber-8) * 4));
    		}
    	}
    	break;

        case GPIO_B:
            GPIOB_MODER &= ~(0x03 << (PinNumber * 2));
            GPIOB_MODER |= (PinMode << (PinNumber * 2));

            if (PinMode == GPIO_INPUT) {
                GPIOB_PUPDR &= ~(0x03 << (PinNumber * 2));
                GPIOB_PUPDR |= (DefaultState << (PinNumber * 2));
            }
    		else if (PinMode == GPIO_OUTPUT) {
                GPIOB_OTYPER  &=~(0x1 << PinNumber);
                GPIOB_OTYPER  |= (DefaultState << (PinNumber));
            }
    		else if (PinMode == GPIO_AF) {
    			// Configure Alternate Function (AF01 for TIM2_CH1)
    			if(PinNumber < 8) {
    				GPIOB_AFRL &= ~(0xF << (PinNumber * 4)); // Clear AF bits
    				GPIOB_AFRL |= (1 << (PinNumber * 4));    // AF01 for TIM2_CH1
    			} else {
    				GPIOB_AFRH &= ~(0xF << ((PinNumber-8) * 4));
    				GPIOB_AFRH |= (1 << ((PinNumber-8) * 4));
    			}
    		}
            break;

        case GPIO_C:
        	GPIOC_MODER &= ~(0x03 << (PinNumber * 2));
			GPIOC_MODER |= (PinMode << (PinNumber * 2));

			if (PinMode == GPIO_INPUT) {
				GPIOC_PUPDR &= ~(0x03 << (PinNumber * 2));
				GPIOC_PUPDR |= (DefaultState << (PinNumber * 2));
			}
			else if (PinMode == GPIO_OUTPUT) {
				GPIOC_OTYPER  &=~(0x1 << PinNumber);
				GPIOC_OTYPER  |= (DefaultState << (PinNumber));
			}
			else if (PinMode == GPIO_AF) {
				// Configure Alternate Function (AF01 for TIM2_CH1)
				if(PinNumber < 8) {
					GPIOC_AFRL &= ~(0xF << (PinNumber * 4)); // Clear AF bits
					GPIOC_AFRL |= (1 << (PinNumber * 4));    // AF01 for TIM2_CH1
				} else {
					GPIOC_AFRH &= ~(0xF << ((PinNumber-8) * 4));
					GPIOC_AFRH |= (1 << ((PinNumber-8) * 4));
				}
			}
        	break;

        case GPIO_D:
        	GPIOD_MODER &= ~(0x03 << (PinNumber * 2));
        	GPIOD_MODER |= (PinMode << (PinNumber * 2));

        	if(PinMode == GPIO_INPUT){
        		GPIOD_PUPDR &= ~(0x03 << (PinNumber * 2));
        		GPIOD_PUPDR |= (DefaultState << (PinNumber * 2));
        	}else{
        		GPIOD_OTYPER &= ~(0x01 << PinNumber);
        		GPIOD_OTYPER |= (DefaultState << PinNumber);
        	}

            break;

        default:
            break;
    }

}

uint8 Gpio_WritePin(uint8 PortName, uint8 PinNumber, uint8 Data) {
    // TODO: check if pin number on port is input or output
    // if input return NOK
    // else do the action
	uint8 mode;
	switch (PortName) {
		case GPIO_A:
			mode = (((GPIOA_MODER) >> (PinNumber * 2)) & 0x03);
			break;

		case GPIO_B:
			mode = (((GPIOB_MODER) >> (PinNumber * 2)) & 0x03);
			break;

		case GPIO_C:
			mode = (((GPIOC_MODER) >> (PinNumber * 2)) & 0x03);
			break;

		case GPIO_D:
			mode = (((GPIOD_MODER) >> (PinNumber * 2)) & 0x03);
			break;

		default:
			break;
	}

	if(mode == GPIO_INPUT){
		return NOK;
	}

    switch (PortName) {
        case GPIO_A:
            GPIOA_ODR &= ~(0x1 << PinNumber);
        	GPIOA_ODR |= (Data << PinNumber);
            break;

        case GPIO_B:
            GPIOB_ODR  &=~(0x1 << PinNumber);
            GPIOB_ODR |= (Data << PinNumber);
            break;

        case GPIO_C:
        	GPIOC_ODR  &=~(0x1 << PinNumber);
        	GPIOC_ODR |= (Data << PinNumber);
            break;

        case GPIO_D:
        	GPIOD_ODR  &=~(0x1 << PinNumber);
        	GPIOD_ODR |= (Data << PinNumber);
            break;

        default:
            break;
    }
    return OK;
}


uint8 Gpio_ReadPin(uint8 PortName, uint8 PinNumber){
	uint8 pin_value;
    switch (PortName) {
        case GPIO_A:
        	pin_value = READ_BIT(GPIOA_IDR, PinNumber);
            break;

        case GPIO_B:
        	pin_value = READ_BIT(GPIOB_IDR, PinNumber);
        	break;

        case GPIO_C:
        	pin_value = READ_BIT(GPIOC_IDR, PinNumber);
            break;

        case GPIO_D:
        	pin_value = READ_BIT(GPIOD_IDR, PinNumber);
            break;

        default:
            break;
    }
    return pin_value;
}





