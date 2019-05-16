#include "tm4c123gh6pm.h"
#include "delay.h"
#include "LCD.h"
#include "led_rgb.h"
#include "ADC.h"
#include "stdint.h"
#include "UART.h"

#define ADC0_PSSI_SS3			(0x1 << 3)
extern char data_uart;
uint16_t temp;


void SystemInit(void){
	
}


int main()
	{
	SYSCTL_RCGCADC_R |= SYSCTL_RCGCADC_R0;  																								//	enable adc1
	SYSCTL_RCGCWTIMER_R|= 1;
	UART_init();

	while(1)
	{
		//ADC CONVERSION OF TEMP SENSOR 
		ADC0_PSSI_R = ADC0_PSSI_SS3;									//START OF CONVERSION 																				
		while((ADC0_RIS_R&8)==0);									//WAIT FOR COMPLETION OF CONVERSION 
		temp = 147 - (247 * ADC0_SSFIFO3_R) / 4096;							//TEMP. CALCULATION 
		ADC0_ISC_R = (1<<3);										//CLEAR FLAG FOR END OF CONVERSION 

		send_byte((uint8_t)temp);									//SENDING DATA BY UART 
		
	}
}


