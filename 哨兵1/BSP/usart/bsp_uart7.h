#ifndef __UART7_H
#define	__UART7_H

#include "stm32f4xx.h"
#include <stdio.h>


//引脚定义
/*******************************************************/
#define JSON_USART                             UART7
#define JSON_USART_CLK                         RCC_APB1Periph_UART7
#define JSON_USART_PeriphClockCmd              RCC_APB1PeriphClockCmd
#define JSON_USART_BAUDRATE                    115200  //串口波特率

#define JSON_USART_RX_GPIO_PORT                GPIOE
#define JSON_USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOE
#define JSON_USART_RX_PIN                      GPIO_Pin_7
#define JSON_USART_RX_AF                       GPIO_AF_UART7
#define JSON_USART_RX_SOURCE                   GPIO_PinSource7

#define JSON_USART_TX_GPIO_PORT                GPIOE
#define JSON_USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOE
#define JSON_USART_TX_PIN                      GPIO_Pin_8
#define JSON_USART_TX_AF                       GPIO_AF_UART7
#define JSON_USART_TX_SOURCE                   GPIO_PinSource8

#define JSON_USART_IRQHandler                  UART7_IRQHandler
#define JSON_USART_IRQ                 				UART7_IRQn
/************************************************************/

void JSON_USART_Config(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);

void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);

#endif /* __USART1_H */
