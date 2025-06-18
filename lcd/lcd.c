//
// Created by shahd 7 on 6/3/2025.
//

#include "lcd.h"
#include "../RCC/RCC.h"
#include "../Gpio/GPIO.h"

void LCD_Init(void) {
    // Enable clock for GPIO ports
    Rcc_Enable(RCC_GPIOA);  // Control port
    Rcc_Enable(RCC_GPIOB);  // Data port

    // Initialize control pins as output
    Gpio_Init(LCD_CTRL_PORT, LCD_RS_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_Init(LCD_CTRL_PORT, LCD_EN_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);

    // Initialize data pins as output
    Gpio_Init(LCD_DATA_PORT, LCD_D4_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_Init(LCD_DATA_PORT, LCD_D5_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_Init(LCD_DATA_PORT, LCD_D6_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_Init(LCD_DATA_PORT, LCD_D7_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);

    // Set initial states
    Gpio_WritePin(LCD_CTRL_PORT, LCD_RS_PIN, LOW);  // Command mode
    Gpio_WritePin(LCD_CTRL_PORT, LCD_EN_PIN, LOW);  // Enable low

    // LCD initialization sequence (4-bit mode)
    LCD_Delay_ms(50);  // Wait for LCD to power up

    // Send initialization sequence
    LCD_SendNibble(0x03); // Function set
    LCD_Delay_ms(5);

    LCD_SendNibble(0x03); // Function set
    LCD_Delay_us(150);

    LCD_SendNibble(0x03); // Function set
    LCD_Delay_us(150);

    LCD_SendNibble(0x02); // Set to 4-bit mode
    LCD_Delay_us(150);

    // Configure LCD settings
    LCD_SendCommand(LCD_FUNCTION_SET_4BIT);      // 4-bit, 2 lines, 5x8 font
    LCD_SendCommand(LCD_DISPLAY_OFF);            // Display off
    LCD_SendCommand(LCD_CLEAR_DISPLAY);          // Clear display
    LCD_SendCommand(LCD_ENTRY_MODE_SET);         // Entry mode: increment cursor
    LCD_SendCommand(LCD_DISPLAY_ON_CURSOR_OFF);  // Display on, cursor off
}

void LCD_SendCommand(uint8 command) {
    Gpio_WritePin(LCD_CTRL_PORT, LCD_RS_PIN, LOW);  // Command mode

    // Send upper nibble
    LCD_SendNibble((command >> 4) & 0x0F);

    // Send lower nibble
    LCD_SendNibble(command & 0x0F);

    LCD_Delay_ms(2);  // Wait for command execution
}

void LCD_SendData(uint8 data) {
    Gpio_WritePin(LCD_CTRL_PORT, LCD_RS_PIN, HIGH);  // Data mode

    // Send upper nibble
    LCD_SendNibble((data >> 4) & 0x0F);

    // Send lower nibble
    LCD_SendNibble(data & 0x0F);

    LCD_Delay_us(50);  // Wait for data execution
}

void LCD_SendNibble(uint8 nibble) {
    // Set data pins according to nibble value
    Gpio_WritePin(LCD_DATA_PORT, LCD_D4_PIN, (nibble >> 0) & 0x01);
    Gpio_WritePin(LCD_DATA_PORT, LCD_D5_PIN, (nibble >> 1) & 0x01);
    Gpio_WritePin(LCD_DATA_PORT, LCD_D6_PIN, (nibble >> 2) & 0x01);
    Gpio_WritePin(LCD_DATA_PORT, LCD_D7_PIN, (nibble >> 3) & 0x01);

    // Pulse enable pin
    LCD_Pulse_Enable();
}

void LCD_Pulse_Enable(void) {
    Gpio_WritePin(LCD_CTRL_PORT, LCD_EN_PIN, HIGH);
    LCD_Delay_us(1);  // Enable pulse width
    Gpio_WritePin(LCD_CTRL_PORT, LCD_EN_PIN, LOW);
    LCD_Delay_us(1);  // Enable cycle time
}

void LCD_SendString(const char* str) {
    while (*str) {
        LCD_SendData(*str);
        str++;
    }
}

void LCD_SetCursor(uint8 row, uint8 col) {
    uint8 address;

    if (row == 0) {
        address = LCD_SET_CURSOR_FIRST_LINE + col;
    } else if (row == 1) {
        address = LCD_SET_CURSOR_SECOND_LINE + col;
    } else {
        address = LCD_SET_CURSOR_FIRST_LINE;  // Default to first line
    }

    LCD_SendCommand(address);
}

void LCD_Clear(void) {
    LCD_SendCommand(LCD_CLEAR_DISPLAY);
    LCD_Delay_ms(2);
}

void LCD_PrintNumber(uint32 number) {
    char buffer[12];  // Enough for 32-bit number
    uint8 i = 0;

    // Handle zero case
    if (number == 0) {
        LCD_SendData('0');
        LCD_SendData(' ');  // Clear any remaining digit
        LCD_SendData(' ');  // Clear any remaining digit
        return;
    }

    // Convert number to string (reverse order)
    uint32 temp = number;
    while (temp > 0) {
        buffer[i++] = (temp % 10) + '0';
        temp /= 10;
    }

    // Send digits in correct order
    uint8 digits_printed = 0;
    while (i > 0) {
        LCD_SendData(buffer[--i]);
        digits_printed++;
    }

    // Clear remaining positions (assuming max 3 digits for percentage)
    while (digits_printed < 3) {
        LCD_SendData(' ');
        digits_printed++;
    }
}


void LCD_PrintFloat(float number, uint8 decimal_places) {
    // Handle negative numbers
    if (number < 0) {
        LCD_SendData('-');
        number = -number;
    }

    // Print integer part
    uint32 integer_part = (uint32)number;
    LCD_PrintNumber(integer_part);

    // Print decimal point
    LCD_SendData('.');

    // Print decimal part
    float decimal_part = number - integer_part;
    for (uint8 i = 0; i < decimal_places; i++) {
        decimal_part *= 10;
        uint8 digit = (uint8)decimal_part;
        LCD_SendData(digit + '0');
        decimal_part -= digit;
    }
}

// Simple delay functions (for basic timing)
// Note: These are approximate delays and may need calibration
void LCD_Delay_ms(uint16 delay) {
    for (uint16 i = 0; i < delay; i++) {
        LCD_Delay_us(1000);
    }
}

void LCD_Delay_us(uint16 delay) {
    // Approximate delay for microseconds
    // This needs to be calibrated based on your system clock
    // For 16MHz system clock, roughly:
    volatile uint32 count = delay * 4;  // Adjust this multiplier as needed
    while (count--) {
        // Do nothing - just waste time
    }
}