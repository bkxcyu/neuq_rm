
/*****     此文件专门用来放各个初始化函数    *****/

#include "My_Init.h"
#include "stm32f4xx_rcc.h"
#include "delay.h"
#include "key.h"
#include "LED.h"
#include "myflash.h"
#include "timer.h"
#include "buzzer.h"
#include "can.h"
#include "power.h"
#include "fric.h"
#include "motor.h"
#include "speed_pid.h"
#include "angle_pid.h"
#include "DJi_remote.h"
#include "FS_remote.h"
#include "remote_code.h"
#include "bsp_debug_usart.h"
#include "bsp_uart7.h"
#include "gimbal.h"
#include "bsp_imu_usart.h"

RCC_ClocksTypeDef get_rcc_clock;		//系统时钟结构体

// 函数: All_Init()
// 描述: 机器人所有参数初始化
// 参数：无
// 输出：无
void All_Init()
{
	Stm32_Clock_Init(360,12,2,8);				//设置时钟,180Mhz = 12M / 25 * 350 / 2
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	
	delay_init(180);									//延时初始化
	
	power_init();										  //电机电源初始化，默认为关
	power_open_all();									//开启所有电机电源
	
	if((Control_Mode&DJi_Remote_Control) == DJi_Remote_Control)					//大疆遥控器
		Dji_Remote_Init();									//大疆遥控器初始化
	else if((Control_Mode&FS_Remote_Control) == FS_Remote_Control)					//富斯遥控器
		FS_Remote_Init();										//富斯遥控器初始化

	led_init();											//led初始化
	key_init();											//按键初始化

	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_4tq,CAN_BS1_4tq,5,CAN_Mode_Normal);				//can初始化（电机初始化） 45M/(4+4+1)/5
	CAN2_Mode_Init(CAN_SJW_1tq,CAN_BS2_4tq,CAN_BS1_4tq,5,CAN_Mode_Normal);				//can初始化（电机初始化） 45M/(4+4+1)/5

	Debug_USART_Config();           //通信串口初始化（USART2）
	JSON_USART_Config();           	//主从控通信串口初始化（UART7）
	
	motor_init();		//电机参数初始化
	fric_PWM_configuration();       //摩擦轮电机pwm初始化   TIM1 /*******************************/新增
	TIM1_GIMBAL_Init();

	TIM3_Int_Init(10-1,9000-1);		  //定时器时钟90M，9000，所以90M/9000=10Khz的计数频率，计数10次为1ms  即1khz
	//TIM12_PWM_Init(1000-1,90-1);		//90M/90约1Mhz的计数频率,重装载值1000，所以PWM频率为 1M/400=2.5Khz. 
  TIM4_Int_Init(100-1,9000-1);
  bsp_imu_usart_init();
	VPID_Init_All();								//速度pid参数初始化
	APID_Init_All();								//角度pid参数初始化

	ap_pid_flag = ang_pid;									//位置角度闭环选择标志
	stop_chassis_motor();									//让电机保持当前角度（锁死电机）

	RCC_GetClocksFreq(&get_rcc_clock); 			//查看系统时钟(watch中)
	
	
}
