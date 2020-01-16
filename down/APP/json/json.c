#include <string.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include <jansson.h>
#include "json.h" 
#include "motor.h"
#include "kinematic.h"
#include "mode.h"
#include "bsp_debug_usart.h"
#include "remote_code.h"
#include "gimbal.h"
#include "delay.h"
  extern char receiveBuffer[MAX_LENGTH];
  enum chassis_mode_t chassis_modes;
  enum gimbal_mode_t gimbal_modes;
  enum fric_mode_t fric_modes;

float pwm_pulse1=1500;
float pwm_pulse2=1500;
void send_cgf_info_by_json(void)
{
	/*Kinematics.actual_velocities.linear_x=1;
	Kinematics.actual_velocities.linear_y=2;
	Kinematics.actual_angular.gimbal_angular.yaw_angular=4;
	Kinematics.actual_velocities.angular_z=3;
	Kinematics.actual_angular.gimbal_angular.pitch_angular=5;
	Kinematics.actual_angular.fric_angular=6;*/
	
	json_t *root;
	char *out;           
	root = json_pack("[{sfsfsfsfsfsfsfsfsfsf}[ffffffffff]]",\
						"linear_x", (Kinematics.actual_velocities.linear_x),\
						"linear_y", (Kinematics.actual_velocities.linear_y),\
					  "yaw_angular", (Kinematics.actual_angular.gimbal_angular.yaw_angular),\
	          "angular_z", (Kinematics.actual_velocities.angular_z),\
						"pitch_angular", (Kinematics.actual_angular.gimbal_angular.pitch_angular),\
	          "fric_angular", (Kinematics.actual_angular.fric_angular),\
	          "ceshi1", (Kinematics.actual_angular.fric_angular),\
	          "ceshi2", (Kinematics.actual_angular.fric_angular),\
	          "ceshi3", (Kinematics.actual_angular.fric_angular),\
	          "ceshi4", (Kinematics.actual_angular.fric_angular),\
					  (Kinematics.actual_velocities.linear_x),\
						(Kinematics.actual_velocities.linear_y),\
	          (Kinematics.actual_velocities.angular_z),\
						(Kinematics.actual_angular.gimbal_angular.yaw_angular),\
            (Kinematics.actual_angular.gimbal_angular.pitch_angular),\
	          (Kinematics.actual_angular.fric_angular),\
          	(Kinematics.actual_angular.fric_angular),\
          	(Kinematics.actual_angular.fric_angular),\
          	(Kinematics.actual_angular.fric_angular),\
          	(Kinematics.actual_angular.fric_angular));
	
	out = json_dumps(root, JSON_ENCODE_ANY);//  变为字符串
	printf("%s\r\n", out);
	json_decref(root);
	//free(root);
	free(out);
}

//发送底盘实际速度信息

void send_chassis_info_by_json(void)
{
	Kinematics.actual_velocities.linear_x=1;
	Kinematics.actual_velocities.linear_y=2;
	Kinematics.actual_velocities.angular_z=3;
	json_t *root;
	char *out;           //
	root = json_pack("[{sfsfsf}[fff]]",\
						"linear_x", (Kinematics.actual_velocities.linear_x),\
						"linear_y", (Kinematics.actual_velocities.linear_y),\
						"angular_z", (Kinematics.actual_velocities.angular_z),\
						(Kinematics.actual_velocities.linear_x),\
						(Kinematics.actual_velocities.linear_y),\
						(Kinematics.actual_velocities.angular_z));   //(int),
						
	out = json_dumps(root, JSON_ENCODE_ANY);//  变为字符串
	printf("%s\r\n", out);
	json_decref(root);//减小引用计数 导致资源回收
	//free(root);
	free(out);
}

void send_gimbal_info_by_json(void)   ///新增发送云台信息 待完善*********************************
{
//测试
	//Kinematics.target_angular.gimbal_angular.yaw_angular=5;
	//Kinematics.target_angular.gimbal_angular.yaw_angular=10;
  json_t *root;
	char *out;           //
	root = json_pack("[{sfsf}[ff]]",\
						
					  "yaw_angular", (Kinematics.actual_angular.gimbal_angular.yaw_angular),\
						"pitch_angular", (Kinematics.actual_angular.gimbal_angular.pitch_angular),\
						(Kinematics.actual_angular.gimbal_angular.yaw_angular),\
						(Kinematics.actual_angular.gimbal_angular.pitch_angular));   //(int),
						
	out = json_dumps(root, JSON_ENCODE_ANY);
	printf("%s\r\n", out);
	json_decref(root);
	//free(root);
	free(out);

}
void send_fric_info_by_json()     //发送摩擦轮信息
{
//测试   
Kinematics.actual_angular.fric_angular=7;
json_t *root;
	char *out;           //
	root = json_pack("[{sf}[f]]",\
						
					  "fric_angular", (Kinematics.actual_angular.fric_angular),\
						
						(Kinematics.actual_angular.fric_angular));   //(int),
						
	out = json_dumps(root, JSON_ENCODE_ANY);
	printf("%s\r\n", out);
	json_decref(root);
	//free(root);
	free(out);
}



	float tmp_getx;
	float tmp_gety;

  float pitch_angle;
	float yaw_angle;
//json数据缓冲区
char json_Buffer[MAX_LENGTH];
extern char receiveBuffer[MAX_LENGTH];
//标志位，标志已经收到一个控制指令，在定时器中断中调用下列解析函数
uint8_t flag_command_recieved = 0;
uint8_t flag_command_recieved1 = 0;
uint8_t flag_command_recieved2 = 0;
uint8_t flag_command_recieved3 = 0;
uint8_t flag_command_recieved4 = 0;
uint8_t flag_command_recieved5 = 0;

//解析接收到的底盘速度控制指令
void resolve_json_chassis_command(void)
{
	json_t *root;
	json_t *chassis_obj;
	json_t *item_obj;
	json_error_t error;
	root = json_loads(json_Buffer,0,&error); //解码Json字符串 返回它包含的数组or  object
	chassis_obj = json_object_get( root, "chassis" );  //Get a value corresponding to key from object
	item_obj = json_array_get( chassis_obj, 0 );//Returns the element in array at position index
	Kinematics.target_velocities.linear_x =5.0f*json_integer_value(item_obj);	//real
	item_obj = json_array_get( chassis_obj, 1 );
	Kinematics.target_velocities.linear_y = 5.0f*json_integer_value(item_obj);
	item_obj = json_array_get( chassis_obj, 2 );
	Kinematics.target_velocities.angular_z = 0.8f*json_integer_value(item_obj);//100;///100;
	json_decref(item_obj); //Decrement the reference count of json. As soon as a call to json_decref() drops the reference count to zero, the value is destroyed and it can no longer be used.
	json_decref(chassis_obj);
	json_decref(root);
}
//解析收到的云台控制指令
void resolve_json_gimbal_command()
{ 
	json_t *root;
	json_t *gimbal_obj;
	json_t *item_obj;
	json_error_t error;
	root = json_loads(json_Buffer,0,&error);
	gimbal_obj = json_object_get( root, "gimbal" );
	item_obj = json_array_get( gimbal_obj, 0 );
	Kinematics.target_angular.gimbal_angular.yaw_angular=1.0f*json_integer_value(item_obj);
	item_obj = json_array_get( gimbal_obj, 1 );
	Kinematics.target_angular.gimbal_angular.pitch_angular=1.0f*json_integer_value(item_obj);
	json_decref(item_obj);
	json_decref(gimbal_obj);
	json_decref(root);

}



void resolve_json_handgimbal_command(void)
{ 
	json_t *root;
	json_t *gimbal_obj;
	json_t *item_obj;
	json_error_t error;
	root = json_loads(json_Buffer,0,&error);
	gimbal_obj = json_object_get( root, "hand_angle" );
	item_obj = json_array_get( gimbal_obj, 0 );
	Kinematics.target_angular.gimbal_angular.yaw_angular=1.0f*json_integer_value(item_obj);
	item_obj = json_array_get( gimbal_obj, 1 );
	Kinematics.target_angular.gimbal_angular.pitch_angular=1.0f*json_integer_value(item_obj);
	json_decref(item_obj);
	json_decref(gimbal_obj);
	json_decref(root);
}

//解析收到的摩擦轮控制指令
void resolve_json_fric_command()
	{ 
	json_t *root;
	json_t *fric_obj;
	json_t *item_obj;
	json_error_t error;
	root = json_loads(json_Buffer,0,&error);
	fric_obj = json_object_get( root, "fric_angular" );
	item_obj = json_array_get( fric_obj, 0 );
	Kinematics.target_angular.fric_angular=1.0f*json_integer_value(item_obj);
	json_decref(item_obj);
	json_decref(fric_obj);
	json_decref(root);

}
void resolve_json_trigger_command()
	{ 
	json_t *root;
	json_t *trigger_obj;
	json_t *item_obj;
	json_error_t error;
	root = json_loads(json_Buffer,0,&error);
	trigger_obj = json_object_get( root, "trigger_angular" );
	item_obj = json_array_get( trigger_obj, 0 );
	Kinematics.target_angular.trigger_angular=150;//1.0f*json_integer_value(item_obj);
	json_decref(item_obj);
	json_decref(trigger_obj);
	json_decref(root);

}
	
	//解析模式控制指令
void resolve_json_mode_command()
{
  resolve_chassis_mode_command();
	resolve_gimbal_mode_command();
	resolve_fric_mode_command();

}
void resolve_chassis_mode_command()
{ 
  json_t *root;
	json_t *chassis_mode_obj;
	json_t *item_obj;
	json_error_t error;
	root = json_loads(json_Buffer,0,&error);
	chassis_mode_obj = json_object_get( root, "translation" );
	item_obj = json_array_get( chassis_mode_obj, 0 );
	chassis_modes = (chassis_mode_t)(json_integer_value(item_obj));
	json_decref(item_obj);
	json_decref(chassis_mode_obj);
	json_decref(root);

}
void resolve_gimbal_mode_command()
{
  json_t *root;
	json_t *gimbal_mode_obj;
	json_t *item_obj;
	json_error_t error;
	root = json_loads(json_Buffer,0,&error);
	gimbal_mode_obj = json_object_get( root, "gimbal_mode" );
	item_obj = json_array_get( gimbal_mode_obj, 0 );
	gimbal_modes = (gimbal_mode_t)(json_integer_value(item_obj));
	json_decref(item_obj);
	json_decref(gimbal_mode_obj);
	json_decref(root);

}
void resolve_fric_mode_command()
{
  json_t *root;
	json_t *fric_mode_obj;
	json_t *item_obj;
	json_error_t error;
	root = json_loads(json_Buffer,0,&error);
	fric_mode_obj = json_object_get( root, "fric_mode" );
	item_obj = json_array_get( fric_mode_obj, 0 );
	fric_modes = (fric_mode_t)(json_integer_value(item_obj));
	json_decref(item_obj);
	json_decref(fric_mode_obj);
	json_decref(root);

}

void resolve_json(void)
{
	//创建json空对象
	json_t *Chassis_obj;
	json_t *item1_obj;
	json_error_t error;
	//将缓冲区的数据转换为json对象
	Chassis_obj = json_loads(json_Buffer,0,&error);
	
	if(!Chassis_obj)
	{
		//printf("load json failed\t\n");
	}
	else
	{
		
//		json_t *x, *y, *z;
		//json_object_get:提取父对象/数组中的对象/数组/键值
		//将主对象里的内容提取出来
//		x = json_object_get( Chassis_obj, "linear_x" );
//		y = json_object_get( Chassis_obj, "linear_y" );
//		z = json_object_get( Chassis_obj, "angular_z" );
//		
//		tmp_getx = json_real_value(x);
//		tmp_gety = json_real_value(y);
		
		
		item1_obj = json_object_get(Chassis_obj, "x");
		//Kinematics.target_velocities.linear_x = json_real_value(item1_obj);
		item1_obj = json_object_get(Chassis_obj, "y");
		Kinematics.target_velocities.linear_y = json_real_value(item1_obj);
		item1_obj = json_object_get(Chassis_obj, "z");
		//Kinematics.target_velocities.angular_z = json_real_value(item1_obj);
		
		
	}
	//json_array_get:提取父数组中的元素
	//json_array_get(Arry_obj,0);
	//
	//sprintf(json_Buffer, "item1_obj value is %f",json_real_value(item1_obj));
	
	json_delete(Chassis_obj);
	json_delete(item1_obj);
}





//****************************Jansson Test*******************************//
void jansson_pack_test(void)
{
	json_t *root;
	char *out;
	
	/* Build an empty JSON object */
	root = json_pack("{}");
	
	out = json_dumps(root, JSON_ENCODE_ANY);
	//printf("out:%s\r\n", out);
	json_delete(root);
	//free(root);
	free(out);
	
	/* Build the JSON object {"foo": 42, "bar": 7} */
	root = json_pack("{sisi}", "foo", 42, "bar", 7);
	
	out = json_dumps(root, JSON_ENCODE_ANY);
	printf("out:%s\r\n", out);
	json_delete(root);
	free(out);
	
	/* Like above, ':', ',' and whitespace are ignored */
	root = json_pack("{s:i, s:i}", "foo", 42, "bar", 7);
	
	out = json_dumps(root, JSON_ENCODE_ANY);
	printf("out:%s\r\n", out);
	json_delete(root);
	free(out);
	
	/* Build the JSON array [[1, 2], {"cool": true}] */
	root = json_pack("[[i,i],{s:b}]", 1, 2, "cool", 1);
	
	out = json_dumps(root, JSON_ENCODE_ANY);
	printf("out:%s\r\n", out);
	json_delete(root);
	free(out);
	
	/* Build a string from a non-null terminated buffer */
	char buffer[4] = {'t', 'e', 's', 't'};
	root = json_pack("[s#]", buffer, 4);

	out = json_dumps(root, JSON_ENCODE_ANY);
	printf("out:%s\r\n", out);
	json_delete(root);
	free(out);
	
	/* Concatenate strings together to build the JSON string "foobarbaz" */
	root = json_pack("[s++]", "foo", "bar", "baz");
	
	out = json_dumps(root, JSON_ENCODE_ANY);
	printf("out:%s\r\n", out);
	json_delete(root);
	free(out);
	
	
	
	
}





void caclulate_pwm_pulse()
{
	float unit_pwm_pulse= (840.0f/360.0f);
	
	Kinematics.target_angular.gimbal_angular.yaw_angular=180+Kinematics.target_angular.gimbal_angular.yaw_angular;
	Kinematics.target_angular.gimbal_angular.pitch_angular=180-Kinematics.target_angular.gimbal_angular.pitch_angular;
	if(Kinematics.target_angular.gimbal_angular.pitch_angular<225 && Kinematics.target_angular.gimbal_angular.pitch_angular>135)
	
	   pwm_pulse1 = (1080+unit_pwm_pulse * Kinematics.target_angular.gimbal_angular.pitch_angular)*1.0f;
	if(Kinematics.target_angular.gimbal_angular.yaw_angular<270 && Kinematics.target_angular.gimbal_angular.yaw_angular>90)
		
	   pwm_pulse2 = (1080+unit_pwm_pulse * Kinematics.target_angular.gimbal_angular.yaw_angular)*1.0f;
	
}
void caclulate_handpwm_pulse()
{
  static double  yaw_pwm_pulse=1500;
  static double  pitch_pwm_pulse=1500;

	if(Kinematics.target_angular.gimbal_angular.yaw_angular==1 && pwm_pulse2>=1395)
	{
    yaw_pwm_pulse=yaw_pwm_pulse-1;
		pwm_pulse2=yaw_pwm_pulse;
		delay_ms(2);
	}
	if(Kinematics.target_angular.gimbal_angular.yaw_angular==-1 && pwm_pulse2<=1605)
	{
		yaw_pwm_pulse++;
		pwm_pulse2=yaw_pwm_pulse;
		delay_ms(2);
		
	}
	if(Kinematics.target_angular.gimbal_angular.yaw_angular==0)
	{
		if(yaw_pwm_pulse>1500)
			 yaw_pwm_pulse=yaw_pwm_pulse-1;
		   pwm_pulse2=yaw_pwm_pulse;
		   delay_ms(2);
		if(yaw_pwm_pulse<1500)
		  yaw_pwm_pulse++;
		  pwm_pulse2=yaw_pwm_pulse;
		  delay_ms(2);
	}
	
	
	if(Kinematics.target_angular.gimbal_angular.pitch_angular==1 && pwm_pulse1<=1605)
	{
		pitch_pwm_pulse++;
		pwm_pulse1=pitch_pwm_pulse;
		delay_ms(2);
		
	}
	if(Kinematics.target_angular.gimbal_angular.pitch_angular==-1 && pwm_pulse1>=1395)
	{
		pitch_pwm_pulse=pitch_pwm_pulse-1;
		pwm_pulse1=pitch_pwm_pulse;
		delay_ms(2);
	}
	
		if(Kinematics.target_angular.gimbal_angular.pitch_angular==0)
	{
			if(pitch_pwm_pulse>1500)
			 pitch_pwm_pulse=pitch_pwm_pulse-1;
		   pwm_pulse1=pitch_pwm_pulse;
		   delay_ms(2);
		  if(pitch_pwm_pulse<1500)
		  pitch_pwm_pulse++;
		  pwm_pulse1=pitch_pwm_pulse;
		  delay_ms(2);
	}

}


//void convert_ascii2json_test(char * receive_buffer)
//{
// json_t *root;
// printf("receive_buffer:%s\r\n", receive_buffer);
// if(receive_buffer[0]=='{')
// {  
//    root=json_loads(receive_buffer,0,&j_error);//将字符串转换成json，都是ASCII
//  json_unpack(root, "{s:i, s:i}","cx", &data1,"cy", &data2);
//    //char * output_buffer = json_dumps(root,JSON_ENCODE_ANY);
//    //printf("output_buffer:%s\r\n", output_buffer);
//  printf("data:%d，%d\r\n",(int)data1,(int)data2);    
//  json_delete(root);//不要用free，用free（）会导致Heap溢出
//  //free(root);
// }
// else
// {
//  //Usart_SendString( USART2, "error");
// }
//}
