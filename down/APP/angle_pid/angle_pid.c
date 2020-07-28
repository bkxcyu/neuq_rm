#include "angle_pid.h"
#include "motor.h"
#include <math.h>
#include "speed_pid.h"

#define IntegralUpperLimit    2000		//积分上限
#define IntegralSeparation    200			//积分分离阈值 
#define aPID_OUT_MAX          1000		//即最大速度
int ap_pid_flag = ang_pid;	//角度和位置pid标志

// 函数: APID_Init()
// 描述: 电机机械角度pid参数初始化
// 参数：电机机械角度pid参数结构体
// 输出：无
// 内部函数，用户无需调用
void APID_Init(APID_t *apid)
{
	apid->actual_angle=0;
	apid->target_angle=0;
	apid->err=0;
	apid->last_err=0;
	apid->err_integration=0;
	apid->P_OUT=0;
	apid->I_OUT=0;
	apid->D_OUT=0;
	apid->PID_OUT=0;
}

// 函数: APID_Init_All()
// 描述: 所有电机机械角度pid参数初始化
// 参数：无
// 输出：无
void APID_Init_All()
{
	APID_Init(&motor1.apid);
	APID_Init(&motor2.apid);
	APID_Init(&motor3.apid);
	APID_Init(&motor4.apid);
	
 APID_Init(&motor5.apid);
	
}
//if(ptr->angle - ptr->last_angle > 4096)
//	ptr->round_cnt --;
//else if (ptr->angle - ptr->last_angle < -4096)
//	ptr->round_cnt ++;
//	ptr->total_angle = ptr->round_cnt * 8192 + ptr->angle - ptr->offset_angle;
// 函数: apid_realize()
// 描述: 电机机械角度pid计算
// 参数：电机机械角度pid参数结构体，电机机械角度pid系数
// 输出：无
// 内部函数，用户无需调用
void apid_realize(APID_t *apid,float kp,float ki,float kd)
{
	//偏差项
	apid->err = apid->target_angle - apid->actual_angle;
	//机械角度最大最小值跃迁处理
//	if(apid->err > 4096)
//		apid->err = apid->err - 8192;
//	if(apid->err < -4096)
//		apid->err = apid->err + 8192;
	
	//积分项
	if(abs(apid->err) <= IntegralSeparation)		//积分分离
		apid->err_integration += apid->err;
	if(apid->err_integration > IntegralUpperLimit)		//抗积分饱和
		apid->err_integration = IntegralUpperLimit;
	else if(apid->err_integration < -IntegralUpperLimit)
		apid->err_integration = -IntegralUpperLimit;
	
	//三项输出
	apid->P_OUT = kp * apid->err;
	apid->I_OUT = ki * apid->err_integration;
	apid->D_OUT = kd * (apid->err-apid->last_err);
	apid->last_err = apid->err;
	
	//输出限幅
	if((apid->P_OUT + apid->I_OUT + apid->D_OUT) > aPID_OUT_MAX) 			
		apid->PID_OUT = aPID_OUT_MAX;
	else if((apid->P_OUT + apid->I_OUT + apid->D_OUT) < -aPID_OUT_MAX) 
		apid->PID_OUT = -aPID_OUT_MAX;
	else
		apid->PID_OUT = apid->P_OUT + apid->I_OUT;
	
}

// 函数: apid_PID_realize()
// 描述: 电机机械角度pid实现
// 参数：电机机械角度pid系数
// 输出：无
void apid_PID_realize(float kp,float ki,float kd)
{
	//读取当前角度值
	motor1.apid.actual_angle = motor1.total_angle;
	motor2.apid.actual_angle = motor2.total_angle;
	motor3.apid.actual_angle = motor3.total_angle;
	motor4.apid.actual_angle = motor4.total_angle;
	motor5.apid.actual_angle = motor5.total_angle;
	
	//计算电机机械角度pid
	apid_realize(&motor1.apid,kp,ki,kd);
	apid_realize(&motor2.apid,kp,ki,kd);
	apid_realize(&motor3.apid,kp,ki,kd);
	apid_realize(&motor4.apid,kp,ki,kd);
	apid_realize(&motor5.apid,kp,ki,kd);
	
	
	//设置电机目标速度
	set_chassis_motor_speed(motor1.apid.PID_OUT,motor2.apid.PID_OUT,motor3.apid.PID_OUT,motor4.apid.PID_OUT);
}
//设置电机目标机械角度
void set_chassis_motor_angle(int motor1_angle,int motor2_angle,int motor3_angle,int motor4_angle)
{
	
	motor1.apid.target_angle = motor1_angle;
	motor2.apid.target_angle = motor2_angle;
	motor3.apid.target_angle = motor3_angle;
	motor4.apid.target_angle = motor4_angle;
}
void set_trigger_motor_angle(int motor5_angle)
{
	
	motor5.apid.target_angle = motor5_angle;

}
