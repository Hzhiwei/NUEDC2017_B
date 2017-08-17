#ifndef __DRIVER_STEERING_H
#define __DRIVER_STEERING_H


#include "stm32f4xx.h"
#include "BSP_TIM.h"


#define XSTEERINGLIMIT_MAX		1900
#define XSTEERINGLIMIT_CENTER	1500
#define XSTEERINGLIMIT_MIN		1100

#define YSTEERINGLIMIT_MAX		1900
#define YSTEERINGLIMIT_CENTER	1500
#define YSTEERINGLIMIT_MIN		1100


void steering_InitConfig(void);
void steering_AngleControl(char S, float Angle);


#endif
