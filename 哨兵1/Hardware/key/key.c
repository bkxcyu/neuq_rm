#include "key.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

// 函数: key_init()
// 描述: 按键GPIO初始化
// 参数: 无
void key_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;		//输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;		//下拉
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
}

// 函数: key_press()
// 描述: 判断按键是否被按下
// 参数: 无
// return： 1为按下，0为弹起
u8 key_press()
{
	static u8 key_state = 0,key_last_state = 0;
	u8 data_back = 0;
	
	key_state = PBin(2);		 //读当前按键状态
	if(key_state==1)
	{
		if(key_last_state == key_state)		//如果两次状态相同都是高电平，说明按键被按下
		{
			key_last_state = key_state;
			data_back = 1;
		}
		else
		{
			key_last_state = key_state;
			data_back = 0;
		}
	}
	else
		data_back = 0;
	
	return data_back;
		
}



