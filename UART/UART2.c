
 #include "lm3s9b92.h"
#include "inc/hw_types.h"
#include "driverlib/timer.h"
#include "inc/hw_memmap.h"
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

 

void delay(unsigned long);
void myISR(void);

int main(){
int i ;
int day=0;
 
      SysCtlClockSet(SYSCTL_SYSDIV_1|SYSCTL_USE_OSC|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
      
      //enable peripheral clock for UART0
      SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

      //enable peripheral clock for PORT A
      SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

      delay(5);

      GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0);
      GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_1);
    
      // disable UART
      UARTDisable(UART0_BASE);
      
      // set UART0 configurations.
      UARTConfigSetExpClk(UART0_BASE,SysCtlClockGet(),2400,(UART_CONFIG_WLEN_8| UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE));

      // regist ISR function
      UARTIntRegister(UART0_BASE,myISR); 

      // enable FIFO
      UARTFIFOEnable(UART0_BASE);

      // set interrupt levels for TX FIFO and RX FIFO
      UARTFIFOLevelSet(UART0_BASE,UART_FIFO_TX1_8,UART_FIFO_RX1_8);

      //initialize UARTStdio
      UARTStdioInitExpClk(0,2400);

      // enable individual UART interrupt source
      UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

      //enable UART0 interupt
      IntEnable(INT_UART0);

      // enable processor interrupt
      IntMasterEnable(); 

      // enable UART
      UARTEnable(UART0_BASE);
     
      UARTprintf("\n  SUN  MON  TUE  WED  THU  FRI  SAT"); 
      UARTprintf("\n");

     for(i=0; i <31 ; i++){
      if((i+day)%7 == 0) // 출력될 차례가 일요일이면, 개행
        UARTprintf("\n");

      else // 날짜 출력
            UARTprintf("%6d",i);

     }
  UARTprintf("\n\n");

      while(1){;}
 
       
       
   return 0;

}

void delay(unsigned long loops){
     volatile unsigned long i;
     for(i = 0 ; i < loops ; i++);
}


void myISR(void){

    long data;
    int i;


     if(UARTCharsAvail(UART0_BASE)){

          data = UARTCharGet(UART0_BASE);

          if(data == 0x0D)
           UARTCharPut(UART0_BASE,0x0A);
           for(i = 0 ; i < 40 ; i++){         
           UARTCharPut(UART0_BASE,data);
           }
     }
}
