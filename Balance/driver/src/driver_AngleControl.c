#include "driver_AngleControl.h"

#include "BSP_TIM.h"
#include "driver_steering.h"


typedef struct
{
	float error;
	float deathWide;
	float P;
	float I;
	float D;
	float Pout;
	float Iout;
	float Dout;
	float PIDout;
	float IMax;
	float PIDMax;
	float LastError;
	float LastPIDout;
}PIDType;

PIDType XPID = 
{
	.error = 0,
	.deathWide = 0,
	.P = 20,
	.I = 5,
	.D = 0,
	.Pout = 0,
	.Iout = 0,
	.Dout = 0,
	.PIDout = 0,
	.IMax = 20,
	.PIDMax = 80,
	.LastError = 0,
	.LastPIDout = 0,
};

PIDType YPID = 
{
	.error = 0,
	.deathWide = 0,
	.P = 20,
	.I = 5,
	.D = 0,
	.Pout = 0,
	.Iout = 0,
	.Dout = 0,
	.PIDout = 0,
	.IMax = 20,
	.PIDMax = 80,
	.LastError = 0,
	.LastPIDout = 0,
};



/**
  * @brief  角度控制函数初始化
  * @param  实际角度XY
  * @param  目标角度XY
  * @param  舵机控制XY
  * @retval void
  */
void Angle_ControlInit(void)
{
	
}	


float DebugAngle[2] = {0, 0};


/**
  * @brief  角度控制函数
  * @param  实际角度XY
  * @param  目标角度XY
  * @param  舵机控制XY
  * @retval void
  */
void Angle_Control(float *R, float *T, int16_t *C)
{
	XPID.error = T[0] - R[0];
	XPID.error = DebugAngle[0] - R[0];
	
	if((XPID.error < XPID.deathWide) && (XPID.error > -XPID.deathWide))
	{
		XPID.error = 0;
	}
	
	XPID.Pout = XPID.P * XPID.error;
	XPID.Iout += XPID.I * XPID.error;
	XPID.Dout = XPID.D * (XPID.error - XPID.LastError);
	
	XPID.Iout = XPID.Iout > XPID.IMax ? XPID.IMax : XPID.Iout;
	XPID.Iout = XPID.Iout < -XPID.IMax ? -XPID.IMax : XPID.Iout;
	
	XPID.PIDout = XPID.Pout + XPID.Iout + XPID.Dout;
	
	XPID.PIDout = XPID.PIDout > XPID.PIDMax ? XPID.PIDMax : XPID.PIDout;
	XPID.PIDout = XPID.PIDout < -XPID.PIDMax ? -XPID.PIDMax : XPID.PIDout;
	
	XPID.LastError = XPID.error;
	XPID.LastPIDout = XPID.PIDout;
	
	
	////////////////////
	
	YPID.error = T[1] - R[1];
	YPID.error = DebugAngle[1] - R[1];
	
	if((YPID.error < YPID.deathWide) && (YPID.error > -YPID.deathWide))
	{
		YPID.error = 0;
	}
	
	YPID.Pout = YPID.P * YPID.error;
	YPID.Iout += YPID.I * YPID.error;
	YPID.Dout = YPID.D * (YPID.error - YPID.LastError);
	
	YPID.Iout = YPID.Iout > YPID.IMax ? YPID.IMax : YPID.Iout;
	YPID.Iout = YPID.Iout < -YPID.IMax ? -YPID.IMax : YPID.Iout;
	
	YPID.PIDout = YPID.Pout + YPID.Iout + YPID.Dout;
	
	YPID.PIDout = YPID.PIDout > YPID.PIDMax ? YPID.PIDMax : YPID.PIDout;
	YPID.PIDout = YPID.PIDout < -YPID.PIDMax ? -YPID.PIDMax  : YPID.PIDout;
	
	YPID.LastError = YPID.error;
	YPID.LastPIDout = YPID.PIDout;
	
	
	/////////////////////////
	
	C[0] = -XPID.PIDout;
	C[1] = -YPID.PIDout;
}



