#ifndef __TASK_UARTDMARECEIVE_H
#define __TASK_UARTDMARECEIVE_H


#include "stm32f4xx.h"


typedef struct
{
	uint8_t currentMode;	//当前模式
	uint8_t found;
	int16_t Loc[2];			//位置
	int16_t Speed[2];		//速度
	uint8_t NOP[5];			//5个无用字节，补DMA
}DownloadData_Type;


void task_UARTDMAReceive(void *param);


#endif
