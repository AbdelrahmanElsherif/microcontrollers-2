#ifndef PWM_H
#define PWM_H

#include "tm4c123gh6pm.h"

#define GPIO_PF2_M	0x04

void PWM_init(void);
void Rotate(char degree);
void Motor_SetDutyCycle(uint16_t duty_cycle);
void LED_SetDutyCycle(uint16_t duty_cycle);

#endif
