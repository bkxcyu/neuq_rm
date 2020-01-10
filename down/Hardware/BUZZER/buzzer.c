/*#include "buzzer.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "delay.h"


//TIM12 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM12_PWM_Init(u32 arr,u32 psc)
{		 					 
	//此部分需手动修改IO口设置
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);  	//TIM12时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE); 	//使能PORTH时钟	
	
	GPIO_PinAFConfig(GPIOH,GPIO_PinSource6,GPIO_AF_TIM12); //GPIOH6复用为定时器12
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           //GPIOH6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOH,&GPIO_InitStructure);              //初始化PH6
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM12,&TIM_TimeBaseStructure);//初始化定时器12
	
	//初始化TIM12 Channel PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	TIM_OC1Init(TIM12, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM12OC1

	TIM_OC1PreloadConfig(TIM12, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
 
  TIM_ARRPreloadConfig(TIM12,ENABLE);//ARPE使能 
	
	TIM_Cmd(TIM12, ENABLE);  //使能TIM12								  
}  


// 函数: nrf_no_exist()
// 描述: 用来检查nrf是否插在单片机上，如果没有，则蜂鸣器发出警报声
// 参数：是否使能
// 输出：无
void nrf_no_exist(int able)
{
	TIM_Cmd(TIM12, ENABLE); 
	if(able==1)
	{
		TIM_SetCompare1(TIM12,100);	//修改比较值，修改占空比，范围0--1000
		delay_ms(300);
		TIM_SetCompare1(TIM12,0);	//修改比较值，修改占空比，范围0--1000
		delay_ms(300);
	}
	else
		TIM_Cmd(TIM12, DISABLE); 
}

// 函数: nrf_no_connect()
// 描述: 用来检查单片机上的nrf是否与电脑端nrf通讯成功，若没有成功，则发出警报声
// 参数：是否使能
// 输出：无
void nrf_no_connect(int able)
{
	TIM_Cmd(TIM12, ENABLE); 
	if(able==1)
	{
		TIM_SetCompare1(TIM12,100);	//修改比较值，修改占空比，范围0--1000
		delay_ms(700);
		TIM_SetCompare1(TIM12,0);	//修改比较值，修改占空比，范围0--1000
		delay_ms(200);
	}
	else
		TIM_Cmd(TIM12, DISABLE); 
}
*/
