#include "FS_remote.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "misc.h"

//内部函数声明
void Record_Pulse_Width(void);

//脉宽结构体
Pulse_Width_CH Pulse_Width;

// 函数: Pulse_Width_Init()
// 描述: 脉宽参数初始化
// 参数：无
// 输出：无
// 内部函数 用户无需调用
void Pulse_Width_Init()
{
	Pulse_Width.CH1 = 0;
	Pulse_Width.CH2 = 0;
	Pulse_Width.CH3 = 0;
	Pulse_Width.CH4 = 0;
	Pulse_Width.CH5 = 0;
	Pulse_Width.CH6 = 0;
	Pulse_Width.CH7 = 0;
	Pulse_Width.CH8 = 0;
}


// 函数: FS_Remote_Init()
// 描述: 富斯遥控器初始化，配置定时器5输入捕获
// 参数：无
// 输出：无
void FS_Remote_Init()
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM5_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTA时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //GPIOA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //下拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA0

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //PA0复用位定时器5
  
	  
	TIM_TimeBaseStructure.TIM_Prescaler=45-1;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=0XFFFFFFFF;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
	

	//初始化TIM5输入捕获参数
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
  TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  TIM_ICInit(TIM5, &TIM5_ICInitStructure);
		
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	
  TIM_Cmd(TIM5,ENABLE ); 	//使能定时器5

 
  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
	
	Pulse_Width_Init();
}


int debug_int=0;

//捕获状态 TIM5CH1_CAPTURE_STA
//[7]:0,没有成功的捕获;1,成功捕获到一次.
//[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u32	TIM5CH1_CAPTURE_VAL;	//输入捕获值(TIM2/TIM5是32位)
u8 CH=0;
//定时器5中断服务程序	 
void TIM5_IRQHandler(void)
{
	debug_int=1;
	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{
		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//溢出
		{	     
			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获了一次
					TIM5CH1_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
		if(TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到下降沿 		
			{	  			
				TIM5CH1_CAPTURE_STA &= 0X80;		//标记成功捕获到一次高电平脉宽
			  TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);//获取当前的捕获值.
	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
				CH++;
				if(TIM5CH1_CAPTURE_VAL>10000)		//如果捕获到很大的值，则是无用脉宽，CH清零不记录脉宽
					CH=0;
				Record_Pulse_Width();		//记录脉宽
			}
			else  								//若捕获上升沿
			{
				TIM5CH1_CAPTURE_STA=0;				//清空
				TIM5CH1_CAPTURE_VAL=0;
				TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
				TIM_Cmd(TIM5,DISABLE ); 			//关闭定时器5
	 			TIM_SetCounter(TIM5,0);				//计数器清零
	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
				TIM_Cmd(TIM5,ENABLE ); 				//使能定时器5
			}		    
		}			     	    					   
 	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
}

// 函数: Record_Pulse_Width()
// 描述: 根据CH值记录脉宽
// 参数：无
// 输出：无
// 内部函数 用户无需调用
void Record_Pulse_Width()
{
	switch(CH)
	{
		case 1:Pulse_Width.CH1 = TIM5CH1_CAPTURE_VAL;break;
		case 2:Pulse_Width.CH2 = TIM5CH1_CAPTURE_VAL;break;
		case 3:Pulse_Width.CH3 = TIM5CH1_CAPTURE_VAL;break;
		case 4:Pulse_Width.CH4 = TIM5CH1_CAPTURE_VAL;break;
		case 5:Pulse_Width.CH5 = TIM5CH1_CAPTURE_VAL;break;
		case 6:Pulse_Width.CH6 = TIM5CH1_CAPTURE_VAL;break;
		case 7:Pulse_Width.CH7 = TIM5CH1_CAPTURE_VAL;break;
		case 8:Pulse_Width.CH8 = TIM5CH1_CAPTURE_VAL;break;
	}
}






