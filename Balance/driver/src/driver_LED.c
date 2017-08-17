
#include "driver_LED.h"


extern uint8_t FlashStatus;


/**
  * @brief  LED³õÊ¼»¯
  * @param  void
  * @retval void
  */
void LED_InitConfig(void)
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_0);
	GPIO_ResetBits(GPIOC, GPIO_Pin_1);
	GPIO_ResetBits(GPIOC, GPIO_Pin_2);
	GPIO_ResetBits(GPIOC, GPIO_Pin_3);
}


/**
  * @brief  LEDÁÁÃð¿ØÖÆ
  * @param  LED±àºÅ 0-3
  * @param  0 Ãð  else ÁÁ
  * @retval void
  */
void LED_Control(uint8_t Num, uint8_t Status)
{
	if(!Status)
	{
		switch(Num)
		{
			case 1 : GPIO_ResetBits(GPIOC, GPIO_Pin_0);	break;
			case 2 : GPIO_ResetBits(GPIOC, GPIO_Pin_1);	break;
			case 3 : GPIO_ResetBits(GPIOC, GPIO_Pin_2);	break;
			case 4 : GPIO_ResetBits(GPIOC, GPIO_Pin_3);	break;
		}
	}
	else
	{
		switch(Num)
		{
			case 1 : GPIO_SetBits(GPIOC, GPIO_Pin_0);	break;
			case 2 : GPIO_SetBits(GPIOC, GPIO_Pin_1);	break;
			case 3 : GPIO_SetBits(GPIOC, GPIO_Pin_2);	break;
			case 4 : GPIO_SetBits(GPIOC, GPIO_Pin_3);	break;
		}
	}
}


/**
  * @brief  LEDÁÁÃð¿ØÖÆ(RGBLED)
  * @param  LED×´Ì¬
  * @retval void
  */
void LED_ControlRGB(uint8_t Status)
{
	if(Status & 0x01)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_0);
	}
	else
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_0);
	}
	
	if(Status & 0x02)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_1);
	}
	
	if(Status & 0x04)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_2);
	}
	else
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);
	}
}


/**
  * @brief  LEDÉÁË¸×´Ì¬ÉèÖÃ
  * @param  LED×´Ì¬
  * @retval void
  */
void LED_SetFlash(uint8_t Status)
{
	FlashStatus = Status;
}
