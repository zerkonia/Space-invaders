// DAC.h
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Header file for the 8-bit digital to analog converter
// Daniel Valvano, Jonathan Valvano
// March 13, 2014

#define PortB0_7                  (*((volatile unsigned long *)0x400053FC))

// **************DAC_Init*********************
// Initialize 8-bit DAC 
// Input: none
// Output: none

void DAC_Init(void);


// **************DAC_Out*********************
// output to DAC
// Input: 8-bit data, 0 to 255 
// Output: none
void DAC_Out(unsigned long data);
  


