
#include "Config.h"
#include "BSP_GPIO.h"


/**
  * @brief  GPIO ≥ı ºªØ
  * @param  void
  * @retval void
  */
void BSP_GPIO_InitConfig(void)
{
    GPIO_InitTypeDef	GPIO_InitStructure;
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	//USART1
	GPIO_InitStructure.GPIO_Pin		=	GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode	=	GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType	=	GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	=	GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_High_Speed;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	
	//USART3
	GPIO_InitStructure.GPIO_Pin		=	GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode	=	GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType	=	GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	=	GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_High_Speed;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
	
	
	//ON_BOARD_IMU_IIC
	GPIO_InitStructure.GPIO_Pin		=	GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode	=	GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType	=	GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd	=	GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_High_Speed;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	//EXT_IIC
	GPIO_InitStructure.GPIO_Pin		=	GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode	=	GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType	=	GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd	=	GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_High_Speed;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	//OLED_IIC
	GPIO_InitStructure.GPIO_Pin		=	GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode	=	GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType	=	GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd	=	GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_High_Speed;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	//TIM1
	GPIO_InitStructure.GPIO_Pin		=	GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode	=	GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType	=	GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	=	GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_High_Speed;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
	
	
	//TIM3
	GPIO_InitStructure.GPIO_Pin		=	GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode	=	GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType	=	GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	=	GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_High_Speed;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM3);
	
	
	//LED
	GPIO_InitStructure.GPIO_Pin		=	GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode	=	GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType	=	GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	=	GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_High_Speed;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//πÿ±’LED
	GPIO_ResetBits(GPIOC, GPIO_Pin_0);
	GPIO_ResetBits(GPIOC, GPIO_Pin_1);
	GPIO_ResetBits(GPIOC, GPIO_Pin_2);
	GPIO_ResetBits(GPIOC, GPIO_Pin_3);
	
	
	//KEY
	GPIO_InitStructure.GPIO_Pin		=	GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode	=	GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd	=	GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_High_Speed;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
