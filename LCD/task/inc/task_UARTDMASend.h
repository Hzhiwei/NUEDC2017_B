#ifndef __TASK_UARTDMASEND_H
#define __TASK_UARTDMASEND_H


#include "stm32f4xx.h"


typedef struct
{
	uint8_t mode;			//����ģʽ
	uint8_t fourNode[4];	//����6�ĸ��ڵ�
	uint8_t align;			//x+,x-,y+,y-����λ
}UploadData_Type;


void task_UARTDMASend(void *param);


#endif
