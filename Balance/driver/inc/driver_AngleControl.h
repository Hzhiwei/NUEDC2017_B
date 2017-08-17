#ifndef __DRIVER_ANGLECONTROL_H
#define __DRIVER_ANGLECONTROL_H


#include "stm32f4xx.h"


void Angle_ControlInit(void);
void Angle_Control(float *R, float *T, int16_t *C);


#endif
