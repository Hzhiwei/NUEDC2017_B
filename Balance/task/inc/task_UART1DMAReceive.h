#ifndef __TASK_UART1DMARECEIVE_H
#define __TASK_UART1DMARECEIVE_H


#include "stm32f4xx.h"


typedef struct
{
	uint8_t mode;			//����ģʽ
	uint8_t fourNode[4];	//����6�ĸ��ڵ�
	uint8_t align;			//x+,x-,y+,y-����λ
	uint8_t NOP[5];			//5�������ֽڣ���DMA
}DownloadData_Type;


void task_UART1DMAReceive(void *param);


#endif
