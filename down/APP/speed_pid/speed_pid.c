#include "speed_pid.h"
#include "motor.h"
#include "Kinematic.h"

#define IntegralUpperLimit    5000    //底盘抗积分饱和值
#define Integralgimbal        500     //云台积分饱和值
#define IntegralSeparation    300     //底盘积分分离
#define vPID_OUT_MAX          8000		//即最大电流
#define gPID_OUT_MAX          30000   //云台pid输出限幅
#define gimbal_angel_upperlimit  500  //云台抗积分饱和值
#define gimbal_angel_downlimit   20   //云台积分分离
#define tvPID_OUT_MAX         9000    //拨弹轮

int pid_flag_start=1;
int pid_flag_end=0;

int vpid_out_max=vPID_OUT_MAX;
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
		
	if(vpid->err==0)
	{
   vpid->err_integration=0;
	}
	if(abs(vpid->err) <= IntegralSeparation)		//积分分离
			vpid->err_integration += vpid->err;
	if(vpid->err_integration > IntegralUpperLimit)		//抗积分饱和
		vpid->err_integration = IntegralUpperLimit;
	else if(vpid->err_integration < -IntegralUpperLimit)
		vpid->err_integration = -Integralgimbal;
	
	vpid->P_OUT = kp * vpid->err;								//P项
	vpid->I_OUT = ki * vpid->err_integration;		//I项
	
	//输出限幅
	if((vpid->P_OUT + vpid->I_OUT )> vPID_OUT_MAX) 
		vpid->PID_OUT = vPID_OUT_MAX;
	else if((vpid->P_OUT + vpid->I_OUT ) < -vPID_OUT_MAX) 
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

/*	power_limitation_jugement();
	power_limitation_coefficient();*/
	
}

void tvpid_realize(VPID_t *vpid,float kp,float ki)
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
	if((vpid->P_OUT + vpid->I_OUT) > tvPID_OUT_MAX) 
		vpid->PID_OUT = tvPID_OUT_MAX;
	else if((vpid->P_OUT + vpid->I_OUT) < -tvPID_OUT_MAX) 
		vpid->PID_OUT = -tvPID_OUT_MAX;
	else
		vpid->PID_OUT = vpid->P_OUT + vpid->I_OUT;
}
void tvpid_PI_realize(float kp,float ki)
{
	//读取电机当前转速
	
	motor5.vpid.actual_speed = motor5.actual_speed;
	

	//计算输出值
	vpid_realize(&motor5.vpid,kp,ki);

	
	
	
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

void set_GIMBAL_angle(int gimbal1_angle,int gimbal2_angle)
{
	gimbal1.apid.target_speed = gimbal1_angle;  //angel是速度
	//gimbal1.apid.target_angle = gimbal1_angle;
}

void set_trigger_motor_speed(int motor5_speed)
{
	motor5.vpid.target_speed = motor5_speed;
	
	motor5.target_speed = motor5_speed;	
	

}
void set_gimbal1_motor_speed(int gimbal1_speed)
  {
	gimbal1.vpid.target_speed = gimbal1_speed;
	gimbal1.target_speed = gimbal1_speed;		
	
	}


/*********************************************云台pid部分*******************************************************/
void apid_GIMBAL_realize(APID_t *vpid,float kpa,float kia,float kda)
{
	vpid->err = vpid->target_speed - vpid->actual_speed;
	//vpid->err = vpid->target_angle - vpid->actual_angle;
	
	if(vpid->err==0)
	{
   vpid->err_integration=0;
	}
	if(abs(vpid->err) <= gimbal_angel_downlimit)		//积分分离
			vpid->err_integration += vpid->err;
//	if(vpid->err_integration > gimbal_angel_upperlimit)		//抗积分饱和
	//	vpid->err_integration = Integralgimbal;
	//else if(vpid->err_integration < -gimbal_angel_upperlimit)
		//vpid->err_integration = -Integralgimbal;
	
	vpid->P_OUT = kpa * vpid->err;								//P项
	vpid->I_OUT = kia * vpid->err_integration;		//I项
	vpid->D_OUT = kda * (vpid->err-vpid->last_err);//D项
	vpid->last_err=vpid->err;
	//输出限幅
	if((vpid->P_OUT + vpid->I_OUT + vpid->D_OUT)> gPID_OUT_MAX) 
		vpid->PID_OUT = gPID_OUT_MAX;
	else if((vpid->P_OUT + vpid->I_OUT + vpid->D_OUT) < -gPID_OUT_MAX) 
		vpid->PID_OUT = -gPID_OUT_MAX;
	else
		vpid->PID_OUT = vpid->P_OUT + vpid->I_OUT + vpid->D_OUT;
  
  
}

void apid_GIMBAL_PI_realize(float kpa,float kia,float kda)
{
	//读取电机当前转速
	gimbal1.apid.actual_speed = gimbal1.actual_speed;
	gimbal1.apid.actual_angle = gimbal1.actual_angle;
	//计算输出值
	apid_GIMBAL_realize(&gimbal1.apid,kpa,kia,kda);
}

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

int pid_auto(void)
{
	int a=0;
   if(gimbal1.actual_angle>=2048&&gimbal1.actual_angle<=6144&&pid_flag_start)
	 {
	   a=60;
	 }
	 if(gimbal1.actual_angle>=2048&&gimbal1.actual_angle<=6144&&pid_flag_end)
	 {
		 a=-60;
	 }
   if(gimbal1.actual_angle<2048&&gimbal1.actual_angle>2008)
	 {
	 a=0;
	 }
	 if(gimbal1.actual_angle<6184&&gimbal1.actual_angle>6144)
	 {
	 a=0;
	 }

	 if(gimbal1.actual_angle>=6184)
	 {
	   a=0;
		 pid_flag_start=0;
		 pid_flag_end=1;
	 }
	 if(gimbal1.actual_angle<=2008)
	 {
	  a=0;
		pid_flag_start=1;
		pid_flag_end=0;
	 } 
	 return a;
}

int pid_pc(void)
{
	int a = 0;
/*if(gimbal1.actual_angle>=2730&&gimbal1.actual_angle<=5462&&pid_flag_start)
{
	a=5462-gimbal1.actual_angle;
}
if(gimbal1.actual_angle<=5462&&gimbal1.actual_angle>=2730&&pid_flag_end)
{
	a=2730-gimbal1.actual_angle;
}
if(gimbal1.actual_angle>5470)
{
	a=0;
	pid_flag_start=0;
  pid_flag_end=1;
}
if(gimbal1.actual_angle<2720)
{
	a=0;
	pid_flag_start=1;
  pid_flag_start=0;
}
else
{
a=0;
}*/
a=4096-gimbal1.actual_angle;
a=a*0.0347624*3;
return a;
}
