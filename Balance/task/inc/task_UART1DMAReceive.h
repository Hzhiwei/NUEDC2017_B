#ifndef __TASK_UART1DMARECEIVE_H
#define __TASK_UART1DMARECEIVE_H


#include "stm32f4xx.h"


typedef struct
{
	uint8_t mode;			//控制模式
	uint8_t fourNode[4];	//任务6四个节点
	uint8_t align;			//x+,x-,y+,y-低四位
	uint8_t NOP[5];			//5个无用字节，补DMA
}DownloadData_Type;


void task_UART1DMAReceive(void *param);


#endif
