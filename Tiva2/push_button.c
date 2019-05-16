#include "tm4c123gh6pm.h"
#include "PWM.h"
#include "ana.h"
#include "delay.h"
#include "UART.h"

int i = 0;

void Led() {
	GPIO_PORTF_DATA_R ^= 0x01 << 3;
}

void Push_Button_Init(void) {
	SYSCTL_RCGCGPIO_R |= 0x01 << 5;
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R |= 0x01 << 0 | 0x01 << 4 | 0x01 <<3;
	GPIO_PORTF_DIR_R |= 0x01 << 3;
	GPIO_PORTF_DEN_R |= 0x01 << 0 | 0x01 << 4 | 0x01 << 3;
	GPIO_PORTF_PUR_R |= 0x01 << 0 | 0x01 << 4;
	GPIO_PORTF_IM_R |= 0x01 << 0 | 0x01 << 4;
	NVIC_EN0_R |= 0x01 << 30;
}

void GPIOF_Handler(void) {
	if(GPIO_PORTF_RIS_R & 0x01) {
	
			send_byte('A');
		/*
		if(i != 180) {
			for(char degree = i; degree <= i+30; degree++) {
				Rotate(degree);
				delay_ms(20);
			}
		i	 += 30;
	}*/
		Led();
		GPIO_PORTF_ICR_R |= 0x01;
	}
	else if(GPIO_PORTF_RIS_R & (0x01 << 4)) {
		send_byte('B');
		/*if(i != 0) {
			for(char degree = i; degree > i-30; degree--) {
				Rotate(degree);
				delay_ms(20);
			}
			i -= 30;
	}*/
		Led();
		GPIO_PORTF_ICR_R |= 0x01 << 4;
	}
}
