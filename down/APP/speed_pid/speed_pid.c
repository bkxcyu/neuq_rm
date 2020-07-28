#include "speed_pid.h"
#include "motor.h"
#include "power_limitation.h"

#define IntegralUpperLimit    5000
#define IntegralSeparation    300
#define vPID_OUT_MAX          8000		//即最大电流
#define gimbal_angel_upperlimit  2000  //云台位置环上限
#define gimbal_angel_downlimit   200  //云台位置环下下限

int find_max(void);

// 函数: VPID_Init()
// 描述: 电机转速pid参数初始化
// 参数：速度参数结构体
// 输出：无
// 内部函数，用户无需调用
void VPID_Init(VPID_t *vpid)
{
	vpid->target_speed=0;
	vpid->actual_speed=0;
	vpid->err=0;
	vpid->last_err=0;
	vpid->err_integration=0;
	vpid->P_OUT=0;
	vpid->I_OUT=0;
	vpid->PID_OUT=0;
}

// 函数: VPID_Init_All()
// 描述: 四..个电机速度初始化
// 参数：无
// 输出：无
void VPID_Init_All()	
{
	VPID_Init(&motor1.vpid);
	VPID_Init(&motor2.vpid);
	VPID_Init(&motor3.vpid);
	VPID_Init(&motor4.vpid);
	VPID_Init(&motor5.vpid);
}


// 函数: vpid_realize()
// 描述: 速度pid计算
// 参数：速度pid参数结构体，速度pid的p和i，微分项不需要
// 输出：无
// 内部函数，用户无需调用
void vpid_realize(VPID_t *vpid,float kp,float ki)
{
	vpid->err = vpid->target_speed - vpid->actual_speed;
	
	if(abs(vpid->err) <= IntegralSeparation)		//积分分离
		vpid->err_integration += vpid->err;
	if(vpid->err_integration > IntegralUpperLimit)		//抗积分饱和
		vpid->err_integration = IntegralUpperLimit;
	else if(vpid->err_integration < -IntegralUpperLimit)
		vpid->err_integration = -IntegralUpperLimit;
	
	vpid->P_OUT = kp * vpid->err;								//P项
	vpid->I_OUT = ki * vpid->err_integration;		//I项
	
	//输出限幅
	if((vpid->P_OUT + vpid->I_OUT) > vPID_OUT_MAX) 
		vpid->PID_OUT = vPID_OUT_MAX;
	else if((vpid->P_OUT + vpid->I_OUT) < -vPID_OUT_MAX) 
		vpid->PID_OUT = -vPID_OUT_MAX;
	else
		vpid->PID_OUT = vpid->P_OUT + vpid->I_OUT;
}


// 函数: vpid_PI_realize()
// 描述: 电机转速pid实现
// 参数：电机转速pid的p和i，微分项不需要
// 输出：无
void vpid_PI_realize(float kp,float ki)
{
	//读取电机当前转速
	motor1.vpid.actual_speed = motor1.actual_speed;
	motor2.vpid.actual_speed = motor2.actual_speed;
	motor3.vpid.actual_speed = motor3.actual_speed;
	motor4.vpid.actual_speed = motor4.actual_speed;
	

	//计算输出值
	vpid_realize(&motor1.vpid,kp,ki);
	vpid_realize(&motor2.vpid,kp,ki);
	vpid_realize(&motor3.vpid,kp,ki);
	vpid_realize(&motor4.vpid,kp,ki);
	
	/******************功率控制方案*************************/

	power_limitation_jugement();
	power_limitation_coefficient();
	
}

// 函数: set_motor_speed()
// 描述: 设置目标速度
// 参数：4个电机的目标速度
// 输出：无
void set_chassis_motor_speed(int motor1_speed,int motor2_speed,int motor3_speed,int motor4_speed)
{
	motor1.vpid.target_speed = motor1_speed;		//因为电机方向相反  所以加负号
	motor2.vpid.target_speed = motor2_speed;
	motor3.vpid.target_speed = motor3_speed;
	motor4.vpid.target_speed = motor4_speed;
	
	
	
	motor1.target_speed = motor1_speed;		//因为电机方向相反  所以加负号
	motor2.target_speed = motor2_speed;
	motor3.target_speed = motor3_speed;
	motor4.target_speed = motor4_speed;
	

	
}
void set_trigger_motor_speed(int motor5_speed)
{
	//motor5.vpid.target_speed = motor5_speed;
	
	motor5.target_speed = motor5_speed;	
	

}
/*********************************************云台pid部分*******************************************************/
/*void apid_GIMBAL_realize(VPID_t *vpid,float kpa,float kia,float kpv,float,kiv)
{
	vpid->err = vpid->target_angel - vpid->actual_angel;
	
	if(abs(vpid->err) <= gimbal_angel_downlimit)		//积分分离
		vpid->err_integration += vpid->err;
	if(vpid->err_integration > gimbal_angel_upperlimit)		//抗积分饱和
		vpid->err_integration = IntegralUpperLimit;
	else if(vpid->err_integration < -gimbal_angel_upperlimit)
		vpid->err_integration = -gimbal_angel_upperlimit;
	
	vpid->P_OUT = kpa * vpid->err;								//P项
	vpid->I_OUT = kia * vpid->err_integration;		//I项
	
	//输出限幅
	if((vpid->P_OUT + vpid->I_OUT) > vPID_OUT_MAX) 
		vpid->PID_OUT = vPID_OUT_MAX;
	else if((vpid->P_OUT + vpid->I_OUT) < -vPID_OUT_MAX) 
		vpid->PID_OUT = -vPID_OUT_MAX;
	else
		vpid->PID_OUT = vpid->P_OUT + vpid->I_OUT;
	
		vpid->err = vpid->P_OUT + vpid->I_OUT;
	if(abs(vpid->err) <= gimbal_angel_downlimit)		//积分分离
		vpid->err_integration += vpid->err;
	if(vpid->err_integration > gimbal_angel_upperlimit)		//抗积分饱和
		vpid->err_integration = IntegralUpperLimit;
	else if(vpid->err_integration < -gimbal_angel_upperlimit)
		vpid->err_integration = -gimbal_angel_upperlimit;
	
	vpid->P_OUT = kpv * vpid->err;								//P项
	vpid->I_OUT = kiv * vpid->err_integration;		//I项
	
	//输出限幅
	if((vpid->P_OUT + vpid->I_OUT) > vPID_OUT_MAX) 
		vpid->PID_OUT = vPID_OUT_MAX;
	else if((vpid->P_OUT + vpid->I_OUT) < -vPID_OUT_MAX) 
		vpid->PID_OUT = -vPID_OUT_MAX;
	else
		vpid->PID_OUT = vpid->P_OUT + vpid->I_OUT;
}

void apid_GIMBAL_PI_realize(float kpa,float kia,float kpv,float kiv)
{
	//读取电机当前转速
	gimbal1.vpid.actual_speed = gimbal1.actual_speed;
	gimbal2.vpid.actual_speed = gimbal2.actual_speed;
	//计算输出值
	apid_GIMBAL_realize(&gimbal1.vpid,kpa,kia,kpv,kiv);
	apid_GIMBAL_realize(&gimbal2.vpid,kpa,kia,kpv,kiv);
}
*/
/*************************************************云台pid部分******************************************************/

// 函数: abs()
// 描述: 自定义的求绝对值函数，因为math.h里的不好用
// 参数：input
// 输出：|input|
int abs(int input)
{
	if(input<0)
		input = -input;
	return input;
}

