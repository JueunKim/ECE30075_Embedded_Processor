#include <lm3s9b92.h>

void delay(unsigned long);

int main(){
	
	//enable peripheral clock for PORT F
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
	//a dummy delay
	delay(5);
	
	//set up direction for PORT F pin 2 (as output)
	GPIO_PORTF_DIR_R |= (0x01<<2);
	//enable digital function for PORT F pin 2
	GPIO_PORTF_DEN_R |= (0x01<<2);
	
	//set SysTick reload value (for 2sec; system clock = 16M)
	NVIC_ST_RELOAD_R = 16000000 - 1 ;
	
	//clear SysTick control and status register
	//status = NVIC_ST_CTRL_R;

	//enable SysTick timer and set clock source
	NVIC_ST_CTRL_R |= (0x01 << 0 );

	while(1){

		//check if time-out occurs
		if ((NVIC_ST_CTRL_R&0x10000)==1){
					
			if ((NVIC_ST_CTRL_R&0x10000) ==1){
						NVIC_ST_RELOAD_R = (16000000 - 1) ;
						NVIC_ST_CTRL_R |= (0x01 << 0 );
								
				//toggling the value of PORT F pin 2
				GPIO_PORTF_DATA_R ^= (0x1<<2);
			}	
		}
			
	}	
}

void delay(unsigned long loops){
		volatile unsigned long i;
		for(i =0; i< loops; i++);	
}
