#ifndef _ANGLE_PID_H
#define _ANGLE_PID_H

#define pos_pid     0x0001
#define ang_pid     0x0000
extern int ap_pid_flag;

void APID_Init_All(void);			//电机机械角度PID参数初始化
void apid_PID_realize(float kp,float ki,float kd);			//电机机械角度pid实现
void set_chassis_motor_angle(int moto1_angle,int moto2_angle,int moto3_angle,int moto4_angle);			//设置电机目标机械角度
void set_trigger_motor_angle(int moto8_angle);
#endif
