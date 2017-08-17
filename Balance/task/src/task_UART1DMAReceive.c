#include "task_UART1DMAReceive.h"
#include "OSinclude.h"
#include "BSP_DMA.h"


//串口数据接受缓存
DownloadData_Type	UART1ReceiveBuffer;


extern xQueueHandle UART1IDLE_Handler;
extern float TargetLoction[2];


/**
  * @brief  DMA接受任务
  * @param  unused
  * @retval void
  */
void task_UART1DMAReceive(void *param)
{
	while(1)
	{
		//等待串口信号量
		xSemaphoreTake(UART1IDLE_Handler, portMAX_DELAY);
	}
}




