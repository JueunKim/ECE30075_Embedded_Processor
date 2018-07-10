#include "lm3s9b92.h"

#define GPIO_PORTF_DATA_Rsel(x) (*((volatile unsigned long*) (0x450025000 | ((x) <<2))))

void delay(unsigned long);


int main()
{	
	
	//enable peripheral clock for PORT F
	SYSCTL_RCGC2_R |= (0x01 << 5);
	
	//a dummy delay
	delay(5);
	
	//set up direction for PORT F pin 2 (as output)
	GPIO_PORTF_DIR_R |= (0x01 << 2);
	
	//enalbe digital function for PORT F pin 2
	GPIO_PORTF_DEN_R |= (0x01 << 2);


	GPIO_PORTF_DATA_Rsel((0x01<<2)|(0x01<<4)) = 0x01<<2;
	
	while(1){
	
		//turn on LED connected to PORT F pin2
		GPIO_PORTF_DATA_R &= ~(0x01 << 2);
		delay(1000000);
		//turn off LED connected to PORT F pin2
		GPIO_PORTF_DATA_R |= (0x01 << 2);
		delay(1000000);
	}
	}
	return 0;
}


void delay(unsigned long loops){
	volatile unsigned long i;
	for(i=0; i<loops; i++);
}
