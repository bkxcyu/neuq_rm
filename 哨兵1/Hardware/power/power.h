#ifndef _POWER_H
#define _POWER_H

#define M1  1
#define M2  2
#define M3  3
#define M4  4

#define POWER_PORT 		GPIOH
#define POWER_PIN 		GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5
#define POWER_MODE    GPIO_Mode_OUT
#define POWER_OTYPE   GPIO_OType_PP
#define POWER_PuPd		GPIO_PuPd_UP
#define POWER_SPEED		GPIO_Speed_100MHz

#define M1_PIN        GPIO_Pin_2
#define M2_PIN        GPIO_Pin_3
#define M3_PIN        GPIO_Pin_4
#define M4_PIN        GPIO_Pin_5

void power_init(void);							//电机电源初始化，初始值为关闭
void power_open_all(void);					//打开所有电机电源
void power_close_all(void);					//关闭所有电机电源
void power_close_motor(int motor_num);		//关闭指定电机电源
void power_open_motor(int motor_num);			//打开指定电机电源


#endif
