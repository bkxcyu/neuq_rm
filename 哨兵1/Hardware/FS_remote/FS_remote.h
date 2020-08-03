#ifndef _FS_REMOTE_H
#define _FS_REMOTE_H
#include "sys.h"

extern u32	TIM5CH1_CAPTURE_VAL;	//输入捕获值(TIM2/TIM5是32位)

//脉宽结构体
typedef struct{
	
	//各通道
	int CH1;
	int CH2;
	int CH3;
	int CH4;
	int CH5;
	int CH6;
	int CH7;
	int CH8;
	
}Pulse_Width_CH;

extern Pulse_Width_CH Pulse_Width;

void FS_Remote_Init(void);			//富斯遥控器初始化



#endif

