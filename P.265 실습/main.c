#include<lm3s9b92.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"

void delay(unsigned long);
void function();

int main(){
 
	 //configure system clock
	 SysCtlClockSet(SYSCTL_SYSDIV_1|SYSCTL_USE_OSC|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
	 
	 //enable peripheral clock for PROT F
	 SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	 
	 
	 //enable peripheral clock for timer0
	 SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	 
	 delay(5);
	 
	 //configure direction for PORT F pin2 and pin3 (as OUTPUT)
	 GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
	 GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
	 
	 //turn off LED(clear the pin2 of PORT F)
	 GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,(0x1<<2));
	 //turn on LED (clear the pin3 of PORT F)
	 GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,0x0);
	 
	 //configure timer0 to 32bit periodic timer
	 //TIMER0의 를 32bit로 늘리고 PERIODIC MODE로 설정한다.
	 TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
	 
	 //set up the timer0 load value for 2 sec
	 TimerLoadSet(TIMER0_BASE, TIMER_A, 32000000-1);
	 
	 //sub function 호출(ISR)
	 TimerIntRegister(TIMER0_BASE, TIMER_TIMA_TIMEOUT,function);
	 
	 //enable interrupt timeout
	 TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT); 
	 
	 //enable timer A of timer0
	 TimerEnable(TIMER0_BASE, TIMER_A);
	 
	 
	 //반복 수행될수있도록 while문으로 처리	
	  while(1){}
	 
}

//ISR
void function(){
 
       //clear TATORIS of Timer0
       TimerIntClear(TIMER0_BASE, TIMER_RIS_TATORIS);
       
       
       //toggle the value of PORT F pin2
       GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,~GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_2));
       
       //togle the value of PORT F pin3
       GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,~GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_3));
 
}
 
void delay(unsigned long loops){
  
  volatile unsigned long i;
     for(i =0; i< loops; i++);
 
}