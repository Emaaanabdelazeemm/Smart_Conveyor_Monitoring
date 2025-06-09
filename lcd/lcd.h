//
// Created by shahd 7 on 6/3/2025.
//

#ifndef LCD_H_
#define LCD_H_

#include "../LIB/Std_Types.h"

// LCD Configuration
#define LCD_DATA_PORT    GPIO_B    // Data pins connected to Port B
#define LCD_CTRL_PORT    GPIO_A    // Control pins connected to Port A

// LCD Control Pins
#define LCD_RS_PIN       5         // Register Select pin (PA0)
#define LCD_EN_PIN       6         // Enable pin (PA1)

// LCD Data Pins (4-bit mode)
#define LCD_D4_PIN       4         // Data bit 4 (PB4)
#define LCD_D5_PIN       5         // Data bit 5 (PB5)
#define LCD_D6_PIN       6         // Data bit 6 (PB6)
#define LCD_D7_PIN       7         // Data bit 7 (PB7)

// LCD Commands
#define LCD_CLEAR_DISPLAY          0x01
#define LCD_RETURN_HOME            0x02
#define LCD_ENTRY_MODE_SET         0x06
#define LCD_DISPLAY_ON_CURSOR_OFF  0x0C
#define LCD_DISPLAY_OFF            0x08
#define LCD_CURSOR_SHIFT_LEFT      0x10
#define LCD_CURSOR_SHIFT_RIGHT     0x14
#define LCD_FUNCTION_SET_4BIT      0x28
#define LCD_SET_CURSOR_FIRST_LINE  0x80
#define LCD_SET_CURSOR_SECOND_LINE 0xC0

// Function Prototypes
void LCD_Init(void);
void LCD_SendCommand(uint8 command);
void LCD_SendData(uint8 data);
void LCD_SendString(const char* str);
void LCD_SetCursor(uint8 row, uint8 col);
void LCD_Clear(void);
void LCD_PrintNumber(uint32 number);
void LCD_PrintNumber_FixedWidth(uint32 number, uint8 width);
void LCD_PrintFloat(float number, uint8 decimal_places);

// Private helper functions
void LCD_SendNibble(uint8 nibble);
void LCD_Pulse_Enable(void);
void LCD_Delay_ms(uint16 delay);
void LCD_Delay_us(uint16 delay);

#endif /* LCD_H_ */
