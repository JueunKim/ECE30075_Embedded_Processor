#include "lm3s9b92.h"

#define GPIO_PORTF_DATA (*((volatile unsigned long*) (0x400253FC)))
#define PORT2 (*((volatile unsigned long*) (0x424A7F88)))
#define PORT3 (*((volatile unsigned long*) (0x424A7F8C)))

void delay(unsigned long);

int main()
{	
	//enable peripheral clock for PORT F
	SYSCTL_RCGC2_R |= (0x01 << 5);
	
	//a dummy delay
	delay(5);
	
	//set up direction for PORT F pin 2 and pin 3 (as output)
	GPIO_PORTF_DIR_R |= (0x01 << 2);
	GPIO_PORTF_DIR_R |= (0x01 << 3);
	
	//enalbe digital function for PORT F pin 2 and pin 3
	GPIO_PORTF_DEN_R |= (0x01 << 2);
	GPIO_PORTF_DEN_R |= (0x01 << 3);
	
	
	while(1){
	

		PORT2 = 0;
		PORT3 = 1;
		
		delay(1000000);
		
		PORT2 = 1;	
		PORT3 = 0;
			
		delay(1000000);
	}
	return 0;
}

void delay(unsigned long loops){
	volatile unsigned long i;
	for(i=0; i<loops; i++);
}



