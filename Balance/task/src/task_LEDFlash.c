#include "task_LEDFlash.h"
#include "driver_LED.h"
#include "OSinclude.h"


uint8_t FlashStatus = FLASH_NONE;		//LED闪烁方式


/**
  * @brief  LED闪烁任务
  * @param  unused
  * @retval void
  */
void task_LEDFlash(void *param)
{
	uint8_t lastStatus = 1;
	while(1)
	{
		if(lastStatus)
		{
			switch(FlashStatus & 0x7F)
			{
				case FLASH_NONE : LED_ControlRGB(0x00); break;
				case FLASH_INIT : LED_ControlRGB(0x07); break;
				case FLASH_WORKING : LED_ControlRGB(0x01); break;
				case FLASH_LOSTIMU : LED_ControlRGB(0x02); break;
				default : LED_ControlRGB(0x00);
			}
		}
		else
		{
			LED_ControlRGB(0x00);
		}
		
		if(FlashStatus & FLASH_UARTDATA)
		{
			LED_Control(4, 1);
		}
		else
		{
			LED_Control(4, 0);
		}
		
		lastStatus = !lastStatus;
		
		vTaskDelay(FLASH_TICK);
	}
}




