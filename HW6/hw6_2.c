#include <lm3s9b92.h>

#include<inc/hw_types.h>
#include<inc/hw_memmap.h>
#include<driverlib/systick.h>
#include<driverlib/sysctl.h>
#include<driverlib.gpio.h>

void delay(unsigned long);
unsigned long SysTickStatusGet(void);

int main(){
	
	//configure system clock
	//this is the same as default configuration
	//use 16MHz main oscillator
	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	
	//enable peripheral clock for PortF
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	delay(5);
	
	//configure direction for Port F pin2(as output)
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_2);
	
	//setSysTick reload value (for 2 sec)
	SysTickPeriodSet(16000000);

	//enable systick and set up clock source
	SysTickEnable();

		while(1){

			//wait for time out
			while(!(SysTickStatusGet() & (0x1<<16)));
			
			//turn on LED 9 set data for Port F pin 2
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, (0x01<<2));
	
			//wait for time-out
			while(!(SysTickStatusGet() & (0x1<<16)));
			
			//turn off LED 9set data for Port F pin 2
			GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,0x00);
	
		}

}

void delay(unsigned long loops){

		volatile unsigned long i;
					for(i =0; i< loops; i++);
	
}


//you should make a code for the following subrountine
unsigned long SysTickStatusGet(void){

		unsigned long status = NVIC_ST_CTRL_R;

		return status;

}
