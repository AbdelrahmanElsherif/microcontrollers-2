#include "tm4c123gh6pm.h"
#include "ADC.h"
#include "led_rgb.h"
#include "LCD.h"
#include <stdint.h>

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

uint16_t data ;


//ADC FOR INTERNAL TEMPERATURE SENSOR 

void Wtimer_init(void)
{
	
	WTIMER0_CTL_R = 0;
	WTIMER0_CFG_R = 0x04;
	WTIMER0_TAMR_R =0x02;
	WTIMER0_TAILR_R = 16000000 ;
	WTIMER0_CTL_R |= 0x20;
	WTIMER0_CTL_R |=0x01;
	
}

void ADC0_Init_temp(void){
		

	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;																		//enable clock of port E
	ADC0_SSPRI_R = (ADC0_SS3_PRI | ADC0_SS2_PRI | ADC0_SS1_PRI | ADC0_SS0_PRI);		//enable 3 sample sequencers
	ADC0_ACTSS_R &= ~ADC0_ACTSS_SS3;																						//clear bit of ss3 for configuring ss3
	ADC0_EMUX_R &= ~(0xF000) | 0x50;																						//trigger source is timer 
	//ADC0_SSMUX3_R = ADC0_SSMUX3_Channel0;																				// Channel 0 AIN0 PE3
	ADC0_SSCTL3_R |= (ADC0_SSCTL3_IE0 | ADC0_SSCTL3_END0 | ADC0_SSCTL3_TS);			//Internal temp sensor & Enabling interrupt & and setting that we're sending one sample 
	ADC0_ACTSS_R |= ADC0_ACTSS_SS3;																							//Enabling SS3
}

