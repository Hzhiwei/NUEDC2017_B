
#include <math.h>
#include "driver_mpu6050.h"
#include "sim_IIC.h"


#define MPU_ADDR 0x68

#define MPU_SELF_TESTX_REG		0X0D	//自检寄存器X
#define MPU_SELF_TESTY_REG		0X0E	//自检寄存器Y
#define MPU_SELF_TESTZ_REG		0X0F	//自检寄存器Z
#define MPU_SELF_TESTA_REG		0X10	//自检寄存器A
#define MPU_SAMPLE_RATE_REG		0X19	//采样频率分频器
#define MPU_CFG_REG				0X1A	//配置寄存器
#define MPU_GYRO_CFG_REG		0X1B	//陀螺仪配置寄存器
#define MPU_ACCEL_CFG_REG		0X1C	//加速度计配置寄存器
#define MPU_MOTION_DET_REG		0X1F	//运动检测阀值设置寄存器
#define MPU_FIFO_EN_REG			0X23	//FIFO使能寄存器
#define MPU_I2CMST_CTRL_REG		0X24	//IIC主机控制寄存器
#define MPU_I2CSLV0_ADDR_REG	0X25	//IIC从机0器件地址寄存器
#define MPU_I2CSLV0_REG			0X26	//IIC从机0数据地址寄存器
#define MPU_I2CSLV0_CTRL_REG	0X27	//IIC从机0控制寄存器
#define MPU_I2CSLV1_ADDR_REG	0X28	//IIC从机1器件地址寄存器
#define MPU_I2CSLV1_REG			0X29	//IIC从机1数据地址寄存器
#define MPU_I2CSLV1_CTRL_REG	0X2A	//IIC从机1控制寄存器
#define MPU_I2CSLV2_ADDR_REG	0X2B	//IIC从机2器件地址寄存器
#define MPU_I2CSLV2_REG			0X2C	//IIC从机2数据地址寄存器
#define MPU_I2CSLV2_CTRL_REG	0X2D	//IIC从机2控制寄存器
#define MPU_I2CSLV3_ADDR_REG	0X2E	//IIC从机3器件地址寄存器
#define MPU_I2CSLV3_REG			0X2F	//IIC从机3数据地址寄存器
#define MPU_I2CSLV3_CTRL_REG	0X30	//IIC从机3控制寄存器
#define MPU_I2CSLV4_ADDR_REG	0X31	//IIC从机4器件地址寄存器
#define MPU_I2CSLV4_REG			0X32	//IIC从机4数据地址寄存器
#define MPU_I2CSLV4_DO_REG		0X33	//IIC从机4写数据寄存器
#define MPU_I2CSLV4_CTRL_REG	0X34	//IIC从机4控制寄存器
#define MPU_I2CSLV4_DI_REG		0X35	//IIC从机4读数据寄存器

#define MPU_I2CMST_STA_REG		0X36	//IIC主机状态寄存器
#define MPU_INTBP_CFG_REG		0X37	//中断/旁路设置寄存器
#define MPU_INT_EN_REG			0X38	//中断使能寄存器
#define MPU_INT_STA_REG			0X3A	//中断状态寄存器

#define MPU_ACCEL_XOUTH_REG		0X3B	//加速度值,X轴高8位寄存器
#define MPU_ACCEL_XOUTL_REG		0X3C	//加速度值,X轴低8位寄存器
#define MPU_ACCEL_YOUTH_REG		0X3D	//加速度值,Y轴高8位寄存器
#define MPU_ACCEL_YOUTL_REG		0X3E	//加速度值,Y轴低8位寄存器
#define MPU_ACCEL_ZOUTH_REG		0X3F	//加速度值,Z轴高8位寄存器
#define MPU_ACCEL_ZOUTL_REG		0X40	//加速度值,Z轴低8位寄存器

#define MPU_TEMP_OUTH_REG		0X41	//温度值高八位寄存器
#define MPU_TEMP_OUTL_REG		0X42	//温度值低8位寄存器

#define MPU_GYRO_XOUTH_REG		0X43	//陀螺仪值,X轴高8位寄存器
#define MPU_GYRO_XOUTL_REG		0X44	//陀螺仪值,X轴低8位寄存器
#define MPU_GYRO_YOUTH_REG		0X45	//陀螺仪值,Y轴高8位寄存器
#define MPU_GYRO_YOUTL_REG		0X46	//陀螺仪值,Y轴低8位寄存器
#define MPU_GYRO_ZOUTH_REG		0X47	//陀螺仪值,Z轴高8位寄存器
#define MPU_GYRO_ZOUTL_REG		0X48	//陀螺仪值,Z轴低8位寄存器

#define MPU_I2CSLV0_DO_REG		0X63	//IIC从机0数据寄存器
#define MPU_I2CSLV1_DO_REG		0X64	//IIC从机1数据寄存器
#define MPU_I2CSLV2_DO_REG		0X65	//IIC从机2数据寄存器
#define MPU_I2CSLV3_DO_REG		0X66	//IIC从机3数据寄存器

#define MPU_I2CMST_DELAY_REG	0X67	//IIC主机延时管理寄存器
#define MPU_SIGPATH_RST_REG		0X68	//信号通道复位寄存器
#define MPU_MDETECT_CTRL_REG	0X69	//运动检测控制寄存器
#define MPU_USER_CTRL_REG		0X6A	//用户控制寄存器
#define MPU_PWR_MGMT1_REG		0X6B	//电源管理寄存器1
#define MPU_PWR_MGMT2_REG		0X6C	//电源管理寄存器2 
#define MPU_FIFO_CNTH_REG		0X72	//FIFO计数寄存器高八位
#define MPU_FIFO_CNTL_REG		0X73	//FIFO计数寄存器低八位
#define MPU_FIFO_RW_REG			0X74	//FIFO读写寄存器
#define MPU_DEVICE_ID_REG		0X75	//器件ID寄存器

#define ACCEL_ON        (0x01)
#define GYRO_ON         (0x02)


#define MPUIIC_SingleSend IIC_SingleSend
#define MPUIIC_SingleRead IIC_SingleRead
#define MPUIIC_SendBuffer IIC_SendBuffer
#define MPUIIC_ReadBuffer IIC_ReadBuffer


#if MOTION_METHOD == MOTION_DMP | MOTION_EMPL
unsigned char *mpl_key = (unsigned char*)"eMPL 5.1";		//使用empl库必须定义
#endif


static float IMUcoefficient[2][3] =  {{1, 1, 1},	//加速度系数
								{1, 1, 1}};				//角速度系数
static int16_t IMUoffset[2][3] =  {{0, 0, 0},		//加速度偏移
								{4, -24, 6}};			//角速度偏移


/**
  * @brief  获取加速度与角速度数据(g,°/s)
  * @param  x加速度存放地址
  * @param  y加速度存放地址
  * @param  z加速度存放地址
  * @param  x角速度存放地址
  * @param  y角速度存放地址
  * @param  z角速度存放地址
  * @retval 1获取成功		0获取失败
  */
uint8_t mpu6050_GetIMUMotion(Acce_Type *A, Gyro_Type *G)
{
	uint8_t buffer[14];
	
	if(MPUIIC_ReadBuffer(MPU_ADDR, MPU_ACCEL_XOUTH_REG, 14, buffer))
	{
		return 0;
	}
	
	A->ox = ((((int16_t)buffer[0]) << 8) | buffer[1]);
	A->oy = ((((int16_t)buffer[2]) << 8) | buffer[3]);
	A->oz = ((((int16_t)buffer[4]) << 8) | buffer[5]);
	G->ox = ((((int16_t)buffer[8]) << 8) | buffer[9]);
	G->oy = ((((int16_t)buffer[10]) << 8) | buffer[11]);
	G->oz = ((((int16_t)buffer[12]) << 8) | buffer[13]);
	
	A->cx = A->ox;
	A->cy = A->oy;
	A->cz = A->oz;
	G->cx = G->ox - IMUoffset[1][0];
	G->cy = G->oy - IMUoffset[1][1];
	G->cz = G->oz - IMUoffset[1][2];
	
	A->x = A->cx / 65536.0f * 8.0f;
	A->y = A->cy / 65536.0f * 8.0f;
	A->z = A->cz / 65536.0f * 8.0f;
	G->x = G->cx / 65536.0f * 4000.0f * 3.1416 / 180.0;
	G->y = G->cy / 65536.0f * 4000.0f * 3.1416 / 180.0;
	G->z = G->cz / 65536.0f * 4000.0f * 3.1416 / 180.0;
	
	return 1;
}


/**
  * @brief  获取加速度数据(g)
  * @param  x加速度存放地址
  * @param  y加速度存放地址
  * @param  z加速度存放地址
  * @retval 1获取成功		0获取失败
  */
uint8_t mpu6050_GetAcceleration(Acce_Type *A)
{
	uint8_t buffer[6];
	
	if(MPUIIC_ReadBuffer(MPU_ADDR, MPU_ACCEL_XOUTH_REG, 6, buffer))
	{
		return 0;
	}
	
	A->ox = ((((int16_t)buffer[0]) << 8) | buffer[1]);
	A->oy = ((((int16_t)buffer[2]) << 8) | buffer[3]);
	A->oz = ((((int16_t)buffer[4]) << 8) | buffer[5]);
	
	A->cx = A->ox;
	A->cy = A->oy;
	A->cz = A->oz;
	
	A->x = A->cx / 65535.0f * 8.0f;
	A->y = A->cy / 65535.0f * 8.0f;
	A->z = A->cz / 65535.0f * 8.0f;
	
	return 1;
}


/**
  * @brief  获取角速度数据(°/s)
  * @param  x角速度存放地址
  * @param  y角速度存放地址
  * @param  z角速度存放地址
  * @retval 1获取成功		0获取失败
  */
uint8_t mpu6050_GetGyroscope(Gyro_Type *G)
{
	uint8_t buffer[14];
	
	if(MPUIIC_ReadBuffer(MPU_ADDR, MPU_GYRO_XOUTH_REG, 6, buffer))
	{
		return 0;
	}
	
	G->ox = ((((int16_t)buffer[0]) << 8) | buffer[1]);
	G->oy = ((((int16_t)buffer[1]) << 8) | buffer[2]);
	G->oz = ((((int16_t)buffer[3]) << 8) | buffer[4]);
	
	G->cx = G->ox - IMUoffset[1][0];
	G->cy = G->oy - IMUoffset[1][1];
	G->cz = G->oz - IMUoffset[1][2];
	
	G->x = G->cx / 65535.0f * 4000.0f * 3.1416 / 180.0f;
	G->y = G->cy / 65535.0f * 4000.0f * 3.1416 / 180.0f;
	G->z = G->cz / 65535.0f * 4000.0f * 3.1416 / 180.0f;
	
	return 1;
}


/**
  * @brief  获取温度数据(℃)
  * @param  温度存放地址
  * @retval 1获取成功		0获取失败
  */
uint8_t mpu6050_GetTemperature(float *temp)
{
	uint8_t buffer[2];
	
	if(MPUIIC_ReadBuffer(MPU_ADDR, MPU_TEMP_OUTH_REG, 2, buffer))
	{
		return 0;
	}
	
	*temp = ((((int16_t) buffer[0]) << 8) | buffer[1] - 32768) / 340.0f + 36.53f;
	
	return 1;
}


/******************************************	以下为CUSTOM模式相关函数	**************************************************/
#if MOTION_METHOD == MOTION_CUSTOM

const float c_SingleTick = 0.001f;	//一个Tick实际的时间（s）
float c_MahongyP = 1.0f;			//Mahony参数
float c_MahongyI = 0.25f;			//Mahony参数


Quat_Type CurrentQuat = 			//当前姿态四元数
{
	.q0 = 1,
	.q1 = 0,
	.q2 = 0,
	.q3 = 0,
};


static float invSqrt(float number);						//开平方并求倒数

static const float PI = 3.1415926f;



/**
  * @brief  Mahony互补滤波
  * @param  姿态数据
  * @param  输出四元数
  * @retval void
  */
float Kp = (1.0f );
float Ki = (0.0f);
	float ax, ay, az, gx, gy, gz;
	float recipNorm;
	float vx, vy, vz;
	float ex = 0.0f, ey = 0.0f, ez = 0.0f;
	static float exInt = 0, eyInt = 0, ezInt = 0;
	float QTemp[4];
uint8_t mpu9250_MahonyFilter(Acce_Type *A, Gyro_Type *G, float dt)
{
	
//	ax = LPF2pApply_1(A->x);
//	ay = LPF2pApply_2(A->y);
//	az = LPF2pApply_3(A->z);
//	gx = LPF2pApply_4(G->x);
//	gy = LPF2pApply_5(G->y);
//	gz = LPF2pApply_6(G->z);
	
	ax = A->x;
	ay = A->y;
	az = A->z;
	
	recipNorm = invSqrt(ax * ax + ay * ay + az * az);
	ax *= recipNorm;
	ay *= recipNorm;
	az *= recipNorm;
	
	vx = CurrentQuat.q1 * CurrentQuat.q3 - CurrentQuat.q0 * CurrentQuat.q2;
	vy = CurrentQuat.q0 * CurrentQuat.q1 + CurrentQuat.q2 * CurrentQuat.q3;
	vz = CurrentQuat.q0 * CurrentQuat.q0 - CurrentQuat.q1 * CurrentQuat.q1 - CurrentQuat.q2 * CurrentQuat.q2 + CurrentQuat.q3 * CurrentQuat.q3;
	
	ex = ay * vz - az * vy;
	ey = az * vx - ax * vz;
	ez = ax * vy - ay * vx;

	exInt += Ki * ex;
	eyInt += Ki * ey;
	ezInt += Ki * ez;
	
	gx = G->x + Kp * ex + exInt;
	gy = G->y + Kp * ey + eyInt;
	gz = G->z + Kp * ez + ezInt;
	
	QTemp[0] = CurrentQuat.q0;
	QTemp[1] = CurrentQuat.q1;
	QTemp[2] = CurrentQuat.q2;
	QTemp[3] = CurrentQuat.q3;
	
	CurrentQuat.q0 += (-QTemp[1] * gx - QTemp[2] * gy - QTemp[3] * gz) * 0.5f * dt;
	CurrentQuat.q1 += (QTemp[0] * gx + QTemp[2] * gz - QTemp[3] * gy) * 0.5f * dt;
	CurrentQuat.q2 += (QTemp[0] * gy - QTemp[1] * gz + QTemp[3] * gx) * 0.5f * dt;
	CurrentQuat.q3 += (QTemp[0] * gz + QTemp[1] * gy - QTemp[2] * gx) * 0.5f * dt; 

	recipNorm = invSqrt(CurrentQuat.q0 * CurrentQuat.q0 + CurrentQuat.q1 * CurrentQuat.q1 + CurrentQuat.q2 * CurrentQuat.q2 + CurrentQuat.q3 * CurrentQuat.q3);
	CurrentQuat.q0 *= recipNorm;
	CurrentQuat.q1 *= recipNorm;
	CurrentQuat.q2 *= recipNorm;
	CurrentQuat.q3 *= recipNorm;
	
	return 1;
}


/**
  * @brief  获取四元数
  * @param  四元数存储地址
  * @retval void
  */
void mpu6050_GetQuaternion(Quat_Type *Q)
{
	Q->q0 = CurrentQuat.q0;
	Q->q1 = CurrentQuat.q1;
	Q->q2 = CurrentQuat.q2;
	Q->q3 = CurrentQuat.q3;
}


/**
  * @brief  四元数转欧拉角
  * @param  待处理四元数
  * @param  处理结果
  * @retval void
  */
void mpu6050_Quaternion2Euler(Quat_Type *Q, Euler_Type *E)
{
	float gx, gy, gz;
	
	gx = 2 * (Q->q1 * Q->q3 - Q->q0 * Q->q2);
	gy = 2 * (Q->q0 * Q->q1 - Q->q2 * Q->q3);
	gz = Q->q0 * Q->q0 - Q->q1 * Q->q1 - Q->q2 * Q->q2 + Q->q3 * Q->q3;
	
	E->Pitch = -atan(gx / sqrt(gy*gy + gz*gz)) * 180 / PI;
	E->Roll = atan(gy / sqrt(gx*gx + gz*gz)) * 180 / PI;
	E->Yaw = atan2(2 * Q->q1 * Q->q2 - 2 * Q->q0 * Q->q3, 2 * Q->q0 * Q->q0 + 2 * Q->q1 * Q->q1 - 1) * 180.0f / PI;
}


/**
  * @brief  开平方并求倒数
  * @param  待处理数
  * @retval 处理结果
  */
static float invSqrt(float number)
{
    volatile long i;
    volatile float x, y;
    volatile const float f = 1.5F;

    x = number * 0.5F;
    y = number;
    i = * (( long * ) &y);
    i = 0x5f375a86 - ( i >> 1 );
    y = * (( float * ) &i);
    y = y * ( f - ( x * y * y ) );
    return y;
}
	
/******************************************	以上为CUSTOM模式相关函数	**************************************************/
/******************************************	以下为DMP模式相关函数	**************************************************/
#elif MOTION_METHOD == MOTION_DMP
#define q30  1073741824.0f
uint8_t mpu6050_DMPEuler(Euler_Type *E)
{
    float q0 = 0, q1 = 0, q2 = 0, q3 = 0;
	unsigned long sensor_timestamp;
	short gyro[3], accel[3], sensors;
	unsigned char more;
	long quat[4]; 
    
	if(dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors,&more))
    {
        return 1;
    }
	if(sensors&INV_WXYZ_QUAT) 
	{
		q0 = quat[0] / q30;	//q30格式转换为浮点数
		q1 = quat[1] / q30;
		q2 = quat[2] / q30;
		q3 = quat[3] / q30; 
		//计算得到俯仰角/横滚角/航向角
        E->Pitch = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3;	
        E->Roll  = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3;	
        E->Yaw   = atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;	
	}
    else 
    {
        return 2;
	}
    return 0;
}
/******************************************	以上为DMP模式相关函数	**************************************************/
/******************************************	以下为EMPL模式相关函数	**************************************************/
#elif MOTION_METHOD == MOTION_EMPL

uint8_t mpu6050_eMPLEular(Euler_Type *E, inv_time_t T)
{
	long temp[3];
	Acce_Type A;
	Gyro_Type G;
	long temperature;
	long data[3];
	int8_t accuracy;
	int8_t result;
	
	result = mpu_get_accel_reg(&(A.ox), NULL);
	if(result)
	{
		return 1;
	}
	temp[0] = A.ox;
	temp[1] = A.oy;
	temp[2] = A.oz;
	result = inv_build_accel(temp, 0, ((unsigned long)T));
	if(result)
	{
		return 1;
	}
	
	result = mpu_get_gyro_reg(&(G.ox), NULL);
	if(result)
	{
		return 1;
	}
	result = inv_build_gyro(&(G.ox), ((unsigned long)T));
	if(result)
	{
		return 1;
	}
	
	result = mpu_get_temperature(&temperature, NULL);
	if(result)
	{
		return 1;
	}
	result = inv_build_temp(temperature, ((unsigned long)T));
	if(result)
	{
		return 1;
	}
	
	inv_execute_on_data();
	
	inv_get_sensor_type_euler(data, &accuracy, NULL);
	
	E->Roll = data[0] / 65536.0f;
	E->Pitch = data[1] / 65536.0f;
	E->Yaw = data[2] / 65536.0f;
	
	return 0;
}

/******************************************	以上为EMPL模式相关函数	**************************************************/
#endif





/**
  * @brief  检测mpu9250是否在线
  * @param  void
  * @retval 0 离线	1在线
  */
uint8_t mpu6050_check(void)
{
	uint8_t temp = 0;
	MPUIIC_SingleRead(MPU_ADDR, 0x75, &temp);
	
	if(temp == MPU_ADDR)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}





/******************************************************************/










/**
  * @brief  mpu9250初始化
  * @param  void
  * @retval 0初始化成功		1离线	2初始化失败
  */
uint8_t mpu6050_InitConfig(void)
{
/******************************************	以下为CUSTOM模式初始化	**************************************************/
#if MOTION_METHOD == MOTION_CUSTOM	
	uint8_t temp;
	uint16_t index;
	
	//检测mpu6050是否存在
	if(!mpu6050_check())
	{
		return 1;
	}

	//复位,唤醒，使能温度传感器
	MPUIIC_SingleSend(MPU_ADDR, MPU_PWR_MGMT1_REG, 0x00);
	while(1)
	{
		index = 1000;
		while(index--);
		if(MPUIIC_SingleRead(MPU_ADDR, MPU_PWR_MGMT1_REG, &temp))
		{
			return 2;
		}
		if(!(temp & 0x80))
		{
			break;
		}
	}
	
	//配置陀螺仪最大量程为±2000°/s
	MPUIIC_SingleSend(MPU_ADDR, MPU_GYRO_CFG_REG, 0x03 << 3);
	
	//配置陀螺仪最大量程为±4g
	MPUIIC_SingleSend(MPU_ADDR, MPU_ACCEL_CFG_REG, 0x01 << 3);
	
	//关闭所有中断
	MPUIIC_SingleSend(MPU_ADDR, MPU_INT_EN_REG, 0x00);
	
	//关闭所有中断
	MPUIIC_SingleSend(MPU_ADDR, MPU_INTBP_CFG_REG, 0x00);
	
	//设置采样时钟为陀螺仪X轴
	MPUIIC_SingleSend(MPU_ADDR, MPU_PWR_MGMT1_REG, 0x01);
	
	//设置采样频率分频器		8000 / (1 + 15) = 500Hz
	MPUIIC_SingleSend(MPU_ADDR, MPU_SAMPLE_RATE_REG, 15);
	
	//设置DLPF
	MPUIIC_SingleSend(MPU_ADDR, MPU_CFG_REG, 0x00);
	
	//滤波器配置
	LPF2pSetCutoffFreq_1(200,30);
	LPF2pSetCutoffFreq_2(200,30);
	LPF2pSetCutoffFreq_3(200,30);
	LPF2pSetCutoffFreq_4(200,30);
	LPF2pSetCutoffFreq_5(200,30);
	LPF2pSetCutoffFreq_6(200,30);
	
/******************************************	以上为CUSTOM模式初始化	**************************************************/
/******************************************	以下为DMP模式初始化	**************************************************/
#elif MOTION_METHOD == MOTION_DMP

	struct platform_data_s {
		signed char orientation[9];
	};
	
	
	struct rx_s {
		unsigned char header[3];
		unsigned char cmd;
	};
	struct hal_s {
		unsigned char lp_accel_mode;
		unsigned char sensors;
		unsigned char dmp_on;
		unsigned char wait_for_tap;
		volatile unsigned char new_gyro;
		unsigned char motion_int_mode;
		unsigned long no_dmp_hz;
		unsigned long next_pedo_ms;
		unsigned long next_temp_ms;
		unsigned long next_compass_ms;
		unsigned int report;
		unsigned short dmp_features;
		struct rx_s rx;
	};
	static struct hal_s hal = {0};
	
	
	inv_error_t result;
    unsigned char accel_fsr;
    unsigned short gyro_rate, gyro_fsr;
    struct int_param_s int_param;
	static struct platform_data_s gyro_pdata = {
		.orientation = { -1, 0, 0,
						 0, 1, 0,
						 0, 0, 1}
	};

	//检测mpu6050是否存在
	if(!mpu6050_check())
	{
		return 1;
	}
	
	result = mpu_init(&int_param);
	if(result)
	{
		return 1;
	}
	
    mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL);
    mpu_set_sample_rate(200);
    mpu_get_gyro_fsr(&gyro_fsr);
    mpu_get_accel_fsr(&accel_fsr);
    inv_set_gyro_sample_rate(1000000L / gyro_rate);
    inv_set_accel_sample_rate(1000000L / gyro_rate);
    dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_pdata.orientation));
	
	mpu_set_lpf(3);
	
	result = dmp_load_motion_driver_firmware();
	if(result)
	{
		return 1;
	}
	
    hal.dmp_features = DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP;
    dmp_enable_feature(hal.dmp_features);
    dmp_set_fifo_rate(200);
    mpu_set_dmp_state(1);
    hal.dmp_on = 1;
	
/******************************************	以上为DMP模式初始化	**************************************************/  
/******************************************	以下为EMPL模式初始化	**************************************************/
#elif MOTION_METHOD == MOTION_EMPL
	
	struct platform_data_s {
		signed char orientation[9];
	};
	
	
	inv_error_t result;
    unsigned char accel_fsr;
    unsigned short gyro_rate, gyro_fsr;
    struct int_param_s int_param;
	static struct platform_data_s gyro_pdata = {
		.orientation = { 1, 0, 0,
						 0, 1, 0,
						 0, 0, 1}
	};

	//检测mpu6050是否存在
	if(!mpu6050_check())
	{
		return 1;
	}
	
	result = mpu_init(&int_param);
	if(result)
	{
		return 1;
	}
	result = inv_init_mpl();
	if(result)
	{
		return 1;
	}
    inv_enable_quaternion();
    inv_enable_9x_sensor_fusion();
    inv_enable_fast_nomot();
    inv_enable_gyro_tc();
    inv_enable_eMPL_outputs();
	result = inv_start_mpl();
	if(result)
	{
		return 1;
	}
	
//	mpu_set_lpf(3);
	
    mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL);
    mpu_set_sample_rate(200);
    mpu_get_sample_rate(&gyro_rate);
    mpu_get_gyro_fsr(&gyro_fsr);
    mpu_get_accel_fsr(&accel_fsr);
    inv_set_gyro_sample_rate(1000000L / gyro_rate);
    inv_set_accel_sample_rate(1000000L / gyro_rate);
    inv_set_gyro_orientation_and_scale(
            inv_orientation_matrix_to_scalar(gyro_pdata.orientation),
            (long)gyro_fsr<<15);
    inv_set_accel_orientation_and_scale(
            inv_orientation_matrix_to_scalar(gyro_pdata.orientation),
            (long)accel_fsr<<15);
	
//     以上为EMPL模式初始化                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           MPL模式初始化	**************************************************/
#endif
	
	return 0;
}


