#ifndef _BSP_IMU_USART_H_
#define _BSP_IMU_USART_H_

#include "stm32f4xx.h"
#include <stdio.h>
#include "sys.h"

#define IMU_USART_IRQHandler USART6_IRQHandler 
/**@brief Fuction for initation of USART6 for imu to transmit data
*/
void bsp_imu_usart_init(void);
#endif //_BSP_IMU_USART_H_

