// ADC.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0 SS3 to be triggered by
// software and trigger a conversion, wait for it to finish,
// and return the result. 
// Daniel Valvano
// January 15, 2016

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2015

 Copyright 2016 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

#include "ADC.h"
#include "tm4c123gh6pm.h"
#include "switch.h"
volatile unsigned long result_x;
volatile unsigned long result_y;
volatile unsigned long ADC_conversion;

//unsigned char extern String[10]; // null-terminated ASCII string
//unsigned char extern String1[]={"Lab 14"}; // null-terminated ASCII string
//unsigned char String2[]={"Hello world"}; // null-terminated ASCII string



// This initialization function sets up the ADC0 
// Max sample rate: <=125,000 samples/second
// SS0 triggering event: software trigger
// SS0 1st sample source:  channel 0 & 1
// SS0 interrupts: enabled and promoted to controller
void ADC0_Init(void){ 
	unsigned volatile long delay ;
	SYSCTL_RCGCADC_R |= 0x01;
  SYSCTL_RCGCGPIO_R |= 0x10;      // 1) activate clock for Port E
  delay = SYSCTL_RCGCGPIO_R;      //  allow time for clock to stabilize
  GPIO_PORTE_AFSEL_R |= 0x0C;     // 3) enable alternate function on PE2, PE3
  GPIO_PORTE_DEN_R &= ~0x0C;      // 4) disable digital I/O on PE2, PE3
  GPIO_PORTE_AMSEL_R |= 0x0C;     // 5) enable analog function on PE2, PE3
  SYSCTL_RCGC0_R |= 0x00010000;   // 6) activate ADC0
  delay = SYSCTL_RCGC0_R;        
  ADC0_PC_R  = 0x1;               // 7) configure for 125K
  ADC0_SSPRI_R = 0x3210;          // 8) Sequencer 0 is highest priority
  ADC0_ACTSS_R &= ~0x0001;        // 8) disable sample sequencer 0
  ADC0_EMUX_R &= ~0x000F;         // 9) seq0 is software trigger
  ADC0_SSMUX0_R &= ~0x000000FF;   // 10) clear SS0 field
	ADC0_SSMUX0_R |= 0x00010 ;      // set channel Ain1 (PE2) & channel Ain0 (PE3)
  ADC0_SSCTL0_R |= 0x00000064 ;   // 12) no TS0 D0 END0, yes IE0 
	ADC0_SAC_R |= 0x6;
	ADC0_IM_R |= 0x00000001;
	NVIC_PRI3_R = (NVIC_PRI3_R&0xFF0FFFFF)|0x00800000; // 26)priority 4
  // Interrupts enabled in the main program after all devices initialized
  // Vector number 30, interrupt number 14
  NVIC_EN0_R = (1<<14);           // 29)Enable IRQ 14 in NVIC
	ADC0_ACTSS_R |= 0x0001;         // 13) enable sample sequencer 0
	ADC0_PSSI_R |=0x0001;
}
void ADC0Seq0_Handler(void){
	ADC0_ISC_R = ADC_ISC_IN0;
	ADC0_PSSI_R |=0x0001;
	ADC_conversion = ADC0_SSFIFO0_R&0xFFF;
	if(((ADC0_SSFSTAT0_R&0xF) == 0x0)){
		result_x = ADC_conversion;
	}
	else if(((ADC0_SSFSTAT0_R&0xF) == 0x1)){
		result_y = ADC_conversion;
  }
}

//------------ADC0_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
unsigned long ADC0_In_x(void){ 
return result_x;	
}

//------------ADC0_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
unsigned long ADC0_In_y(void){  
	return result_y; 
}
