#  Smart Conveyor Monitoring & Control System
**STM32 Embedded System with Proteus Simulation**  
*Real-time speed measurement, motor control, and object detection for industrial automation*

## Project Highlights
-  **Timer Input Capture** for precise conveyor speed measurement (no interrupts)
-  **PWM Motor Control** driven by potentiometer ADC input
-  **Object Counter** with software-based edge detection
-  **Emergency Stop** with interrupt-driven safety response
-  **16x2 LCD Interface** showing real-time parameters

## Technical Stack
| Component          | Implementation Details |
|--------------------|------------------------|
| **Microcontroller** | STM32F401 (ARM Cortex-M4) |
| **Speed Sensor**   | Timer Capture (TIM2) @ 1µs resolution |
| **Motor Control**  | PWM Generation (TIM3) + 12-bit ADC |
| **Object Detector**| GPIO Polling (Falling Edge) |
| **Emergency Stop** | EXTI Interrupt (Highest Priority) |
| **Simulation**     | Proteus 8 Professional |
