/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "main.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}


/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
#include "stm32f4xx.h"
#include "OSinclude.h"
#include "task_UARTDMAReceive.h"


extern uint8_t BackLightLevel;
extern xQueueHandle Touch_Handler;
extern xQueueHandle UARTIDLE_Handler;


//±³¹â°´¼üÖÐ¶Ï
void EXTI9_5_IRQHandler(void)
{
	TickType_t currentTick;
	static TickType_t lastTick = 0;
		
	currentTick = xTaskGetTickCountFromISR();
	
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)
	{
		if((currentTick > lastTick + 200) && (BackLightLevel < 10))
		{
			BackLightLevel++;
		}
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
	
	if(EXTI_GetITStatus(EXTI_Line8) != RESET)
	{
		if((currentTick > lastTick + 200) && (BackLightLevel > 1))
		{
			BackLightLevel--;
		}
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
	
	TIM3->CCR1 = BackLightLevel * 100;
}


//´¥ÃþÖÐ¶Ï
void EXTI1_IRQHandler(void)
{
	xSemaphoreGiveFromISR(Touch_Handler, NULL);
	
	EXTI_ClearITPendingBit(EXTI_Line1);
}


uint8_t UARTtemp;

//´®¿Ú¿ÕÏÐÖÐ¶Ï
void USART3_IRQHandler(void)
{
    UARTtemp = USART3->DR;
    UARTtemp = USART3->SR;
	
	xSemaphoreGiveFromISR(UARTIDLE_Handler, NULL);
	
    DMA_Cmd(DMA1_Stream1, DISABLE);
    DMA_ClearFlag(DMA1_Stream1, DMA_FLAG_TCIF1 | DMA_FLAG_HTIF1);
    while(DMA_GetCmdStatus(DMA1_Stream1) != DISABLE);
    DMA_SetCurrDataCounter(DMA1_Stream1, sizeof(DownloadData_Type) + 5);
    DMA_Cmd(DMA1_Stream1, ENABLE);
	
	USART_ClearITPendingBit(USART3, USART_IT_IDLE);
}

