#ifndef __ADC_H__
#define __ADC_H__

#include <stdint.h>
#define ADC_RESOLUTION	(3.3 / 4096)

void ADC1_Init_pot(void);
//void ADC0_SS3_In_pot(uint16_t *data);
void Wtimer_init(void);
void ADC0_Init_temp(void);
//void ADC1SS3_Handler(void);
//void ADC0_SS3_In_temp(uint16_t *temp);

extern uint16_t data ;

//void ADC0_SS3_In(uint16_t *data);

#endif // __ADC_H__
