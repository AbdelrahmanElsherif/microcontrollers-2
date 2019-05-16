#include "tm4c123gh6pm.h"
#include "PWM.h"
#include "delay.h"
#include "UART.h"
#include "led_rgb.h"

char data_uart = 0;
int i = 0;

void UART_init (void){
	SYSCTL_RCGCUART_R |= 2; //Enabling clock in run mode
	SYSCTL_RCGCGPIO_R |= 2; //Enabling the clock at PORTA in run mode
	UART1_CTL_R &= ~0x1; //uart disable during setting
	UART1_IBRD_R = 8; //int part @9600
	UART1_FBRD_R = 44; //float part
	UART1_LCRH_R |= ((1<<6)|(1<<5)|(1<<4));
	
	//enable inerrupt on receiving
	UART1_IM_R |= 0x01 << 4;
	//enable UART interrupts in the NVIC
	NVIC_EN0_R |= 0x01 << 6;
	
	UART1_CTL_R |= 0x1; //uart enable
	UART1_CTL_R |= UART_CTL_RXE;
	UART1_CTL_R |= UART_CTL_TXE;
	GPIO_PORTB_AFSEL_R|=0x3; //Enabling alternate function
	GPIO_PORTB_DEN_R|=0x3; //digital enable
	GPIO_PORTB_PCTL_R=((GPIO_PORTB_PCTL_R&0xFFFFFF00)+0x11);
	GPIO_PORTB_AMSEL_R &=~0x3;
}

void UART1_Handler() {
	data_uart = UART1_DR_R & 0xFF;
	if(data_uart == 'A') {
		if(i != 180) {
			//for(char degree = i; degree <= i+30; degree++) {
				Rotate(i+30);
				//delay_ms(20);
			//}
			led_rgb_set_color(green);
			i	 += 30;
		}
	}
	else if(data_uart == 'B') {
		
		if(i != 0) {
			//for(char degree = i; degree > i-30; degree--) {
				Rotate(i-30);
				//delay_ms(20);
			//}
			led_rgb_set_color(dark);
			i -= 30;
		}
	}
	else if(data_uart == 'Z') {
		while(UART1_FR_R & (0x01 << 4));
		LED_SetDutyCycle(UART1_DR_R);
	}
	UART1_ICR_R |= 0x01 << 4;
}

void send_byte(uint8_t one_byte){
	
	while((UART1_FR_R&0x20)!=0); //monitoring bit field 5 to check that
	//GPIO_PORTF_DATA_R |= 0x01 << 3;
	UART1_DR_R=one_byte; //any previous transmission has completed or not
}

void send_str(unsigned char *buffer){
	while(*buffer!=0){
		send_byte(*buffer);
		buffer++;
	}
	send_byte('\n');
}
