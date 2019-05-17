#include "tm4c123gh6pm.h"
#include "ADC.h"
#include "led_rgb.h"
#include "LCD.h"
#include <stdint.h>
#include "UART.h"

#define ADC0_SS0_PRI 			0x3
#define ADC0_SS1_PRI 			(0x2 << 4)
#define ADC0_SS2_PRI 			(0x1 << 8)
#define ADC0_SS3_PRI 			(0x0 << 12)
#define ADC0_ACTSS_SS3 		0x8
#define ADC0_EMUX_SS3			(0x0 << 12) // Processor Trigger
#define ADC0_SSMUX3_Channel0				0x0					// AIN0 (PE3)
#define ADC0_SSCTL3_IE0		(0x1 << 2)
#define ADC0_SSCTL3_END0	(0x1 << 1)
#define ADC0_PSSI_SS3			(0x1 << 3)
#define ADC0_RIS_INR3			(0x1 << 3)
#define GPIO_PE3_M				(0x1 << 3)
#define ADC0_SSCTL3_TS		(0x1 << 3)
//FOR POTENTIOMETER 
#define ADC1_SS0_PRI 			0x3
#define ADC1_SS1_PRI 			(0x2 << 4)
#define ADC1_SS2_PRI 			(0x1 << 8)
#define ADC1_SS3_PRI 			(0x0 << 12)
#define ADC1_ACTSS_SS3 		0x8
#define ADC1_EMUX_SS3			(0xF << 12) // continous Trigger
#define ADC1_SSMUX3_Channel1				0x1					// AIN1 (PE2)
#define ADC1_SSCTL3_IE0		(0x1 << 2)
#define ADC1_SSCTL3_END0	(0x1 << 1)
#define ADC1_PSSI_SS3			(0x1 << 3)
#define ADC1_RIS_INR3			(0x1 << 3)
#define GPIO_PE2_M				(0x1 << 2)
#define ADC1_SSCTL3_TS		(0x1 << 3)

uint16_t data ;


//ADC FOR POTENTIOMETER 
/*
void ADC1_Init_pot(void){
	
	short i;
	
	//SYSCTL_RCGCADC_R = (1<<1);  																								//	enable adc1
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;																		//	enable clock of port E
	
	for(i = 0; i < 1000; i++) {
	}
	
	GPIO_PORTE_DIR_R &= ~GPIO_PE2_M;																						// SETTING PE2 AS INPUT 												
	GPIO_PORTE_AFSEL_R |= GPIO_PE2_M;																						// configuring PE2
  GPIO_PORTE_DEN_R &= ~GPIO_PE2_M;
  GPIO_PORTE_AMSEL_R |= GPIO_PE2_M;
	ADC1_SSPRI_R = (ADC1_SS3_PRI | ADC1_SS2_PRI | ADC1_SS1_PRI | ADC1_SS0_PRI);	//	enable 4 sample sequencers
	ADC1_ACTSS_R &= ~ADC1_ACTSS_SS3;																						//	clear bit of ss3 for configuring ss3
	ADC1_EMUX_R = (ADC1_EMUX_R&0x0FFF) | (0xF << 12) ;													//	trigger source is continous  
	ADC1_SSMUX3_R = ADC1_SSMUX3_Channel1;																				// Channel 1 AIN1 PE2
	ADC1_SSCTL3_R |= (ADC1_SSCTL3_IE0 | ADC1_SSCTL3_END0);											// Enabling interrupt & and setting that we're sending one sample 
	ADC1_IM_R = (1<<3);																													//	SETTING INTERRUPT MASK FOR SS3
	ADC1_ACTSS_R |= ADC1_ACTSS_SS3;																							//	ENABLING SS3	
	while((ADC1_RIS_R&8)==0);	
	//led_rgb_set_color(0x0C);
	ADC1_ISC_R = (1<<3);																												//CLEARING INTERRUPT FLAG 			
	NVIC_EN1_R |= 0x01 << 19;	
}

void ADC1SS3_Handler(void){
	
		//led_////////////////rgb_set_color(0x0C);
		data= ADC1_SSFIFO3_R&0xFFF;																							// take data from first 12 bits 
		ADC1_ISC_R = (1<<3) ;	
}

//ADC FOR INTERNAL TEMPRETURE SENSOR 
*/
void Wtimer_init(void)
{
	SYSCTL_RCGCWTIMER_R  |= 0x01 << 0;
	for(short i = 0; i < 1000; i++) {
	}
	WTIMER0_CTL_R = 0;
	WTIMER0_CFG_R = 0x04;
	WTIMER0_TAMR_R =0x02;
	WTIMER0_TAILR_R = 16000000 ;
	WTIMER0_CTL_R |= 0x20;
	WTIMER0_CTL_R |=0x01;
	
}

void ADC0_Init_temp(void){
		short i;
	SYSCTL_RCGCADC_R |= 0x01;
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;																		//enable clock of port E
	for(i = 0; i < 1000; i++) {
	}
	ADC0_SSPRI_R = (ADC0_SS3_PRI | ADC0_SS2_PRI | ADC0_SS1_PRI | ADC0_SS0_PRI);	//enable 3 sample sequencers
	ADC0_ACTSS_R &= ~ADC0_ACTSS_SS3;																						//clear bit of ss3 for configuring ss3
	ADC0_EMUX_R = (ADC0_EMUX_R&0x0FFF) | (0xF << 12) ;																						//trigger source is timer 
	ADC0_SSMUX3_R = ADC0_SSMUX3_Channel0;																				// Channel 0 AIN0 PE3
	ADC0_SSCTL3_R |= (ADC0_SSCTL3_IE0 | ADC0_SSCTL3_END0 | ADC0_SSCTL3_TS);			//Internal temp sensor & Enabling interrupt & and setting that we're sending one sample 
	ADC0_IM_R = (1<<3);
	ADC0_ACTSS_R |= ADC0_ACTSS_SS3;																							//Enabling SS3
	while((ADC0_RIS_R&8)==0);
	ADC0_ISC_R = (1<<3);
	NVIC_EN0_R |= 0x01 << 17;
}

void ADC0SS3_Handler(void) {
	data= ADC0_SSFIFO3_R&0xFF;	// take data from first 8 bits 
	send_byte(data);
	ADC0_ISC_R = (1<<3) ;
}

