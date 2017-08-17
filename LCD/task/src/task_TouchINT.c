#include "task_TouchINT.h"
#include "OSinclude.h"
#include "driver_touch.h"
#include "driver_touch.h"
#include "UIPage.h"


extern xQueueHandle Touch_Handler;
extern uint16_t TouchX, TouchY;
extern Page_Type *Page;


/**
  * @brief  �����ж�����
  * @param  unused
  * @retval void
  */
void task_TouchINT(void *param)
{
	while(1)
	{
		//�ȴ������ź���
		xSemaphoreTake(Touch_Handler, portMAX_DELAY);
		
		//�����жϣ�ADCת��������IRQ�Ż��ҷ�����
		EXTI->IMR &= 0x007FFFFD;
		
		//��ʱ�ȴ��ж��ȶ�
		vTaskDelay(50);
		
		Touch_GetPos(NULL, NULL);
		
		if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
		//����
		{
			Page_OnPush(Page, TouchX, TouchY);
		}
		
		//�����ж�
		EXTI->IMR |= 0x00000002;
	}
}





