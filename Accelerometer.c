
#include "Accelerometer.h"
#ifndef  TM4C123GHPM_H
#define  TM4C123GHPM_H
#include "tm4c123gh6pm.h"
#endif 

#include "SpaceInvaders_definition.h"
  volatile unsigned long delay;
	volatile unsigned long T11 = 0;                 //This variable is used to hold rising edge timing event
	volatile unsigned long T12 = 0;                 //This variable is used to hold falling edge timing event
  volatile long duty1 = 0;                        //This variable is used to hold T2-T1
	volatile unsigned long T21 = 0;                 //This variable is used to hold rising edge timing event
	volatile unsigned long T22 = 0;                 //This variable is used to hold falling edge timing event
	volatile long duty2 = 0;                        //This variable is used to hold T2-T1
  volatile long *Acc_x;
  volatile long *Acc_y;
	long ACC1_position;
	long ACC2_position;
	volatile long old_accX1 = 0;
	volatile long old_accX2 = 0;
	volatile long old_accX3 = 0;
	volatile long old_accX4 = 0;
	volatile long old_accX5 = 0;
	volatile long old_accX6 = 0;
	volatile long acc_avg1 = 0;
	volatile long old_accY1 = 0;
	volatile long old_accY2 = 0;
	volatile long old_accY3 = 0;
	volatile long old_accY4 = 0;
	volatile long old_accY5 = 0;
	volatile long old_accY6 = 0;
	volatile long acc_avg2 = 0;
void Accelerometer_init(void)
{
	Acc_x = &duty1;
	Acc_y = &duty2;
	T11 = 0;
	T12 = 0;
	duty1 = 0;
	T21 = 0;
	T22 = 0;
	duty2 = 0;
  SYSCTL_RCGC2_R  |= 0x00000004;              // 1) Enable port C clock
	SYSCTL_RCGCGPIO_R |= 0x04;                  // 2)Enable PortC
	delay = SYSCTL_RCGC2_R;                     // 3) Delay
	GPIO_PORTC_AFSEL_R |= 0x30;                 // 5) Alternate function is enabled
	SYSCTL_RCGCWTIMER_R |= 0x01;                // 4) Enable WTimer0
	GPIO_PORTC_PCTL_R |= GPIO_PCTL_PC4_WT0CCP0; // 6)Select timerA0 alternative function for PC4
	GPIO_PORTC_PCTL_R |= GPIO_PCTL_PC5_WT0CCP1; // 7)Select timerB0 alternative function for PC5
  GPIO_PORTC_CR_R |= 0x30;                    // 8) Allow changes to PC4 & PC5      
  GPIO_PORTC_AMSEL_R &= ~0x30;                // 9) Disable analog function 
  GPIO_PORTC_DIR_R &= ~0x30;                  // 10) PC4 & PC5 Input  
  GPIO_PORTC_DEN_R |= 0x30;                   // 11) Enable digital pins PC4 & PC5
	GPIO_PORTC_PCTL_R |= (0x00770000);          // 12) GPIO clear bit PCTL 
	WTIMER0_CTL_R &= ~TIMER_CTL_TAEN;           // 13)disable WTimer0
	WTIMER0_CTL_R &= ~TIMER_CTL_TBEN;           // 14)disable WTimer0
	WTIMER0_CFG_R |= 0x00000004;                // 15)Configuring timer0 to 64 bit
	WTIMER0_TAMR_R |= 0x17;                     // 16)Selecting count up mode, setting timer to capture mode
	//and setting to edge time mode
	WTIMER0_TBMR_R |= 0x17;                     // 17)Selecting count up mode, setting timer to capture mode
	//and setting to edge time mode
	WTIMER0_CTL_R |= 0xC;                       // 18)Setting event to both edges event for Timer0A
	WTIMER0_CTL_R |= 0xC00;                     // 19)Setting event to both edges event for Timer0B
	WTIMER0_TAPR_R &= ~(0xFFFF);                // 20)No prescaler is used for timerA
	WTIMER0_TBPR_R &= ~(0xFFFF);                // 21)No prescaler is used for timerB
	WTIMER0_TAILR_R = 0xFFFFFFFF;               // 22)Intialize interval load register 
	WTIMER0_TBILR_R |= 0xFFFFFFFF00000000;      // 23)Intialize interval load register
	WTIMER0_ICR_R |= 0x404;                     // 24)TimerA&B Capture Mode Event Interrupt Clear 
	WTIMER0_IMR_R |= 0x404;                     // 25)Arm Capture Mode Event interrupt
	NVIC_PRI23_R = (NVIC_PRI23_R&0xFF0FFFFF)|0x00400000; // 26)priority 4
// Interrupts enabled in the main program after all devices initialized
// Vector number 110, interrupt number 94
	NVIC_PRI23_R = (NVIC_PRI23_R&0x0FFFFFFF)|0x40000000; // 27)priority 4
// Interrupts enabled in the main program after all devices initialized
// Vector number 111, interrupt number 95
  WTIMER0_CTL_R |= TIMER_CTL_TAEN;            // 28)Enable WTimer0
	WTIMER0_CTL_R |= TIMER_CTL_TBEN; 
	NVIC_EN2_R = 0x40000000;                    // 29)Enable IRQ 94 in NVIC
	NVIC_EN2_R = 0x80000000;                    // 30)Enable IRQ 95 in NVIC
}
	

void WideTimer0A_Handler(void){
	WTIMER0_ICR_R  = TIMER_ICR_CAECINT ; // acknowledge TIMER0A Capture Mode Event Interrupt
	if((GPIO_PORTC_DATA_R & 0x10) != 0x10){
		T11 = 0;
		T12 = 0;
	}
	if(T11 == 0 && Accelerometer_disable == No){	
	  T11 = WTIMER0_TAR_R;
	}
  if(T11 != 0 && Accelerometer_disable == No){
	  T12 = WTIMER0_TAR_R;
		if(T11 < T12){
	     duty1 = (T12 - T11)/1000;
	     }
		//if(T11 >= T12){
	     //duty1 = ((4000000 + T11) - T12);
		  // }
	   }
	 }

void WideTimer0B_Handler(void){
	WTIMER0_ICR_R  = TIMER_ICR_CBECINT;  // acknowledge TIMER0BCapture Mode Event Interrupt
	if((GPIO_PORTC_DATA_R & 0x20) != 0x20){
		T21 = 0;
		T22 = 0;
	}
	if(T21 == 0 && Accelerometer_disable == No){	
	  T21 = WTIMER0_TBR_R;
	}
  if(T21 != 0 && Accelerometer_disable == No){
	  T22 = WTIMER0_TBR_R;
		if(T21 < T22){
	     duty2 = (T22 - T21)/1000;
		   }
		//if(T21 >= T22){
	    // duty2 = ((4000000 + T21) - T22);
		  // }
	   }
	 }

unsigned long Convert_accelerometer1(void){
	ACC1_position = ((-112*(*Acc_x))+48497)/51;
	if(ACC1_position >= 114 && ACC1_position <=  562){
	ACC1_position =114;	
	}
	if(ACC1_position > 562){
	ACC1_position = 2;	
	}
	old_accX6 = old_accX5;
	old_accX5 = old_accX4;
	old_accX4 = old_accX3;
	old_accX3 = old_accX2;
	old_accX2 = old_accX1;
	old_accX1 = ACC1_position;
	acc_avg1 = (old_accX1 + old_accX2 + old_accX3 + old_accX4 + old_accX5 + old_accX6)/6;
	return acc_avg1;
}

unsigned long Convert_accelerometer2(void){
	ACC2_position = ((-25*(*Acc_y))+10997)/11;
	if(ACC2_position >= 127 && ACC2_position <=  562){
	ACC2_position =127;	
	}
	if(ACC2_position > 562){
	ACC2_position = 27;	
	}
	old_accY6 = old_accY5;
	old_accY5 = old_accY4;
	old_accY4 = old_accY3;
	old_accY3 = old_accY2;
	old_accY2 = old_accY1;
	old_accY1 = ACC2_position;
	acc_avg2 = (old_accY1 + old_accY2 + old_accY3 + old_accY4 + old_accY5 + old_accY6)/6;
	return acc_avg2;
}

