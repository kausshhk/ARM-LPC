#include <LPC17xx.H>
void delay(unsigned long int x);
void initTimer0(void);
void delayUS(unsigned int microseconds);
  
 
  
int main()
	{	SystemInit ();
 		LPC_GPIO1->FIOMASK3=0XEF;  // 1101 1111 
 		LPC_GPIO1->FIODIR3=0X10;	 // 0001 0000
		initTimer0();
	while(1)
		{  
		LPC_GPIO1->FIOSET3=0X10;
  	delayUS(500); 
		LPC_GPIO1->FIOCLR3=0X10;
		delayUS(500); 
		}
	}

void delay(unsigned long int x)
	{
 		unsigned long int i=0;
 		for(i=0;i<x;i++);	
	}


void initTimer0(void) //PCLK must be = 72Mhz! 
  { 
		LPC_TIM0->CTCR = 0x00; // CTCR[1:0]=00;Timer Mode;CTCR[1:0]=01; Counter Rising
  	LPC_TIM0->PR = 17; //Increment TC at every 24999+1 clock cycles 
  	LPC_TIM0->TCR = 0x02; //0010; TCR[1]=Reset Timer on Next rising edge of PCLK_Timer0 
  } 
	
void delayUS(unsigned int microseconds) //Using Timer0 
  { 
  	LPC_TIM0->TCR = 0x02; //Reset Timer 
  	LPC_TIM0->TCR = 0x01; //Enable timer 
  	while(LPC_TIM0->TC < microseconds)
		{}			//wait until timer counter reaches the desired delay 
  	LPC_TIM0->TCR = 0x00; //Disable timer 
  } 
	
		