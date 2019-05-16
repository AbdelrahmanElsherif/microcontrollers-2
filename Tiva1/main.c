#include "tm4c123gh6pm.h"
#include "PWM.h"
#include "ana.h"
#include "UART.h"
#include "ADC.h"
#include "delay.h"
#include "led_rgb.h"

uint16_t temp;

int main (void) {
	led_rgb_init();
	UART_init();
	PWM_init();
	ADC0_Init_temp();
	Wtimer_init();
	while(1) {
		ADC0_PSSI_R = 0X01 << 3;
		temp = 147 - (247*ADC0_SSFIFO3_R)/4096;
		ADC0_ISC_R=(1<<3);			
	}
}
