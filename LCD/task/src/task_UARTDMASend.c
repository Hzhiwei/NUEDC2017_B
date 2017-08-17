#include "task_UARTDMASend.h"
#include "BSP_DMA.h"
#include "OSinclude.h"


#define UARTDATASENDPERIOD	50


UploadData_Type UARTSendBuffer =
{
	.mode = 0,
	.fourNode = {1, 2, 3, 4},
	.align = 0,
};	


/**
  * @brief  DMA周期性发送数据任务
  * @param  unused
  * @retval void
  */
void task_UARTDMASend(void *param)
{
	UARTSendBuffer.mode = 0;
	
	while(1)
	{
		UART3_DMASend((uint8_t *)(&UARTSendBuffer), sizeof(UploadData_Type));
		
		vTaskDelay(UARTDATASENDPERIOD);
	}
}








