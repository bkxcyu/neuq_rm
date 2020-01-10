#ifndef _LED_H
#define _LED_H


#define LED0 PGout(1)
#define LED1 PGout(2)
#define LED2 PGout(3)
#define LED3 PGout(4)
#define LED4 PGout(5)
#define LED5 PGout(6)
#define LED6 PGout(7)
#define LED7 PGout(8)

#define LED_PORT 		GPIOG
#define LED_PIN 		GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8
#define LED_MODE    GPIO_Mode_OUT
#define LED_OTYPE   GPIO_OType_PP
#define LED_PuPd		GPIO_PuPd_UP
#define LED_SPEED		GPIO_Speed_100MHz

void led_init(void);			//LEDµ∆≥ı ºªØ

#endif
