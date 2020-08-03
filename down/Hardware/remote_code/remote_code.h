#ifndef _REMOTE_CODE_H_
#define _REMOTE_CODE_H_
#include "sys.h"

//Control_Mode第1位   FS为0   DJi为1
#define FS_Remote_Control			0x0
#define DJi_Remote_Control		0x1

//Control_Mode第2位  auto为1   remote为0
#define auto_control					0x2
#define remote_control        0x1
#define ROS_control						0x4

//Control_Mode第1位遥控器选择，第二位模式选择
#define control_mode     (auto_control | DJi_Remote_Control)			//自动+大疆遥控器

extern u8 Control_Mode;

/*
富斯遥控器脉宽范围				     				 大疆遥控器参数范围
CH1：1197-2200-3198									 ch0:364-1024-1684
CH2：1197-2200-3198									 ch1:364-1024-1684
CH3：1197-2200-3198									 ch2:364-1024-1684
CH4：1197-2200-3198                  ch3:364-1024-1684
CH5：1197-2200-3198                  s1: 1-3-2
CH6：1197-2200-3198                  s2: 1-3-2
CH7：1197-2200-3198
CH8：1197-2200-3198

富斯CH5-CH8
按键：    1197-3198
SWA|SWD:  1197-3198
SWB|SWC:  1198-2198-3198
旋钮：    1198-2198-3198

*/
#if (control_mode == (auto_control | FS_Remote_Control))					//富斯遥控器

	#define x_CH_width            Pulse_Width.CH1         //x方向通道脉宽   右摇杆左右
	#define y_CH_width            Pulse_Width.CH2         //y方向通道脉宽   右摇杆上下
	#define r_CH_width            Pulse_Width.CH4         //r方向通道脉宽   左摇杆左右
	#define stop_CH_width         Pulse_Width.CH5					//急停脉宽				 SWB拨到最下
	#define remote_CH_width       Pulse_Width.CH5					//遥控模式脉宽    SWB拨到中间
	       	
	/*以下定义中的数值均通过watch中观察各通道值所得*/
	
  //各方向初始值
	#define x_initial_value       2200              
	#define y_initial_value       2200
	#define r_initial_value       2200
	
	//各方向最大最小值
	#define x_max_value           3198             
	#define x_min_value           1197
	#define y_max_value           3198
	#define y_min_value           1197
	#define r_max_value           3198
	#define r_min_value           1197
	//阈值上下限
	#define stop_max_value				4000		
	#define stop_min_value				3000
	#define remote_max_value      4000
	#define remote_min_value      2000		//remote范围应包含stop
	
#elif (control_mode == (auto_control | DJi_Remote_Control))				//大疆遥控器

  #define x_CH_width            rc.ch0         //x方向通道脉宽   右摇杆左右
	#define y_CH_width            rc.ch1         //y方向通道脉宽   右摇杆上下
	#define r_CH_width            rc.ch2         //r方向通道脉宽   左摇杆左右
	#define i_CH_width            rc.ch3         //云台俯仰通道脉宽 左摇杆上下
	#define dance_CH_width         rc.s1					 //跳舞脉宽				s1拨到最下
	#define chassis_CH_width       rc.s1  				 //遥控底盘    s1拨到中间   1 3  2      最上云台  中间底盘  最下陀螺
	#define gimbal_CH_width         rc.s1            //遥控云台    s1最上  1
	#define trigger_CH_width      rc.s2          //拨弹轮控制
	
	/*以下定义中的数值均通过watch中观察各通道值所得*/
	
  //各方向初始值
	#define x_initial_value       1024            
	#define y_initial_value       1024
	#define r_initial_value       1024
	#define i_initial_value       1024
	//各方向最大最小值
	#define x_max_value           1684             
	#define x_min_value           364
	#define y_max_value           1684
	#define y_min_value           364
	#define r_max_value           1684
	#define r_min_value           364
	#define i_max_value           1684
	#define i_min_value           364
	//阈值上下限
	#define stop_max_value				2.5
	#define stop_min_value				1.5
	#define remote_max_value      4
	#define remote_min_value     0.5		//remote范围应包含stop

#endif

void Remote_Control(void);
float x_max_speed_caculator(float x);
float y_max_speed_caculator(float y);
float z_max_speed_caculator(float z);


#endif
