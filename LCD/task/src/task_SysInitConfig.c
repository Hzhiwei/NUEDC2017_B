
#include "task_SysinitConfig.h"
#include "task_LCD5310Update.h"
#include "task_TouchINT.h"
#include "task_UARTDMAReceive.h"
#include "task_UARTDMASend.h"
#include "task_UARTDMASend.h"

#include "BSP_GPIO.h"
#include "BSP_UART.h"
#include "BSP_TIM.h"
#include "BSP_EXIT.h"
#include "BSP_FSMC.h"
#include "BSP_DMA.h"

#include "driver_LCD5310.h"
#include "driver_SRAM.h"
#include "driver_UI.h"
#include "driver_touch.h"

#include "NVIC.h"

#include "UIDrawRAM.h"


xQueueHandle Touch_Handler;
xQueueHandle UARTIDLE_Handler;



/**
  * @brief  系统初始化任务
  * @param  unused
  * @retval void
  */
void task_SysInitConfig(void * Parameters)
{
	
	vSemaphoreCreateBinary(Touch_Handler);
	vSemaphoreCreateBinary(UARTIDLE_Handler);
	
	//初始化
	BSP_GPIO_InitConfig();
	BSP_TIM_InitConfig();
	BSP_UART_InitConfig();
	BSP_EXIT_InitConfig();
	BSP_FSMC_InitConfig();
	BSP_DMA_InitConfig();
	
	vTaskDelay(200);
	LCD_InitConfig();
	SRAM_IntConfig();
	Touch_InitConfig();
	
	UI_InitConfig();
	UI_Refresh();
	
    xTaskCreate(LCD_Update,
                "Init",
                150,
                NULL, 
                3,
                NULL);
	
    xTaskCreate(task_TouchINT,
                "Init",
                100,
                NULL, 
                3,
                NULL);
	
    xTaskCreate(task_UARTDMAReceive,
                "Init",
                100,
                NULL, 
                3,
                NULL);
	
    xTaskCreate(task_UARTDMASend,
                "Init",
                50,
                NULL, 
                3,
                NULL);
				
	vTaskDelay(100);
	
	NVIC_InitConfig();
	
    DMA_Cmd(DMA1_Stream1, ENABLE);
	
    vTaskDelete(NULL);
}
