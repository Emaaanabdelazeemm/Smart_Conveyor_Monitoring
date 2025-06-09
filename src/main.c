#include "../Lib/Std_Types.h"
#include "../RCC/RCC.h"
#include "../Gpio/GPIO.h"
#include"../ADC/ADC.h"
#include"../PWM/PWM.h"
#include "../Motor/motor.h"
#include"../lcd/lcd.h"
#include "../Timer/Timer.h"



#define POT_PORT    GPIO_A
#define POT_PIN     1
#define POT_CHANNEL ADC_IN1

#define motor_IN1_PIN 15
#define motor_IN2_PIN 14

#define IR_Push_button_pin 9




void setup(void);
void loop(void);
uint16 read_duty_cycle(void);
void check_object_detection();
void update_LCD_object_count(uint8 count);
uint8 Read_IR_button();
void Display_motor_speed(uint16 duty_cycle_percent);


uint8 object_count = 0;
uint8 prev_state = 1;
uint8 curr_state;

int main()
{
	setup();

	while (1)
	{
		loop();
	}

	// This line should never be reached
	return 0;
}

void setup(void)
{
	Rcc_Init();
	Rcc_Enable(RCC_GPIOA);
	Rcc_Enable(RCC_GPIOB);
	Rcc_Enable(RCC_SYSCFG);
	Rcc_Enable(RCC_TIM2);



	Init_Motor(TIM2_CH3, 50);
	LCD_Init();
	TIM_Init(TIM_CH1);
	ADC_INIT(POT_PORT, POT_PIN, POT_CHANNEL);
	Gpio_Init(GPIO_B, motor_IN1_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
	Gpio_Init(GPIO_B, motor_IN2_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
	Gpio_Init(GPIO_B, IR_Push_button_pin, GPIO_INPUT, GPIO_PULL_UP);
	Gpio_WritePin(GPIO_A,motor_IN1_PIN , LOW);
	Gpio_WritePin(GPIO_A, motor_IN2_PIN, HIGH);
	//led for timer
	Gpio_Init(GPIO_A, 7, GPIO_OUTPUT, GPIO_PUSH_PULL);
	Gpio_WritePin(GPIO_A, 7, HIGH);
}

void loop(void) {

	uint16 duty_cycle_percent = read_duty_cycle();
	Set_Motor_Speed(duty_cycle_percent);
	Display_motor_speed(duty_cycle_percent);
	check_object_detection();
	uint32 pulse_width = TIM_GetCaptureValue();
	// Toggle LED if valid pulse detected
	if(pulse_width > 0) {
		Gpio_WritePin(GPIO_A, 7, LOW);
	}



}



uint16 read_duty_cycle(void)
{
	uint16 digital_value = ADC_CONVERSION();  // Read ADC value
	uint16 duty_cycle_percent = ((uint16)digital_value * 100U) / 4095U;

	return duty_cycle_percent;  // Convert to percentage (0-100%)
}

uint8 Read_IR_button() {
	return (Gpio_ReadPin(GPIO_B, IR_Push_button_pin));
}
void update_LCD_object_count(uint8 count) {
	LCD_SetCursor(0, 1);
	LCD_SendString("Count:");
	LCD_PrintNumber(count);
}

void check_object_detection() {
	curr_state = Read_IR_button();

	if (prev_state == 1 && curr_state == 0) {
		object_count++;
		update_LCD_object_count(object_count);  // Function to display count
	}

	prev_state = curr_state;
}

void Display_motor_speed(uint16 duty_cycle_percent) {
	LCD_SetCursor(1, 1);
	LCD_SendString("Motor:");
	LCD_PrintNumber(duty_cycle_percent);
}
