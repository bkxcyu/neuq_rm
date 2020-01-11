/**
  ******************************************************************************
  * @file    Project/APP/kinematic.c 
  * @author  Zhuge Huayang
  * @version V1.0.0
  * @date    2-December-2019
  * @brief   ���������˶�ѧ����
  *          ���ٶȵ�λ�� cm/s
  *          ���ٶȵ�λ�� rad/s
	*          ת�ٵ�λ��   rpm
  ******************************************************************************
  * @attention
  ******************************************************************************
  */


#include "kinematic.h"
#include "motor.h"

#include "speed_pid.h"
#include "angle_pid.h"


Kinematics_t Kinematics;

float max_base_linear_speed=0;		//����������ٶ�
float max_base_rotational_speed=0;		//���������ٶ�

//���˶�ѧ��ʽ
//����Ҫ�õ��ĵ����ٶ�ת��Ϊ���ӵ����ٶ�
void BaseVel_To_WheelVel(float linear_x, float linear_y, float angular_z)
{
//	Kinematics.target_velocities.linear_x  = linear_x;
//	Kinematics.target_velocities.linear_y  = linear_y;
//	Kinematics.target_velocities.angular_z = angular_z;
	
	Kinematics.wheel1.target_speed.linear_vel = 1.04f*(linear_y - linear_x + angular_z*(half_width + half_length));
	Kinematics.wheel2.target_speed.linear_vel = linear_y + linear_x - angular_z*(half_width + half_length);
	Kinematics.wheel3.target_speed.linear_vel = linear_y - linear_x - angular_z*(half_width + half_length);
	Kinematics.wheel4.target_speed.linear_vel = linear_y + linear_x + angular_z*(half_width + half_length);
	
	Kinematics.wheel1.target_speed.rpm = Kinematics.wheel1.target_speed.linear_vel * VEL2RPM;
	Kinematics.wheel2.target_speed.rpm = Kinematics.wheel2.target_speed.linear_vel * VEL2RPM;
	Kinematics.wheel3.target_speed.rpm = Kinematics.wheel3.target_speed.linear_vel * VEL2RPM;
	Kinematics.wheel4.target_speed.rpm = Kinematics.wheel4.target_speed.linear_vel * VEL2RPM;
	
	motor1.target_speed = - (int)(Kinematics.wheel1.target_speed.rpm * M2006_REDUCTION_RATIO);
	motor2.target_speed =   (int)(Kinematics.wheel2.target_speed.rpm * M2006_REDUCTION_RATIO);
	motor3.target_speed =   (int)(Kinematics.wheel3.target_speed.rpm * M2006_REDUCTION_RATIO);
	motor4.target_speed = - (int)(Kinematics.wheel4.target_speed.rpm * M2006_REDUCTION_RATIO);
	
};

void trigger_to_motor(float trigger_angular)
{
     
	motor5.target_speed =(int)(trigger_angular);//
	
}



//���˶�ѧ��ʽ
//ͨ����̥��ʵ��ת�ټ�����̼������ĵ������ٶ�
void Get_Base_Velocities(void)
{
	//���ݵ��ת�ٲ�������ת��
	Kinematics.wheel1.actual_speed.rpm = - motor1.actual_speed / M2006_REDUCTION_RATIO;
	Kinematics.wheel2.actual_speed.rpm =   motor2.actual_speed / M2006_REDUCTION_RATIO;
	Kinematics.wheel3.actual_speed.rpm =   motor3.actual_speed / M2006_REDUCTION_RATIO;
	Kinematics.wheel4.actual_speed.rpm = - motor4.actual_speed / M2006_REDUCTION_RATIO;
	//����ת��ת��Ϊ�������ٶ�
	Kinematics.wheel1.actual_speed.linear_vel = Kinematics.wheel1.actual_speed.rpm * RPM2VEL;
	Kinematics.wheel2.actual_speed.linear_vel = Kinematics.wheel2.actual_speed.rpm * RPM2VEL;
	Kinematics.wheel3.actual_speed.linear_vel = Kinematics.wheel3.actual_speed.rpm * RPM2VEL;
	Kinematics.wheel4.actual_speed.linear_vel = Kinematics.wheel4.actual_speed.rpm * RPM2VEL;
	//�������ٶ�ת��Ϊ��������������ٶ�
	Kinematics.actual_velocities.angular_z = ( Kinematics.wheel1.actual_speed.linear_vel - Kinematics.wheel2.actual_speed.linear_vel\
				- Kinematics.wheel3.actual_speed.linear_vel + Kinematics.wheel4.actual_speed.linear_vel)/(4.0f*(half_width + half_length));
	Kinematics.actual_velocities.linear_x  = (-Kinematics.wheel1.actual_speed.linear_vel + Kinematics.wheel2.actual_speed.linear_vel\
				- Kinematics.wheel3.actual_speed.linear_vel + Kinematics.wheel4.actual_speed.linear_vel)/(4.0f);
	Kinematics.actual_velocities.linear_y  = ( Kinematics.wheel1.actual_speed.linear_vel + Kinematics.wheel2.actual_speed.linear_vel\
				+ Kinematics.wheel3.actual_speed.linear_vel + Kinematics.wheel4.actual_speed.linear_vel)/(4.0f);
}



// ����: speed_control()
// ����: ��pid�ٶ����ת��Ϊ����ٶȣ����մ��ݸ��ٶ�pid
// ����������������ٶ�
// �����4������ٶ�
// ע�����1��4��Ĭ����ת����ͳ���ʵ���������෴����Ҫȡ��
int find_max(void);
int stop_flag_1=0;

void speed_control(float speed_x, float speed_y, float speed_r)
{
	int max;
	if(stop_flag_1 == 0 && speed_x == 0 && speed_y == 0 && speed_r == 0)
	{
		stop_flag_1 = 1;			//ֹͣ   �˱�־Ϊ�˱����ν���
		stop_chassis_motor();			//ͣ����  ���Ƕȱջ�
	}
	else if(speed_x != 0 || speed_y != 0 || speed_r != 0)
	{
		stop_flag_1 = 0;
		//�ٶȻ���
		BaseVel_To_WheelVel(speed_x, speed_y, speed_r);
//		motor1.target_speed=-10.0f*(speed_y - speed_x + speed_r*30);
//		motor2.target_speed=10.0f*(speed_y + speed_x - speed_r*30);
//		motor3.target_speed=10.0f*(speed_y - speed_x - speed_r*30);
//		motor4.target_speed=-10.0f*(speed_y + speed_x + speed_r*30);
		//�ٶȵȱ���ѹ����������ֹ����ٶȾ����ٶ����޶����»��������Ե�����̬
		max=find_max();
		if(max>max_motor_speed)
		{
			motor1.target_speed=(int)(motor1.target_speed*max_motor_speed*1.0/max);
			motor2.target_speed=(int)(motor2.target_speed*max_motor_speed*1.0/max);
			motor3.target_speed=(int)(motor3.target_speed*max_motor_speed*1.0/max);
			motor4.target_speed=(int)(motor4.target_speed*max_motor_speed*1.0/max);
		}
			//�ı��ٶ�pidĿ���ٶ�
			set_chassis_motor_speed(motor1.target_speed, motor2.target_speed, motor3.target_speed, motor4.target_speed);
	}
}	

int stop_flag_2=0;

void trigger_control(float trigger_angular)
{
if(stop_flag_2 == 0 && trigger_angular==0)
	{
		stop_flag_2 = 1;			//ֹͣ   �˱�־Ϊ�˱����ν���
		stop_trigger_motor();			//ͣ����  ���Ƕȱջ�
	}
else if(trigger_angular!=0)
	{
		stop_flag_2 = 0;
		
		trigger_to_motor(trigger_angular);
		
		set_trigger_motor_speed(motor5.target_speed);//set_trigger_motor_speed(motor8.target_speed);
		
}
	}

	
// ����: find_max()
// ����: �ҵ�����õ��ĵ���ٶ����ֵ
// ��������
// �����������õĵ�����ֵ
// �ڲ��������û��������
int find_max()
{
  int temp=0;
  
  temp=abs(motor1.target_speed);
  if(abs(motor2.target_speed)>temp)
    temp=abs(motor2.target_speed);
  if(abs(motor3.target_speed)>temp)
    temp=abs(motor3.target_speed);
  if(abs(motor4.target_speed)>temp)
    temp=abs(motor4.target_speed);
  return temp;
}





