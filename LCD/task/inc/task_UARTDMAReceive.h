#ifndef __TASK_UARTDMARECEIVE_H
#define __TASK_UARTDMARECEIVE_H


#include "stm32f4xx.h"


typedef struct
{
	uint8_t currentMode;	//��ǰģʽ
	uint8_t found;
	int16_t Loc[2];			//λ��
	int16_t Speed[2];		//�ٶ�
	uint8_t NOP[5];			//5�������ֽڣ���DMA
}DownloadData_Type;


void task_UARTDMAReceive(void *param);


#endif
