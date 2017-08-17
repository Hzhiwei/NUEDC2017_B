
#include "task_SysinitConfig.h"

#include "BSP_GPIO.h"
#include "BSP_UART.h"
#include "BSP_TIM.h"
#include "BSP_EXIT.h"
#include "BSP_DMA.h"

#include "driver_LED.h"
#include "driver_mpu6050.h"
#include "driver_steering.h"

#include "NVIC.h"

#include "task_AngleControl.h"
#include "task_LEDFlash.h"
#include "task_UART3DMAReceive.h"
#include "task_BallControl.h"
#include "task_UART1DMASendData.h"
#include "task_UART1DMAReceive.h"
#include "task_HyperControl.h"


xQueueHandle UART3IDLE_Handler;
xQueueHandle UART1IDLE_Handler;
xQueueHandle BallControl_Handler;

/**
  * @brief  系统初始化任务
  * @param  unused
  * @retval void
  */
void task_SysInitConfig(void * Parameters)
{
	uint8_t counter = 0;
	
	vSemaphoreCreateBinary(UART3IDLE_Handler);
	vSemaphoreCreateBinary(BallControl_Handler);
	vSemaphoreCreateBinary(UART1IDLE_Handler);
	
	//初始化
	BSP_GPIO_InitConfig();
	BSP_TIM_InitConfig();
	BSP_UART_InitConfig();
	BSP_EXIT_InitConfig();
	BSP_DMA_InitConfig();
	
	steering_InitConfig();
	LED_InitConfig();
	
    xTaskCreate(task_LEDFlash,
                "Init",
                20,
                NULL, 
                2,
                NULL);
	
	LED_SetFlash(FLASH_INIT);
	
	while(1)
	{
		if(!mpu6050_InitConfig())
		{
			break;
		}
		if(counter >= 10)
		{
			LED_SetFlash(FLASH_LOSTIMU);
		}
		else
		{
			counter++;
		}
		vTaskDelay(300);
	}
	
    xTaskCreate(task_AngleControl,
                "Init",
                150,
                NULL, 
                3,
                NULL);
	
    xTaskCreate(task_UART3DMAReceive,
                "Init",
                200,
                NULL, 
                3,
                NULL);
	
    xTaskCreate(task_BallControl,
                "Init",
                150,
                NULL, 
                3,
                NULL);
	
    xTaskCreate(task_UART1DMASendData,
                "Init",
                100,
                NULL, 
                3,
                NULL);
	
    xTaskCreate(task_UART1DMAReceive,
                "Init",
                100,
                NULL, 
                3,
                NULL);
	
    xTaskCreate(task_HyperControl,
                "Init",
                100,
                NULL, 
                3,
                NULL);
				
	vTaskDelay(100);
	
	NVIC_InitConfig();
	
	LED_SetFlash(FLASH_WORKING);
	
    vTaskDelete(NULL);
}
