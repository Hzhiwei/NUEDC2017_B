
#include "BSP_TIM.h"


void BSP_TIM_InitConfig(void)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  		TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	//TIM3
	TIM_TimeBaseStructure.TIM_Prescaler		=	83;
	TIM_TimeBaseStructure.TIM_CounterMode	=	TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period		=	999;
	TIM_TimeBaseStructure.TIM_ClockDivision	=	TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		 
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;
 	TIM_OCInitStructure.TIM_OutputState	= TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity	= TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM3->CCR1 = 500;
 
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	
	TIM_Cmd(TIM3, ENABLE);
}



