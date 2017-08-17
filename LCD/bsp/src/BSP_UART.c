
#include "BSP_UART.h"
#include <stdio.h>


/**
  * @brief  serial port initialization
  * @param  void 
  * @retval void
  */
void BSP_UART_InitConfig(void)
{
	USART_InitTypeDef	USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	//USART1
	USART_InitStructure.USART_BaudRate	=	115200;
	USART_InitStructure.USART_HardwareFlowControl	=	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode		=	USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity	=	USART_Parity_No;
	USART_InitStructure.USART_StopBits	=	USART_StopBits_1;
	USART_InitStructure.USART_WordLength=	USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);
	
	//USART3
	USART_InitStructure.USART_BaudRate	=	115200;
	USART_InitStructure.USART_HardwareFlowControl	=	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode		=	USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity	=	USART_Parity_No;
	USART_InitStructure.USART_StopBits	=	USART_StopBits_1;
	USART_InitStructure.USART_WordLength=	USART_WordLength_8b;
	USART_Init(USART3, &USART_InitStructure);
	
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
    
    USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);
    USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);
	
	USART_Cmd(USART3, ENABLE);
}


int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (unsigned char) ch);// USART1 可以换成 USART2 等
	while (!(USART1->SR & USART_FLAG_TXE));
	return (ch);
}

