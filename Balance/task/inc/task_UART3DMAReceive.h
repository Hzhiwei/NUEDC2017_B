#ifndef __TASK_UART3DMARECEIVE_H
#define __TASK_UART3DMARECEIVE_H


#include "stm32f4xx.h"


typedef struct
{
	int16_t found;		// 1 发现球    0 未发现球
	int16_t index[9][2];//标记
	int16_t ball[2];	//球位置
	uint8_t NOP[5];		//DMA空数据
}VisionReceive_Type;


void task_UART3DMAReceive(void *param);


#endif
