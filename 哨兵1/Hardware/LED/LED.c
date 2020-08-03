#include "stm32f4xx_gpio.h"
#include "LED.h"


// 函数: led_init()
// 描述: LED灯GPIO初始化
// 参数: 无
void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=LED_PIN;
	GPIO_InitStructure.GPIO_Mode=LED_MODE;
	GPIO_InitStructure.GPIO_OType=LED_OTYPE;

	GPIO_InitStructure.GPIO_PuPd=LED_PuPd;
	GPIO_InitStructure.GPIO_Speed=LED_SPEED;
	
	GPIO_Init(LED_PORT,&GPIO_InitStructure);
	GPIO_SetBits(LED_PORT,LED_PIN);
	
}	

