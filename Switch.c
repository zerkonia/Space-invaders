// Switch.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize PORTE 




#include "Switch.h"
#include "tm4c123gh6pm.h"
#include "ADC.h"
#define FIRE      	              (*((volatile unsigned long *)0x40024004))
#define SPECIAL                   (*((volatile unsigned long *)0x40024008))


void Switchs_Init(void)
{
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000010;            // 1) E clock
  delay = SYSCTL_RCGC2_R;                  // delay   
  GPIO_PORTE_DIR_R &= ~0x13;               // 2) make PE0 & PE1 & PE4 input
	GPIO_PORTE_AFSEL_R &= ~0x13;             // 3) disable alternate function on PE(0-1-4)
	GPIO_PORTE_DEN_R |= 0x13;                // 4) enable digital I/O on PE0 & PE1 & PE4
  GPIO_PORTE_AMSEL_R &= ~0x13;             // 5) disable analog function
  GPIO_PORTE_PCTL_R &= ~0x13;              // 6) GPIO clear bit PCTL  
	/*
  GPIO_PORTE_IS_R &= ~0x03;                // 8) PE0 & PE1 are edge-sensitive	
	GPIO_PORTE_IBE_R &= ~0x03;               // 9) PE0 & PE1 are not both edges
	GPIO_PORTE_IEV_R |= 0x03;                // A) PE0 & PE1 rising edge event
	GPIO_PORTE_ICR_R |= 0x03;                // B) clear flag4
	GPIO_PORTE_IM_R |= 0x03;                 // C) arm interrupt on PE0 & PE1
	NVIC_PRI0_R = (NVIC_PRI1_R&0xFFFFFF00)|0x000000A0;  // D) priority 5
	NVIC_EN0_R = 0x00000010;                // E) enable interrupt 1 in NVIC
	//EnableInterrupts();                      // (F) Enable global Interrupt flag 
*/
}
