#ifndef __ADC_H__
#define __ADC_H__

#include <stdint.h>
#define ADC_RESOLUTION	(3.3 / 4096)

void Wtimer_init(void);
void ADC0_Init_temp(void);


extern uint16_t data ;

#endif // __ADC_H__
