#include "PWM.h"
#include "ana.h"

double micro_sec = 0;

void PWM_init(void) {
	SYSCTL_RCGCPWM_R |= 0x01 << 1;
	
	SYSCTL_RCGCGPIO_R |= 0x01 << 5;
	
	SYSCTL_RCGCGPIO_R |= 0x01 << 0;

	SYSCTL_RCC_R |= 0x01 << 20;
	SYSCTL_RCC_R |= 4 << 17;
	for(short i = 0; i < 1000; i++) {
	}
	
	PWM1_3_CTL_R = 0x00000000;
	PWM1_3_GENA_R = 0x0000008C; // Drive PWM High at reload value and drive it to zero when it matches CMP
	PWM1_3_LOAD_R = 99;
	PWM1_3_CMPA_R = 98; // 0% Duty Cycle
	PWM1_3_CTL_R = 1;	
	GPIO_PORTF_AFSEL_R |= 0x01 << 2;
	GPIO_PORTF_PCTL_R = 0x5 << 8;
	GPIO_PORTF_DIR_R |= 0x01 << 2;
	GPIO_PORTF_DEN_R |= 0x01 << 2;
	
	PWM1_1_CTL_R = 0x00000000;
	PWM1_1_GENA_R = 0x0000008C; // Drive PWM High at reload value and drive it to zero when it matches CMP
	PWM1_1_LOAD_R = 9999;
	PWM1_1_CMPA_R = 9599;
	PWM1_1_CTL_R = 1;	
	GPIO_PORTA_AFSEL_R |= 0x01 << 6;
	GPIO_PORTA_PCTL_R = 0x5 << 24;
	GPIO_PORTA_DIR_R |= 0x01 << 6;
	GPIO_PORTA_DEN_R |= 0x01 << 6;
	
	PWM1_ENABLE_R |= 0x01 << 6 | 0x01 << 2; // M1PWM6 (PF2)
}

// Duty cycle as percentage
void LED_SetDutyCycle(uint16_t duty_cycle){
	if(duty_cycle == 100){
		PWM1_3_CMPA_R = 99;
	} else if(duty_cycle == 0) {
		PWM1_3_CMPA_R = 98;
	}else {
		PWM1_3_CMPA_R = (uint16_t)(100 * (1 - (duty_cycle / 100.0)) - 1);
	}
}

void Rotate(char degree) {
	micro_sec = 15*degree+800;
	Motor_SetDutyCycle(micro_sec/200);
}

void Motor_SetDutyCycle(uint16_t duty_cycle){
	if(duty_cycle == 100){
		PWM1_1_CMPA_R = 9999;
	} else if(duty_cycle == 0) {
		PWM1_1_CMPA_R = 9998;
	}else {
	PWM1_1_CMPA_R = (uint16_t)(10000 * (1 - (duty_cycle / 100.0)) - 1);
	}
}
