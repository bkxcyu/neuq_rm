#ifndef _DJI_REMOTE_H
#define _DJI_REMOTE_H
#include "stdint.h"

typedef struct
{
	uint16_t ch0;
	uint16_t ch1;
	uint16_t ch2;
	uint16_t ch3;
	uint8_t s1;
	uint8_t s2;
}DJi_RC;

extern DJi_RC rc;


void Dji_Remote_Init(void);				//Ò£¿ØÆ÷³õÊ¼»¯

#endif
