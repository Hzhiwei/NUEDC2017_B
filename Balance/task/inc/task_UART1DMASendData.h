#ifndef __TASK_UART1DMASENDDATA_H
#define __TASK_UART1DMASENDDATA_H


#include "stm32f4xx.h"


typedef struct
{
	uint8_t currentMode;	//��ǰģʽ
	uint8_t found;			//1����	0����
	int16_t Loc[2];			//λ��
	int16_t Speed[2];		//�ٶ�
}UploadData_Type;


void task_UART1DMASendData(void *param);



#endif
