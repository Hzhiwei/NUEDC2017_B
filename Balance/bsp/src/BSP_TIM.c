
#include "BSP_TIM.h"


void BSP_TIM_InitConfig(void)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  		TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	
	//TIM1
	TIM_TimeBaseStructure.TIM_Prescaler		=	167;
	TIM_TimeBaseStructure.TIM_CounterMode	=	TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period		=	999;
	TIM_TimeBaseStructure.TIM_ClockDivision	=	TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
		 
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;
 	TIM_OCInitStructure.TIM_OutputState	= TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity	= TIM_OCPolarity_High;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	TIM1->CCR1 = 500;
 
	TIM_ARRPreloadConfig(TIM1,ENABLE);
	
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
	TIM_Cmd(TIM1, ENABLE);
	
	//TIM3  200Hz
	TIM_TimeBaseStructure.TIM_Prescaler		=	83;
	TIM_TimeBaseStructure.TIM_CounterMode	=	TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period		=	4999;
	TIM_TimeBaseStructure.TIM_ClockDivision	=	TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		 
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;
 	TIM_OCInitStructure.TIM_OutputState	= TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity	= TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);

//	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
//	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
//	TIM3->CCR1 = 120;
//	TIM3->CCR2 = 120;
	TIM3->CCR3 = 1500;
	TIM3->CCR4 = 1500;
 
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	
	TIM_Cmd(TIM3, ENABLE);
}



