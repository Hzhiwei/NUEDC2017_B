#ifndef __DRIVER_BALLCONTROL_H
#define __DRIVER_BALLCONTROL_H


#include "stm32f4xx.h"


//void Ball_LocPID(float *T, float *A);
void Ball_ClearInt(void);
void Ball_SpeedPID(float *T,float *A, uint32_t tick);
void Ball_LocPID(float *T, float *S);


#endif
