#ifndef __PWM_H
#define __PWM_H


void TIM1_IRQHandler(void);
void TIM1_GIMBAL_Init(void);
extern float pwm_pulse1;
extern float pwm_pulse2;
#endif
