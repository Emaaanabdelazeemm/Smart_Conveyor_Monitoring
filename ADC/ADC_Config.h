//
// Created by dell on 6/6/2025.
//

#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

/***************************************
 * ADC Resolution Options
 * ADC_RESOLUTION_12_BIT
 * ADC_RESOLUTION_10_BIT
 * ADC_RESOLUTION_8_BIT
 * ADC_RESOLUTION_6_BIT
 ***************************************/
#define ADC_RESOLUTION            ADC_RESOLUTION_12_BIT


/***************************************
 * ADC Data Alignment Options
 * ADC_RIGHT_ALIGNMENT
 * ADC_LEFT_ALIGNMENT
 ***************************************/
#define ADC_DATA_ALIGNMENT        ADC_RIGHT_ALIGNMENT


/***************************************
 * ADC Prescaler Options
 * ADC_PRESCALER_2
 * ADC_PRESCALER_4
 * ADC_PRESCALER_6
 * ADC_PRESCALER_8
 ***************************************/
#define ADC_PRESCALER             ADC_PRESCALER_2


/***************************************
 * ADC Sampling Rate Options
 * ADC_3_CYCLES
 * ADC_15_CYCLES
 * ADC_28_CYCLES
 * ADC_56_CYCLES
 * ADC_84_CYCLES
 * ADC_112_CYCLES
 * ADC_144_CYCLES
 * ADC_480_CYCLES
 ***************************************/
#define SAMPLING_RATE 				ADC_84_CYCLES


/***************************************
 * ADC Number of Channels Selected Options
 * from 1 to 16
 ***************************************/
#define NUM_CHANNELS      			1




#endif //ADC_CONFIG_H
