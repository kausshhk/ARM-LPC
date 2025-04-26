#include <LPC17xx.H>
void delay(unsigned long int x);
int main()
	{	unsigned char cmd[]={0x38,0x0e,0x06,0x01,0x80},i;
		SystemInit ();
 		LPC_GPIO2->FIOMASK0=0X00;  // 1110 1111 
 		LPC_GPIO2->FIODIR0=0XFF;	 // 0001 0000
	
		LPC_GPIO1->FIOMASK1=0XF8;  // 1111 1000 
 		LPC_GPIO1->FIODIR1=0X07;	 // 0000 0111
	  
	  LPC_GPIO1->FIOCLR1=0X02; //rw=0
	
    LPC_GPIO1->FIOCLR1=0X01; // 0000 0001	
	for(i=0;i<5;i++)
	{
		LPC_GPIO2->FIOPIN0=cmd[i];
		LPC_GPIO1->FIOSET1=0X04;
		delay(1000);
		LPC_GPIO1->FIOCLR1=0X04;
		delay(5000);
	}
	
	 LPC_GPIO1->FIOSET1=0X01; // 0000 0001	
	for(i=0;i<5;i++)
	{
		LPC_GPIO2->FIOPIN0=cmd[i];
		LPC_GPIO1->FIOSET1=0X04;
		delay(1000);
		LPC_GPIO1->FIOCLR1=0X04;
		delay(5000);
	}
}

void delay(unsigned long int x)
	{
 		unsigned long int i=0;
 		for(i=0;i<x;i++);	
	}
