#ifndef __DRIVER_MPU9250_H
#define __DRIVER_MPU9250_H


#include "stm32f4xx.h"

#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "invensense.h"
#include "invensense_adv.h"
#include "eMPL_outputs.h"
#include "mltypes.h"
#include "mpu.h"


#define MOTION_CUSTOM	0
#define MOTION_DMP		1
#define MOTION_EMPL		2

#define MOTION_METHOD	MOTION_DMP


//三轴加速度结构体
typedef struct
{
	//读取原始值
	int16_t ox;
	int16_t oy;
	int16_t oz;
	//线性矫正值
	int16_t cx;
	int16_t cy;
	int16_t cz;
	//实际值
	float x;
	float y;
	float z;
	//滤波实际值
	float fx;
	float fy;
	float fz;
}Acce_Type;


//三轴角速度结构体
typedef struct
{
	//读取原始值
	int16_t ox;
	int16_t oy;
	int16_t oz;
	//线性矫正值
	int16_t cx;
	int16_t cy;
	int16_t cz;
	//实际值
	float x;
	float y;
	float z;
	//滤波实际值
	float fx;
	float fy;
	float fz;
}Gyro_Type;


//欧拉角结构体
typedef struct
{
	float Pitch;
	float Roll;
	float Yaw;
}Euler_Type;

//四元数结构体(4行1列的矩阵)
typedef struct
{
	float q0;
	float q1;
	float q2;
	float q3;
}Quat_Type;


uint8_t mpu6050_check(void);
uint8_t mpu6050_InitConfig(void);


uint8_t mpu6050_GetIMUMotion(Acce_Type *A, Gyro_Type *G);
uint8_t mpu6050_GetAcceleration(Acce_Type *A);
uint8_t mpu6050_GetGyroscope(Gyro_Type *G);
uint8_t mpu6050_GetTemperature(float *temp);
#if MOTION_METHOD == MOTION_CUSTOM
uint8_t mpu9250_MahonyFilter(Acce_Type *A, Gyro_Type *G, float dt);
void mpu6050_Quaternion2Euler(Quat_Type *Q, Euler_Type *E);
void mpu6050_GetQuaternion(Quat_Type *Q);
#elif MOTION_METHOD == MOTION_DMP
uint8_t mpu6050_DMPEuler(Euler_Type *E);
#elif MOTION_METHOD == MOTION_EMPL
uint8_t mpu6050_eMPLEular(Euler_Type *E, inv_time_t T);
#endif



#endif
