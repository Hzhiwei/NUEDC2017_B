#ifndef __DRIVER_TOUCH_H
#define __DRIVER_TOUCH_H


#include "stm32f4xx.h"


void Touch_InitConfig(void);
uint8_t Touch_ReadXY(uint16_t *X, uint16_t *Y);
void Touch_GetPos(uint16_t *X, uint16_t *Y);


#endif
