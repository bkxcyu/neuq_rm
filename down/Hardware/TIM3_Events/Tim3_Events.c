
/*****    此文件专门用来放TIM3定时器中断中运行的函数   ******/
#include <string.h>
#include <stdio.h>

#include "Tim3_Events.h"
#include "key.h"
#include "led.h"
#include "bsp_debug_usart.h"
#include "bsp_uart7.h"
#include "fric.h"
#include "motor.h"
#include "kinematic.h"
#include "remote_code.h"
#include "angle_pid.h"
#include "speed_pid.h"
#include "stm32f4xx_tim.h"
#include "gimbal.h"
#include "json.h"
#include "kinematic.h"
//无线要发送的数据


 //Pid_parameter Chassis,Gimbal,Trigger;
float kp=580,ki=0,kd=0.1;//kp=700左右,ki=0.03,kd=0.1;
int pid_target_speed=0;
int pid_target_angle=4096;
//按键宏定义   增强代码可读性
#define pressed     0
#define unpressed   1

// 函数: Robo_Control()
// 描述: 机器人运动函数，计算机器人pid和遥控器信号解析
// 参数：无
// 输出：无
void Robo_Move()
{
	if(stop_flag_1 && ap_pid_flag == ang_pid)			//如果此时速度为0（停止）或者自动控制时没有在运行位置闭环   那么角度闭环
	{	
		break_jugement();
		if(stop_flag_3 && 1)
		{
			stop_chassis_motor();
		}
		apid_PID_realize(0.2,0.05,0);			
	
	}
  if(/*(Control_Mode) ==*/ 1 /*0x03*/)//((Control_Mode & auto_control) == auto_control)
	{
		speed_control(Kinematics.target_velocities.linear_x, Kinematics.target_velocities.linear_y, Kinematics.target_velocities.angular_z);		
		gimbal_control(Kinematics.target_angular.gimbal_angular.yaw_angular,Kinematics.target_angular.gimbal_angular.pitch_angular);
		//auto_fire();//上位机发送标志位  开火
	}
 
	
   	vpid_PI_realize(2,0.05);			//速度闭环2  0.05
	  tvpid_PI_realize(2.5,0.05);      //拨弹轮速度闭环  参数未确定   2.5  0.05
	  apid_GIMBAL_PI_realize(kp,ki,kd);     //
		set_chassis_current();		//设定电机电流
	  set_trigger_current();
	  set_gimbal_current();

	  TIM_SetCompare1(TIM1,pwm_pulse1);
		TIM_SetCompare2(TIM1,pwm_pulse2);

	  
}
union {float fvalue;char data[4];}tmp1;
//底盘信息转换成十六进制数发出去
void send_chassis_info_by_hex(void)//**************************未用到
{
	char str[17];
	str[0] = 0x55;
	tmp1.fvalue = Kinematics.actual_velocities.linear_x;
	str[1] = tmp1.data[0];
	str[2] = tmp1.data[1];
	str[3] = tmp1.data[2];
	str[4] = tmp1.data[3];
	tmp1.fvalue = Kinematics.actual_velocities.linear_y;
	str[5] = tmp1.data[0];
	str[6] = tmp1.data[1];
	str[7] = tmp1.data[2];
	str[8] = tmp1.data[3];
	tmp1.fvalue = Kinematics.actual_velocities.angular_z;
	str[9] = tmp1.data[0];
	str[10] = tmp1.data[1];
	str[11] = tmp1.data[2];
	str[12] = tmp1.data[3];
	
	
//	memcpy(&str[1],&Kinematics.target_velocities.linear_x,4);
//	memcpy(&str[5],&Kinematics.target_velocities.linear_y,4);
//	memcpy(&str[9],&Kinematics.target_velocities.angular_z,4);
	str[13] = 0x56;
	str[14] = '\r';
	str[15] = '\n';
	for(char i=0;i<16;i++)
		Usart_SendByte( JSON_USART, str[i]);
	
	
};



// 函数: Debug_Key()
// 描述: 调试用的按键，即单片机上的白色按键
// 参数：无
// 输出：无
void Debug_Key()
{
	static int key_flag = unpressed;		//用于控制下面判断在按下的过程中只进入一次
	if( key_press() && key_flag == unpressed)		//如果按键被按下
	{
		LED4=!LED4;												//LED4反转，用于状态指示
		key_flag = pressed;			          //按键被按下
		// your codes below
		
		//NRF24L01_TxPacket(send_data);			//nrf发送字符串
	}
	else if(!key_press())
		key_flag=unpressed;		//按键未被按下
}


// 函数: Wireless_Tune_Para()
// 描述: 无线调参，具体内容未写
// 参数：无
// 输出：无
void Wireless_Tune_Para()
{
	LED3=!LED3;				//每接收到一帧数据LED3状态翻转，用于状态指示反馈
	
	//处理收到的数据receive_data
	
}

