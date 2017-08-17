#ifndef __TASK_UART1DMASENDDATA_H
#define __TASK_UART1DMASENDDATA_H


#include "stm32f4xx.h"


typedef struct
{
	uint8_t currentMode;	//当前模式
	uint8_t found;			//1有球	0无球
	int16_t Loc[2];			//位置
	int16_t Speed[2];		//速度
}UploadData_Type;


void task_UART1DMASendData(void *param);



#endif
