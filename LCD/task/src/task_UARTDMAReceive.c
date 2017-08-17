#include "task_UARTDMAReceive.h"
#include "UIPositioningPanel.h"
#include "OSinclude.h"
#include "UIPage.h"
#include "UIButton.h"
#include "UI.h"
#include <stdio.h>


//串口数据接受缓存
DownloadData_Type	UARTReceiveBuffer;

extern xQueueHandle UARTIDLE_Handler;

extern Page_Type *Page;
extern Control_Type *PageControl[20];


/**
  * @brief  DMA接受任务
  * @param  unused
  * @retval void
  */
void task_UARTDMAReceive(void *param)
{
	char temp[10];
	uint32_t startTick = 0;
	
	while(1)
	{
		//等待串口信号量
		xSemaphoreTake(UARTIDLE_Handler, portMAX_DELAY);
		
		if(UARTReceiveBuffer.found)
		{
			sprintf(temp, "%d", UARTReceiveBuffer.Loc[1]);
			Button_SetText(PageControl[1], temp);
			
			sprintf(temp, "%d", -UARTReceiveBuffer.Loc[0]);
			Button_SetText(PageControl[3], temp);
			
			((PositionPanelBody_Type *)(PageControl[14]->body))->targetX = UARTReceiveBuffer.Loc[1];
			((PositionPanelBody_Type *)(PageControl[14]->body))->targetY = -UARTReceiveBuffer.Loc[0];
		}
		else
		{
			Button_SetText(PageControl[1], "-");
			
			Button_SetText(PageControl[3], "-");
			
			((PositionPanelBody_Type *)(PageControl[14]->body))->targetX = 1000;
			((PositionPanelBody_Type *)(PageControl[14]->body))->targetY = 1000;
		}
		
		sprintf(temp, "%d", UARTReceiveBuffer.currentMode);
		Button_SetText(PageControl[15], temp);
		
		if(UARTReceiveBuffer.found)
		{
			sprintf(temp, "%d", (xTaskGetTickCount() - startTick) / 1000);
			Button_SetText(PageControl[18], temp);
		}
		else
		{
			startTick = xTaskGetTickCount();
			Button_SetText(PageControl[18], "0");
		}
	}
}




