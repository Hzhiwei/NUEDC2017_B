#include "task_TouchINT.h"
#include "OSinclude.h"
#include "driver_touch.h"
#include "driver_touch.h"
#include "UIPage.h"


extern xQueueHandle Touch_Handler;
extern uint16_t TouchX, TouchY;
extern Page_Type *Page;


/**
  * @brief  触摸中断任务
  * @param  unused
  * @retval void
  */
void task_TouchINT(void *param)
{
	while(1)
	{
		//等待串口信号量
		xSemaphoreTake(Touch_Handler, portMAX_DELAY);
		
		//屏蔽中断，ADC转换过程中IRQ脚会乱发数据
		EXTI->IMR &= 0x007FFFFD;
		
		//延时等待中断稳定
		vTaskDelay(50);
		
		Touch_GetPos(NULL, NULL);
		
		if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
		//按下
		{
			Page_OnPush(Page, TouchX, TouchY);
		}
		
		//重启中断
		EXTI->IMR |= 0x00000002;
	}
}





