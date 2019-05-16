#include "tm4c123gh6pm.h"
#include "PWM.h"
#include "delay.h"
#include "UART.h"
#include "led_rgb.h"
#include "LCD.h"

char data_uart = 0;
//int i = 0;

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
	LCD_goto(14, 0);
		LCD_puti(data_uart);
		delay_ms(500);
	UART1_ICR_R |= 0x01 << 4;
	//led_rgb_set_color(0x0C);
}

void send_byte(uint8_t one_byte){
	while((UART1_FR_R&0x20)!=0); //monitoring bit field 5 to check that
	UART1_DR_R=one_byte; //any previous transmission has completed or not
}

void send_str(unsigned char *buffer){
	while(*buffer!=0){
		send_byte(*buffer);
		buffer++;
	}
	send_byte('\n');
}
