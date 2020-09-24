/**
  ******************************************************************************
  * @file    Project/APP/kinematic.c 
  * @author  Joe 
  * @version V1.0.0
  * @date    2-09-2020
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

//float max_base_linear_speed=217.817f;		//����������ٶ�
//float max_base_rotational_speed=7.260570f;		//���������ٶ�

//���˶�ѧ��ʽ
//����Ҫ�õ��ĵ����ٶ�ת��Ϊ���ӵ����ٶ�
void BaseVel_To_WheelVel(float linear_x, float linear_y, float angular_z)
{

	
	Kinematics.wheel1.target_speed.linear_vel = linear_x - linear_y + angular_z*(half_width+half_length);
	Kinematics.wheel2.target_speed.linear_vel = linear_x + linear_y - angular_z*(half_width+half_length);
	Kinematics.wheel3.target_speed.linear_vel = linear_x + linear_y + angular_z*(half_width+half_length);
	Kinematics.wheel4.target_speed.linear_vel = linear_x -  linear_y - angular_z*(half_width+half_length);
	//���ٶ� cm/s  תת��  RPM 
	Kinematics.wheel1.target_speed.rpm = Kinematics.wheel1.target_speed.linear_vel * VEL2RPM;
	Kinematics.wheel2.target_speed.rpm = Kinematics.wheel2.target_speed.linear_vel * VEL2RPM;
	Kinematics.wheel3.target_speed.rpm = Kinematics.wheel3.target_speed.linear_vel * VEL2RPM;
	Kinematics.wheel4.target_speed.rpm = Kinematics.wheel4.target_speed.linear_vel * VEL2RPM;
	
	motor1.target_speed = - (int)(Kinematics.wheel1.target_speed.rpm * M3508_REDUCTION_RATIO);
	motor2.target_speed =   (int)(Kinematics.wheel2.target_speed.rpm * M3508_REDUCTION_RATIO);
	motor3.target_speed =  - (int)(Kinematics.wheel3.target_speed.rpm * M3508_REDUCTION_RATIO);
	motor4.target_speed =  (int)(Kinematics.wheel4.target_speed.rpm * M3508_REDUCTION_RATIO);
	
}

void trigger_to_motor(float trigger_angular)
{
     
	motor5.target_speed =(int)(trigger_angular*M2006_REDUCTION_RATIO);
	
}



//���˶�ѧ��ʽ
//ͨ����̥��ʵ��ת�ټ�����̼������ĵ������ٶ�
void Get_Base_Velocities(void)
{
	//���ݵ��ת�ٲ�������ת��
	Kinematics.wheel1.actual_speed.rpm = - motor1.actual_speed / M3508_REDUCTION_RATIO;
	Kinematics.wheel2.actual_speed.rpm =   motor2.actual_speed / M3508_REDUCTION_RATIO;
	Kinematics.wheel3.actual_speed.rpm =   motor3.actual_speed / M3508_REDUCTION_RATIO;
	Kinematics.wheel4.actual_speed.rpm = - motor4.actual_speed / M3508_REDUCTION_RATIO;
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
int stop_flag_4=0;

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
		
		set_trigger_motor_speed(motor5.target_speed);		
}
	}


int stop_flag_3=0;
	
void gimbal_control(float gimbal1_angle,float gimbal2_angle)    //
{
	//ת������
	//gimbal1_angle=gimbal1_angle*8191/360;
  //gimbal2_angle=gimbal2_angle*8191/360;
	
	 	if(gimbal1_angle == 0)
	{
		stop_gimbal_motor();			//ͣ����  ���Ƕȱջ�
	}
    else
    //gimbal1_angle = KalmanFilter(gimbal1_angle,1,200);
	  set_GIMBAL_angle(gimbal1_angle,gimbal2_angle);//(gimbal1_angle,gimbal2_angle);
}

void Gimbal_control(float gimbal1_speed)     //С����ģʽʹ��
  {
		gimbal1.target_speed= -5000*gimbal1_speed;
		set_gimbal1_motor_speed(gimbal1.target_speed);
		
   }


	
void break_jugement(void)
{
    if(motor1.actual_speed <=0.05)
		 stop_flag_3=1;
    
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

/*-------------------------------------------------------------------------------------------------------------*/
/*       
        Q:����������Q���󣬶�̬��Ӧ��죬�����ȶ��Ա仵
        R:����������R���󣬶�̬��Ӧ�����������ȶ��Ա��       
*/

float KalmanFilter(const float ResrcData,float ProcessNiose_Q,float MeasureNoise_R)
                                        
{
        float R = MeasureNoise_R;
        float Q = ProcessNiose_Q;

        static        float x_last = 0;

        float x_mid = x_last;
        float x_now;

        static        float p_last = 0;

        float p_mid ;
        float p_now;
        float kg;       

        x_mid=x_last; //x_last=x(k-1|k-1),x_mid=x(k|k-1)
        p_mid=p_last+Q; //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=����
        kg=p_mid/(p_mid+R); //kgΪkalman filter��RΪ����
        x_now=x_mid+kg*(ResrcData-x_mid);//���Ƴ�������ֵ
               
        p_now=(1-kg)*p_mid;//����ֵ��Ӧ��covariance       

        p_last = p_now; //����covarianceֵ
        x_last = x_now; //����ϵͳ״ֵ̬

        return x_now;               
}

/*-------------------------------------------------------------------------------------------------------------*/




