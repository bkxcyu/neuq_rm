#ifndef __DEBUG_USART_H
#define	__DEBUG_USART_H

#include "stm32f4xx.h"
#include <stdio.h>


//引脚定义
/*******************************************************/
#define DEBUG_USART                             USART2
#define DEBUG_USART_CLK                         RCC_APB1Periph_USART2
#define DEBUG_USART_PeriphClockCmd              RCC_APB1PeriphClockCmd
#define DEBUG_USART_BAUDRATE                    115200  //串口波特率

#define DEBUG_USART_RX_GPIO_PORT                GPIOD
#define DEBUG_USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOD
#define DEBUG_USART_RX_PIN                      GPIO_Pin_6
#define DEBUG_USART_RX_AF                       GPIO_AF_USART2
#define DEBUG_USART_RX_SOURCE                   GPIO_PinSource6

#define DEBUG_USART_TX_GPIO_PORT                GPIOD
#define DEBUG_USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOD
#define DEBUG_USART_TX_PIN                      GPIO_Pin_5
#define DEBUG_USART_TX_AF                       GPIO_AF_USART2
#define DEBUG_USART_TX_SOURCE                   GPIO_PinSource5

#define DEBUG_USART_IRQHandler                  USART2_IRQHandler
#define DEBUG_USART_IRQ                 				USART2_IRQn
/************************************************************/

void Debug_USART_Config(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);

void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);

#endif /* __USART1_H */
