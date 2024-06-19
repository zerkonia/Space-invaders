// Switch.h
// Runs on LM4F120/TM4C123
// Provide functions that initialize PORTE 





//------------Switchs_Init------------
// initialization of PORTE
// Input: none
// Output: none
void Switchs_Init(void);



//------------ADC0_In------------
// get input from switchs
// Input: none
// Output: 1 for fire, 2 for special
unsigned long Switch_In(void);

