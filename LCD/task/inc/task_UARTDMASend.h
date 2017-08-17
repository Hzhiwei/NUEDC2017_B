#ifndef __TASK_UARTDMASEND_H
#define __TASK_UARTDMASEND_H


#include "stm32f4xx.h"


typedef struct
{
	uint8_t mode;			//控制模式
	uint8_t fourNode[4];	//任务6四个节点
	uint8_t align;			//x+,x-,y+,y-低四位
}UploadData_Type;


void task_UARTDMASend(void *param);


#endif
