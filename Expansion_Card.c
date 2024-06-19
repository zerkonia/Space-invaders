

#include "tm4c123gh6pm.h"
#include "Expansion_Card.h"

//volatile unsigned long Temp;
volatile unsigned long MIC;
volatile unsigned long LDR;
volatile unsigned long ADC_conversion_Exp;



void Expansion_Init(void){
	unsigned volatile long delay ;
	SYSCTL_RCGCGPIO_R |= 0x08;            // activate clock for Port D
  while((SYSCTL_PRGPIO_R&0x08) == 0){}; // allow time for clock to stabilize
  GPIO_PORTD_CR_R = 0xFF;               // allow changes to PD7-0
	GPIO_PORTD_AFSEL_R |= 0x0D;     // 3) enable alternate function on PD0, PD1, PD2
  GPIO_PORTD_DEN_R &= ~0x0D;      // 4) disable digital I/O on PD0, PD1, PD2
  GPIO_PORTD_AMSEL_R |= 0x0D;     // 5) enable analog function on PD0, PD1, PD2
	SYSCTL_RCGC0_R |= 0x00010000;   // 6) activate ADC0
  delay = SYSCTL_RCGC0_R;        
  ADC0_PC_R  = 0x1;               // 7) configure for 250K
  ADC0_SSPRI_R = 0x3210;          // 8) Sequencer 1 is 2nd highest priority
  ADC0_ACTSS_R &= ~0x0002;        // 8) disable sample sequencer 1
  ADC0_EMUX_R &= ~0x00F0;         // 9) seq1 is software trigger
	ADC0_SSMUX1_R &= ~0x00FF;       // 10) clear SS0 field
	ADC0_SSMUX1_R |= 0x0045 ;        //    set channel Ain1 (PE2) & channel Ain0 (PE3)
  ADC0_SSCTL1_R |= 0x0064 ;       // 12) no TS0 D0 END0, yes IE0 
	ADC0_CTL_R |= 0x40;
	ADC0_SAC_R |= 0x6;
	ADC0_IM_R |= 0x2;
	NVIC_PRI3_R = (NVIC_PRI3_R&0x0FFFFFFF)|0x80000000; // 26)priority 4
  // Interrupts enabled in the main program after all devices initialized
  // Vector number 30, interrupt number 14
  NVIC_EN0_R = (1<<15);           // 29)Enable IRQ 14 in NVIC
	ADC0_ACTSS_R |= 0x0002;         // 13) enable sample sequencer 1
	ADC0_PSSI_R |=0x0002;
}

void ADC0Seq1_Handler(void){
	ADC0_ISC_R = ADC_ISC_IN1;
	ADC0_PSSI_R |= 0x0002;
	ADC_conversion_Exp = ADC0_SSFIFO1_R&0xFFF;
	if(((ADC0_SSFSTAT1_R&0xF) == 0x0)){
		MIC = ADC_conversion_Exp;
  }
	else if(((ADC0_SSFSTAT1_R&0xF) == 0x1)){
		LDR = ADC_conversion_Exp;
  }
	//else if(((ADC0_SSFSTAT1_R&0xF) == 0x2)){
		//Temp = ADC_conversion_Exp;
 // }
}
//unsigned long Temperature_In(void){ 
//return Temp;	
//}

unsigned long Microphone_In(void){ 
return MIC;	
}

unsigned long Light_In(void){ 
return LDR;	
}
