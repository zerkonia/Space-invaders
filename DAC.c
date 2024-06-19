// DAC.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Implementation of the 4-bit digital to analog converter
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// Port B bits 7-0 have the 8-bit DAC

#include "DAC.h"
#ifndef  TM4C123GHPM_H
#define  TM4C123GHPM_H
#include "tm4c123gh6pm.h"
#endif 


// **************DAC_Init*********************
// Initialize 8-bit DAC 
// Input: none
// Output: none
void DAC_Init(void){
	
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |=0x00000002;
  delay = SYSCTL_RCGC2_R;
  GPIO_PORTB_AMSEL_R &= ~0xFF;        // 3) disable analog function
  GPIO_PORTB_PCTL_R &= ~0xFFFFFFFF;   // 4) GPIO clear bit PCTL
  GPIO_PORTB_DIR_R |= 0xFF;						// 5) PB7-PB0 output
	GPIO_PORTB_DR8R_R|= 0xFF;
  GPIO_PORTB_AFSEL_R &= ~0xFF;        // 6) no alternate function
  GPIO_PORTB_DEN_R |= 0xFF;
	
}


// **************DAC_Out*********************
// output to DAC
// Input: 8-bit data, 0 to 255 
// Output: none
void DAC_Out(unsigned long data){
	
	PortB0_7 = data;
  
}
