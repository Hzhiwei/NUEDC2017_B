#include "task_LCD5310Update.h"
#include "OSinclude.h"
#include "UIPage.h"
#include "driver_UI.h"


#define LCDUPDATEPERIOD		50


extern Page_Type *Page;


/**
  * @brief  LCD更新任务
  * @param  unused
  * @retval void
  */
void LCD_Update(void *param)
{
	TickType_t lastTick, currentTick;
	
	PointI_Type pos, size;
	Control_Type *x;
	pos.x = 100;
	pos.y = 100;
	size.x = 100;
	size.y = 50;
	
	while(1)
	{
		
		Page_FreshBuffer(Page);
		UI_Refresh();
		
		currentTick = xTaskGetTickCount();
		
		vTaskDelay(50);
	}
}







