#include "tm4c123gh6pm.h"
#include "push_button.h"
#include "UART.h"
#include "LCD.h"
#include "delay.h"
#include "ADC.h"
#include "led_rgb.h"

extern char data_uart;
extern uint16_t data;

int main (void) {
	led_rgb_init();
	UART_init();
	LCD_ini(off_crs);
	LCD_clrscr();
	LCD_puts("Temperature = ");
	Push_Button_Init();
	ADC1_Init_pot();
	while(1) {
		LCD_goto(7, 0);
		LCD_puti(data_uart);
		delay_ms(500);
	}
}
