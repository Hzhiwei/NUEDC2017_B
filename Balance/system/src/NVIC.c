
#include "NVIC.h"


/**
  * @brief  NVIC��ʼ��
  * @param  void
  * @retval void
  */
void NVIC_InitConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	//����3�����ж�
	NVIC_InitStructure.NVIC_IRQChannel 						=	USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	=	5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority			=	0;
	NVIC_InitStructure.NVIC_IRQChannelCmd					=	ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
    //USART1
	NVIC_InitStructure.NVIC_IRQChannel						=	USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd					=	ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	=	6;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority			=	0;
	NVIC_Init(&NVIC_InitStructure);
}


