#include "task_UART1DMAReceive.h"
#include "OSinclude.h"
#include "BSP_DMA.h"


//�������ݽ��ܻ���
DownloadData_Type	UART1ReceiveBuffer;


extern xQueueHandle UART1IDLE_Handler;
extern float TargetLoction[2];


/**
  * @brief  DMA��������
  * @param  unused
  * @retval void
  */
void task_UART1DMAReceive(void *param)
{
	while(1)
	{
		//�ȴ������ź���
		xSemaphoreTake(UART1IDLE_Handler, portMAX_DELAY);
	}
}




