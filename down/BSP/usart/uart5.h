#ifndef _USART5_H
#define _USART5_H
#include "sys.h"
#include "judge.h"
#include "stm32f4xx.h"
#include <stdio.h>
#include <stm32f4xx_dma.h>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include "misc.h"

#define    JUDGE_BUFFER_LEN           200

extern uint8_t  Judge_Buffer[ JUDGE_BUFFER_LEN ];

void UART5_Init( void );
void UART5_DMA_Init( void );


void UART5_SendChar( uint8_t cData );



#endif




