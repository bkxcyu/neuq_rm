#ifndef _KINEMATIC_H
#define _KINEMATIC_H

#define wheel_diameter  10.000000f			//轮子直径
#define half_width  25.000000f		//底盘半宽
#define half_length  35.000000f		//底盘半长

#define PI 			3.141593f
#define RPM2RAD 0.104720f										//转速转角速度		1 rpm = 2pi/60 rad/s 
#define RPM2VEL 0.523599f										//转速转线速度		vel = rpn*pi*D/60  cm/s
#define VEL2RPM 1.909859f										//线速度转转度
#define M2006_REDUCTION_RATIO 36.000000f		//齿轮箱减速比
#define M3508_REDUCTION_RATIO 19.000000f		//齿轮箱减速比

typedef struct
{
	float kp;			
	float ki;						
}Pid_parameter;



typedef struct
{
	float linear_vel;			//线速度
	float rpm;						//转速圈每分钟
}Speed_t;

typedef struct
{
	Speed_t target_speed;			
	Speed_t actual_speed;						
}Wheel_t;

//底盘几何中心的线/角速度
typedef struct
{
	float linear_x;	//m/s
	float linear_y;
	float angular_z; //角速度rpm
}Velocities_t;
//新增
typedef struct
{
	float yaw_angular; 
	float pitch_angular;
	
}Gimbal_t;


typedef struct
{
	Gimbal_t gimbal_angular; 
	float fric_angular;
	float trigger_angular;
	
}Angular_t;


typedef struct
{
	Wheel_t wheel1;
	Wheel_t wheel2;
	Wheel_t wheel3;
	Wheel_t wheel4;
	
	Velocities_t target_velocities;		//目标速度
	Velocities_t actual_velocities;	//实际速度
  Angular_t  target_angular;
	Angular_t  actual_angular;
	
}Kinematics_t;
/****************************************************/








extern Kinematics_t Kinematics;
extern float max_base_linear_speed;
extern float max_base_rotational_speed;
extern Pid_parameter Chassis,Gimbal,Trigger;

extern int stop_flag_1;
extern int stop_flag_2;
extern int stop_flag_3; //新加入的，防止刹车过硬过载by LUO   666  by Q

void BaseVel_To_WheelVel(float linear_x, float linear_y, float angular_z);
void trigger_to_motor(float trigger_angular);
void Get_Base_Velocities(void);
void speed_control(float speed_x,float speed_y,float speed_r);		//将三个方向速度转换为电机转速
void trigger_control(float trigger_angular);
void gimbal_control(float gimbal1_angle,float gimbal2_angle);
void Gimbal_control(float gimbal1_speed);
float KalmanFilter(const float ResrcData,float ProcessNiose_Q,float MeasureNoise_R);
void break_jugement(void);  // by luo

#endif


