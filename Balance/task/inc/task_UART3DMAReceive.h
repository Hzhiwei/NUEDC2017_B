#ifndef __TASK_UART3DMARECEIVE_H
#define __TASK_UART3DMARECEIVE_H


#include "stm32f4xx.h"


typedef struct
{
	int16_t found;		// 1 ������    0 δ������
	int16_t index[9][2];//���
	int16_t ball[2];	//��λ��
	uint8_t NOP[5];		//DMA������
}VisionReceive_Type;


void task_UART3DMAReceive(void *param);


#endif
