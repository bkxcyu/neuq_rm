#include "DJi_remote.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_dma.h"
#include "misc.h"
#include "sys.h"

/* ----------------------- RC Channel Definition---------------------------- */
#define RC_CH_VALUE_MIN ((uint16_t)364 )
#define RC_CH_VALUE_OFFSET ((uint16_t)1024)
#define RC_CH_VALUE_MAX ((uint16_t)1684)
/* ----------------------- RC Switch Definition----------------------------- */
#define RC_SW_UP ((uint16_t)1)
#define RC_SW_MID ((uint16_t)3)
#define RC_SW_DOWN ((uint16_t)2)

#define RC_FRAME_LENGTH 								18
/* ----------------------- Data Struct ------------------------------------- */

DJi_RC rc;

/* ----------------------- Internal Data ----------------------------------- */
volatile unsigned char sbus_rx_buffer[2][RC_FRAME_LENGTH]; //double sbus rx buffer to save data

/* ----------------------- Function Implements ---------------------------- */
/******************************************************************************
* @fn RC_Init
*
* @brief configure stm32 usart1 port
* - USART Parameters
* - 100Kbps
* - 8-N-1
* - DMA Mode
*
* @return None.
*
* @note This code is fully tested on STM32F405RGT6 Platform, You can port it
* to the other platform. Using doube buffer to receive data prevent
losing data.
*/
void Dji_Remote_Init(void)
{
/* -------------- Enable Module Clock Source ----------------------------*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_DMA2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7, GPIO_AF_USART1);
/* -------------- Configure GPIO ---------------------------------------*/
	{
		GPIO_InitTypeDef gpio;
		USART_InitTypeDef usart1;
		gpio.GPIO_Pin = GPIO_Pin_7 ;
		gpio.GPIO_Mode = GPIO_Mode_AF;
		gpio.GPIO_OType = GPIO_OType_PP;
		gpio.GPIO_Speed = GPIO_Speed_100MHz;
		gpio.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOB, &gpio);
		USART_DeInit(USART1);
		usart1.USART_BaudRate = 100000;
		usart1.USART_WordLength = USART_WordLength_8b;
		usart1.USART_StopBits = USART_StopBits_1;
		usart1.USART_Parity = USART_Parity_Even;
		usart1.USART_Mode = USART_Mode_Rx;
		usart1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_Init(USART1,&usart1);
		USART_Cmd(USART1,ENABLE);
		USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
	}
/* -------------- Configure NVIC ---------------------------------------*/
	{
		NVIC_InitTypeDef nvic;
		nvic.NVIC_IRQChannel = USART1_IRQn;
		nvic.NVIC_IRQChannelPreemptionPriority = 1;
		nvic.NVIC_IRQChannelSubPriority = 0;
		nvic.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&nvic);
	}
/* -------------- Configure DMA -----------------------------------------*/
	{
		DMA_InitTypeDef dma;
		DMA_DeInit(DMA2_Stream5);
		dma.DMA_Channel = DMA_Channel_4;
		dma.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->DR);
		dma.DMA_Memory0BaseAddr = (uint32_t)&sbus_rx_buffer[0][0];
		dma.DMA_DIR = DMA_DIR_PeripheralToMemory;
		dma.DMA_BufferSize = RC_FRAME_LENGTH;
		dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
		dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		dma.DMA_Mode = DMA_Mode_Circular;
		dma.DMA_Priority = DMA_Priority_VeryHigh;
		dma.DMA_FIFOMode = DMA_FIFOMode_Disable;
		dma.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
		dma.DMA_MemoryBurst = DMA_MemoryBurst_Single;
		dma.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
		DMA_DoubleBufferModeConfig(DMA2_Stream5,(uint32_t)&sbus_rx_buffer[0][0],DMA_Memory_0); //first used memory configuration
		DMA_DoubleBufferModeCmd(DMA2_Stream5, ENABLE);
		DMA_Init(DMA2_Stream5,&dma);
		USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); //usart rx idle interrupt enabled
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //usart rx idle interrupt enabled
		DMA_Cmd(DMA2_Stream5,ENABLE);
		
	}
}
/******************************************************************************
* @fn RemoteDataProcess
*
 * @brief resolution rc protocol data.
* @pData a point to rc receive buffer.
* @return None.
* @note RC_CtrlData is a global variable.you can deal with it in other place.
*/
void RemoteDataProcess(vu8 *pData)
{
	if(pData == 0)
	{
		return;
	}
	rc.ch0 = ((int16_t)pData[0] | ((int16_t)pData[1] << 8)) & 0x07FF;
	rc.ch1 = (((int16_t)pData[1] >> 3) | ((int16_t)pData[2] << 5))& 0x07FF;
	rc.ch2 = (((int16_t)pData[2] >> 6) | ((int16_t)pData[3] << 2) |((int16_t)pData[4] << 10)) & 0x07FF;
	rc.ch3 = (((int16_t)pData[4] >> 1) | ((int16_t)pData[5]<<7)) &0x07FF;
	rc.s1 = ((pData[5] >> 4) & 0x000C) >> 2;
	rc.s2 = ((pData[5] >> 4) & 0x0003);
	
}
/******************************************************************************
* @fn USART1_IRQHandler
*
* @brief USART1 irq, we are care of ilde interrupt that means receiving the
one frame datas is finished.
*
* @return None.
*
* @note This code is fully tested on STM32F405RGT6 Platform, You can port
it
* to the other platform.
*/

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE); //usart rx idle interrupt enabled
	}
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
	 //clear the idle pending flag
		(void)USART1->SR;
		(void)USART1->DR;
		//Target is Memory0
		if(DMA_GetCurrentMemoryTarget(DMA2_Stream5) == 0)
		{
			DMA_Cmd(DMA2_Stream5, DISABLE);
			DMA2_Stream5->NDTR = (uint16_t)RC_FRAME_LENGTH; //relocate the dma memory pointer to the beginning position
			DMA2_Stream5->CR |= (uint32_t)(DMA_SxCR_CT); //enable the current selected memory is Memory 1
			DMA_Cmd(DMA2_Stream5, ENABLE);
			RemoteDataProcess(sbus_rx_buffer[1]);
			
		}
		//Target is Memory1
		else
		{
			DMA_Cmd(DMA2_Stream5, DISABLE);
			DMA2_Stream5->NDTR = (uint16_t)RC_FRAME_LENGTH; //relocate the dma memory pointer to the beginning position
			DMA2_Stream5->CR &= ~(uint32_t)(DMA_SxCR_CT); //enable the current selected memory is Memory 0
			DMA_Cmd(DMA2_Stream5, ENABLE);
			RemoteDataProcess(sbus_rx_buffer[0]);
			
		}
	}
}

