#include <LPC17xx.h>
void lcd_data(unsigned char data);
void delay(unsigned long int count);
#define  RS  0x08 //0000 0001
#define  RW  0x10 //0000 0010
#define  EN  0x20 //0000 0100
unsigned int ad0=0;

int main()
{
unsigned char cmd[]={0x38,0x0E,0x06,0x01,0x80},k;
unsigned char msg1[]="Heater Control";
unsigned char msg2[]="Heater ON";
unsigned char msg3[]="Heater OFF";
SystemInit();
// test LED connected at P1.25 and P1.26 --------------------------------------------------------
LPC_GPIO1->FIOMASK3=0XF9;  // 1110 1001 
LPC_GPIO1->FIODIR3=0X06;	 // 0001 0000
LPC_GPIO1->FIOSET3=0X02;  //0100
LPC_GPIO1->FIOCLR3=0X04;
// Relay operation using P3.25 and P3.26
LPC_GPIO3->FIOMASK3=0XF9;  // 1110 1001 
LPC_GPIO3->FIODIR3=0X06;	 // 0001 0000
LPC_GPIO3->FIOSET3=0X06;	
// LCD Port Initilization -------------------------------------------------------------
LPC_GPIO0->FIOMASKH=0XE01F; // 1110 0000 0001 1111 
LPC_GPIO0->FIODIRH=0X1FE0;	// 0000 0001
LPC_GPIO2->FIOMASK1=0xC7;   // 1100 0111 
LPC_GPIO2->FIODIR1=0X38;	  // 0000 0001
// ADC Initilisation -------------------------------------------------------------------
LPC_SC->PCONP|=0X00001000; // This enable PCADC and retains intial conditions or 
LPC_PINCON->PINSEL3|=0XC0000000;  // 1100 0000 0000 0000 0000 0000 0000 00000 (AD0.5)
LPC_ADC->ADCR=0X00210320; // 0000 0000 0010 0001     0000 0011 0010 0000  ;ADCR[26:24]=Start=000;ADCR[21]=PDN=1 ADCR[16]=Burst=1 
//--------------------------------------------------------------------------------------
LPC_GPIO2->FIOCLR1=RW; // RW=0	
//------------- LCD Command Initilisation-----------------------------------------------------------------------------
  LPC_GPIO2->FIOCLR1=RS; // RS=0 
  for (k=0;k<5;k++)
    {
     lcd_data(cmd[k]);
		}
//------------- Displaying String ------------------------------------------------------------------------------------	
  LPC_GPIO2->FIOSET1=RS; // RS=1 
  for (k=0;k<msg1[k]!='\0';k++)
    {
     lcd_data(msg1[k]);
		}

while(1)
{
	while((LPC_ADC->ADSTAT&0X00000020)!=0X00000020)
	{
	}
	ad0=(((LPC_ADC->ADDR5)&0X0000FFF0)>>4);
	if (ad0>0x7ff)
	{ LPC_GPIO3->FIOCLR3=0X06;	// 0000 0110
		LPC_GPIO1->FIOSET3=0X04; // LED is on 0000 0100
		LPC_GPIO1->FIOCLR3=0X02;
		LPC_GPIO2->FIOCLR1=RS; // RS=0 
		lcd_data(0xC0);
//------------- Displaying String ------------------------------------------------------------------------------------	
    LPC_GPIO2->FIOSET1=RS; // RS=1 
    for (k=0;k<msg2[k]!='\0';k++)
     {
       lcd_data(msg2[k]);
		 }
		
	 }
	else if ( ad0<0x1ff)
	{ LPC_GPIO3->FIOSET3=0X06;	
		LPC_GPIO1->FIOSET3=0X02;  //0100
		LPC_GPIO1->FIOCLR3=0X04;
		
		LPC_GPIO2->FIOCLR1=RS; // RS=0 
		lcd_data(0xC0);
//------------- Displaying String ------------------------------------------------------------------------------------	
    LPC_GPIO2->FIOSET1=RS; // RS=1 
    for (k=0;k<msg3[k]!='\0';k++)
     {
       lcd_data(msg3[k]);
		 }
	}
  
}
}

// ------------------------------------ FUNCTIONS----------------------------------------------------------------


void lcd_data(unsigned char data)
{	
		 LPC_GPIO0->FIOPIN=data<<21;
		 LPC_GPIO2->FIOSET1=EN;    // EN=1
		 delay(0x500);
		 LPC_GPIO2->FIOCLR1=EN;    // EN=0
		 delay(0x500);
}

void delay(unsigned long int count)
{
  unsigned long int j=0,i=0;
  for(j=0;j<count;j++)
  {
    /* At 100Mhz, the below loop introduces DELAY of 1 us */
    for(i=0;i<23;i++);
  }
}
