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


//������ٶȽṹ��
typedef struct
{
	//��ȡԭʼֵ
	int16_t ox;
	int16_t oy;
	int16_t oz;
	//���Խ���ֵ
	int16_t cx;
	int16_t cy;
	int16_t cz;
	//ʵ��ֵ
	float x;
	float y;
	float z;
	//�˲�ʵ��ֵ
	float fx;
	float fy;
	float fz;
}Acce_Type;


//������ٶȽṹ��
typedef struct
{
	//��ȡԭʼֵ
	int16_t ox;
	int16_t oy;
	int16_t oz;
	//���Խ���ֵ
	int16_t cx;
	int16_t cy;
	int16_t cz;
	//ʵ��ֵ
	float x;
	float y;
	float z;
	//�˲�ʵ��ֵ
	float fx;
	float fy;
	float fz;
}Gyro_Type;


//ŷ���ǽṹ��
typedef struct
{
	float Pitch;
	float Roll;
	float Yaw;
}Euler_Type;

//��Ԫ���ṹ��(4��1�еľ���)
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
