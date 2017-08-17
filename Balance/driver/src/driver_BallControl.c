#include "driver_BallControl.h"
#include "Config.h"

typedef struct
{
	float error;
	float deathWidth;
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

//PIDType LocXOPID = 
//{
//	.error = 0,
//	.deathWide = 0,
//	.P = 0.05,
//	.I = 0,
//	.D = 0,
//	.Pout = 0,
//	.Iout = 0,
//	.Dout = 0,
//	.PIDout = 0,
//	.IMax = 0,
//	.PIDMax = 15,
//	.LastError = 0,
//	.LastPIDout = 0,
//};

//PIDType LocXIPID = 
//{
//	.error = 0,
//	.deathWide = 0,
//	.P = 0.3,
//	.I = 0,
//	.D = 0,
//	.Pout = 0,
//	.Iout = 0,
//	.Dout = 0,
//	.PIDout = 0,
//	.IMax = 0,
//	.PIDMax = 15,
//	.LastError = 0,
//	.LastPIDout = 0,
//};

//PIDType LocYOPID = 
//{
//	.error = 0,
//	.deathWide = 0,
//	.P = 0.05,
//	.I = 0,
//	.D = 0,
//	.Pout = 0,
//	.Iout = 0,
//	.Dout = 0,
//	.PIDout = 0,
//	.IMax = 0,
//	.PIDMax = 15,
//	.LastError = 0,
//	.LastPIDout = 0,
//};

//PIDType LocYIPID = 
//{
//	.error = 0,
//	.deathWide = 0,
//	.P = 0.3,
//	.I = 0,
//	.D = 0,
//	.Pout = 0,
//	.Iout = 0,
//	.Dout = 0,
//	.PIDout = 0,
//	.IMax = 0,
//	.PIDMax = 15,
//	.LastError = 0,
//	.LastPIDout = 0,
//};


extern float BallSpeed[2];					//球的速度
extern float BallPostion[2][HisLength];		//历史缓存
extern int dataTick[HisLength];				//缓存对应时间
extern int HisPoint;						//缓存指针，指向最新缓存

float DebugSpeed[2] = {0, 0};

///**
//  * @brief  小球位置PID
//  * @param  目标目标位置
//  * @param  输出角度
//  * @retval void
//  */
//void Ball_LocPID(float *T, float *A)
//{
//	//X out
//	LocXOPID.error = T[0] - BallPostion[0][HisPoint];
//	
//	LocXOPID.Pout = LocXOPID.P * LocXOPID.error;
//	LocXOPID.Iout+= LocXOPID.I * LocXOPID.error * (dataTick[HisPoint] - dataTick[(HisPoint + HisLength + 1) % HisLength]) / 100;
//	LocXOPID.Dout =-LocXOPID.D *  BallSpeed[0] / (dataTick[HisPoint] - dataTick[(HisPoint + HisLength + 1) % HisLength]);
//	
//	LocXOPID.Iout = LocXOPID.Iout > LocXOPID.IMax ? LocXOPID.IMax : LocXOPID.Iout;
//	LocXOPID.Iout = LocXOPID.Iout <-LocXOPID.IMax ?-LocXOPID.IMax : LocXOPID.Iout;
//	
//	LocXOPID.PIDout = LocXOPID.Pout + LocXOPID.Iout + LocXOPID.Dout;
//	
//	LocXOPID.PIDout = LocXOPID.PIDout > LocXOPID.PIDMax ? LocXOPID.PIDMax : LocXOPID.PIDout;
//	LocXOPID.PIDout = LocXOPID.PIDout <-LocXOPID.PIDMax ?-LocXOPID.PIDMax : LocXOPID.PIDout;
//	
//	LocXOPID.LastError = LocXOPID.error;
//	
//	//X in 
//	LocXIPID.error = LocXOPID.PIDout - BallSpeed[0];
//	LocXIPID.error = DebugSpeed[0] - BallSpeed[0];
//	
//	LocXIPID.Pout = LocXIPID.P * LocXIPID.error;
//	LocXIPID.Iout+= LocXIPID.I * LocXIPID.error * (dataTick[HisPoint] - dataTick[(HisPoint + HisLength + 1) % HisLength]) / 100;
//	LocXIPID.Dout = LocXIPID.D * (LocXIPID.error - LocXIPID.LastError) / (dataTick[HisPoint] - dataTick[(HisPoint + HisLength + 1) % HisLength]);
//	
//	LocXIPID.Iout = LocXIPID.Iout > LocXIPID.IMax ? LocXIPID.IMax : LocXIPID.Iout;
//	LocXIPID.Iout = LocXIPID.Iout <-LocXIPID.IMax ?-LocXIPID.IMax : LocXIPID.Iout;
//	
//	LocXIPID.PIDout = LocXIPID.Pout + LocXIPID.Iout + LocXIPID.Dout;
//	
//	LocXIPID.PIDout = LocXIPID.PIDout > LocXIPID.PIDMax ? LocXIPID.PIDMax : LocXIPID.PIDout;
//	LocXIPID.PIDout = LocXIPID.PIDout <-LocXIPID.PIDMax ?-LocXIPID.PIDMax : LocXIPID.PIDout;
//	
//	LocXIPID.LastError = LocXIPID.error;
//	
//	//Y out
//	LocYOPID.error = T[1] - BallPostion[1][HisPoint];
//	
//	LocYOPID.Pout = LocYOPID.P * LocYOPID.error;
//	LocYOPID.Iout+= LocYOPID.I * LocYOPID.error;
//	LocYOPID.Dout =-LocYOPID.D *  BallSpeed[1];
//	
//	LocYOPID.Iout = LocYOPID.Iout > LocYOPID.IMax ? LocYOPID.IMax : LocYOPID.Iout;
//	LocYOPID.Iout = LocYOPID.Iout <-LocYOPID.IMax ?-LocYOPID.IMax : LocYOPID.Iout;
//	
//	LocYOPID.PIDout = LocYOPID.Pout + LocYOPID.Iout + LocYOPID.Dout;
//	
//	LocYOPID.PIDout = LocYOPID.PIDout > LocYOPID.PIDMax ? LocYOPID.PIDMax : LocYOPID.PIDout;
//	LocYOPID.PIDout = LocYOPID.PIDout <-LocYOPID.PIDMax ?-LocYOPID.PIDMax : LocYOPID.PIDout;
//	
//	LocYOPID.LastError = LocYOPID.error;
//	
//	//Y in
//	LocYIPID.error = LocYOPID.PIDout - BallSpeed[1];
//	LocYIPID.error = DebugSpeed[1] - BallSpeed[1];
//	
//	LocYIPID.Pout = LocYIPID.P * LocYIPID.error;
//	LocYIPID.Iout+= LocYIPID.I * LocYIPID.error;
//	LocYIPID.Dout = LocYIPID.D * (LocYIPID.error - LocYIPID.LastError);
//	
//	LocYIPID.Iout = LocYIPID.Iout > LocYIPID.IMax ? LocYIPID.IMax : LocYIPID.Iout;
//	LocYIPID.Iout = LocYIPID.Iout <-LocYIPID.IMax ?-LocYIPID.IMax : LocYIPID.Iout;
//	
//	LocYIPID.PIDout = LocYIPID.Pout + LocYIPID.Iout + LocYIPID.Dout;
//	
//	LocYIPID.PIDout = LocYIPID.PIDout > LocYIPID.PIDMax ? LocYIPID.PIDMax : LocYIPID.PIDout;
//	LocYIPID.PIDout = LocYIPID.PIDout <-LocYIPID.PIDMax ?-LocYIPID.PIDMax : LocYIPID.PIDout;
//	
//	LocYIPID.LastError = LocYIPID.error;
//	
//	
//	///////////////////
//	A[0] = LocXIPID.PIDout;
//	A[1] = LocYIPID.PIDout;
//}




PIDType LocXPID = 
{
	.error = 0,
	.deathWidth = 3,
	.P = 0.05,
	.I = 0.01,
	.D = 0.8,
	.Pout = 0,
	.Iout = 0,
	.Dout = 0,
	.PIDout = 0,
	.IMax = 0.75,
	.PIDMax = 2,
	.LastError = 0,
	.LastPIDout = 0,
};
PIDType LocYPID = 
{
	.error = 0,
	.deathWidth = 3,
	.P = 0.05,
	.I = 0.01,
	.D = 0.8,
	.Pout = 0,
	.Iout = 0,
	.Dout = 0,
	.PIDout = 0,
	.IMax = 0.75,
	.PIDMax = 2,
	.LastError = 0,
	.LastPIDout = 0,
};

float R = 10;
float XOutFilterUP = 3;
float XOutFilterDOWN = 0.3;
float YOutFilterUP = 3;
float YOutFilterDOWN = 0.3;

void Ball_LocPID(float *T, float *S)
{
	LocXPID.error = T[0] - BallPostion[0][HisPoint];
	
	if(LocXPID.error > LocXPID.deathWidth)
	{
		LocXPID.error -= LocXPID.deathWidth;
	}
	else if(LocXPID.error < -LocXPID.deathWidth)
	{
		LocXPID.error += LocXPID.deathWidth;
	}
	
	LocXPID.Pout = LocXPID.P * LocXPID.error;
	LocXPID.Dout =-LocXPID.D *  BallSpeed[0];
	
//	if((LocXPID.error > 0 ? LocXPID.error : -LocXPID.error) >= (LocXPID.LastError > 0 ? LocXPID.LastError : -LocXPID.LastError))
//	{
		LocXPID.Iout+= LocXPID.I * LocXPID.error;
//	}
//	else
//	{
//		LocXPID.Iout+= LocXPID.I * LocXPID.error * R;
//	}
	LocXPID.Iout = LocXPID.Iout > LocXPID.IMax ? LocXPID.IMax : LocXPID.Iout;
	LocXPID.Iout = LocXPID.Iout <-LocXPID.IMax ?-LocXPID.IMax : LocXPID.Iout;
	
	LocXPID.PIDout = LocXPID.Pout + LocXPID.Iout + LocXPID.Dout;
	
	LocXPID.PIDout = LocXPID.PIDout > LocXPID.PIDMax ? LocXPID.PIDMax : LocXPID.PIDout;
	LocXPID.PIDout = LocXPID.PIDout <-LocXPID.PIDMax ?-LocXPID.PIDMax : LocXPID.PIDout;
	
	LocXPID.LastError = LocXPID.error;
	
	/////////////////////////////////////////
	
	
	LocYPID.error = T[1] - BallPostion[1][HisPoint];
	
	if(LocYPID.error > LocYPID.deathWidth)
	{
		LocYPID.error -= LocYPID.deathWidth;
	}
	else if(LocYPID.error < -LocYPID.deathWidth)
	{
		LocYPID.error += LocYPID.deathWidth;
	}
	
	LocYPID.Pout = LocYPID.P * LocYPID.error;
	LocYPID.Iout+= LocYPID.I * LocYPID.error;
	LocYPID.Dout =-LocYPID.D *  BallSpeed[1];
	
	LocYPID.Iout = LocYPID.Iout > LocYPID.IMax ? LocYPID.IMax : LocYPID.Iout;
	LocYPID.Iout = LocYPID.Iout <-LocYPID.IMax ?-LocYPID.IMax : LocYPID.Iout;
	
	LocYPID.PIDout = LocYPID.Pout + LocYPID.Iout + LocYPID.Dout;
	
	LocYPID.PIDout = LocYPID.PIDout > LocYPID.PIDMax ? LocYPID.PIDMax : LocYPID.PIDout;
	LocYPID.PIDout = LocYPID.PIDout <-LocYPID.PIDMax ?-LocYPID.PIDMax : LocYPID.PIDout;
	
	LocYPID.LastError = LocYPID.error;
	
	//////////////////////////////
	
//	if(LocXPID.PIDout > 0)
//	{
//		if((LocXPID.PIDout < XOutFilterUP) && (LocXPID.PIDout > XOutFilterDOWN))
//		{
//			S[0] = XOutFilterUP;
//		}
//		else
//		{
//			S[0] = LocXPID.PIDout;
//		}
//	}
//	else
//	{
//		if((LocXPID.PIDout > -XOutFilterUP) && (LocXPID.PIDout < -XOutFilterDOWN))
//		{
//			S[0] = -XOutFilterUP;
//		}
//		else
//		{
//			S[0] = LocXPID.PIDout;
//		}
//	}
//	
//	if(LocYPID.PIDout > 0)
//	{
//		if((LocYPID.PIDout < YOutFilterUP) && (LocYPID.PIDout > YOutFilterDOWN))
//		{
//			S[1] = YOutFilterUP;
//		}
//		else
//		{
//			S[1] = LocYPID.PIDout;
//		}
//	}
//	else
//	{
//		if((LocYPID.PIDout > -YOutFilterUP) && (LocYPID.PIDout < -YOutFilterDOWN))
//		{
//			S[1] = -YOutFilterUP;
//		}
//		else
//		{
//			S[1] = LocYPID.PIDout;
//		}
//	}
	
	
	if((LocXPID.error < LocXPID.deathWidth) && (LocXPID.error > -LocXPID.deathWidth))
	{
		S[0] = 0;
	}
	else
	{
		S[0] = LocXPID.PIDout;
	}
	if((LocYPID.error < LocYPID.deathWidth) && (LocYPID.error > -LocYPID.deathWidth))
	{
		S[1] = 0;
	}
	else
	{
		S[1] = LocYPID.PIDout;
	}
}




#define ErrorHisLen	4

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
	float LastError[ErrorHisLen];
	uint32_t LastErrortick[ErrorHisLen];
	float LastPIDout;
}SPIDType;

SPIDType LocXISPID = 
{
	.error = 0,
	.deathWide = 0,
	.P = 0.4,
	.I = 0.02,
	.D = 0,
	.Pout = 0,
	.Iout = 0,
	.Dout = 0,
	.PIDout = 0,
	.IMax = 1.2,
	.PIDMax = 3,
	.LastError = {0,0,0,0},
	.LastErrortick = {0,0,0,0},
	.LastPIDout = 0,
};

SPIDType LocYISPID = 
{
	.error = 0,
	.deathWide = 0,
	.P = 0.4,
	.I = 0.02,
	.D = 0,
	.Pout = 0,
	.Iout = 0,
	.Dout = 0,
	.PIDout = 0,
	.IMax = 1.2,
	.PIDMax = 3,
	.LastError = {0,0,0,0},
	.LastErrortick = {0,0,0,0},
	.LastPIDout = 0,
};

//D
float DEThread = 20;			//误差小于此值进行非线性处理
float DECRCenter = 0.01;		//微分强度阈值在此点为0
float DRate;					//微分强度

float errorChangeRateX;			//误差变化率
float errorChangeRateY;			//误差变化率

//I
float MaxIntThread = 15;		//积分起始点，小于此值才积分
float EDER2;					//误差二阶导数，用于判断凹凸
float EDER2Thread = 0.02;
float IntRate;

void Ball_SpeedPID(float *T,float *A, uint32_t tick)
{
	uint8_t index;
	float sumXY = 0, sumX = 0, sumY = 0, sumXX = 0;
	float tickTemp;
	
	
	/***************************************	X	*********************************************/
	
	//计算当前误差
	LocXISPID.error = T[0] - BallSpeed[0];
	LocXISPID.error = DebugSpeed[0] - BallSpeed[0];
	
	//历史数据记录整理
	for(index = ErrorHisLen - 1; index > 0; index--)
	{
		LocXISPID.LastError[index] = LocXISPID.LastError[index-1];
		LocXISPID.LastErrortick[index] = LocXISPID.LastErrortick[index-1];
	}
	LocXISPID.LastError[0] = LocXISPID.error;
	LocXISPID.LastErrortick[0] = tick;
	
	//简单P处理
	LocXISPID.Pout = LocXISPID.P * LocXISPID.error;
	
	//最小二乘法计算误差变化率(D)
	sumXY = 0; 
	sumX = 0; 
	sumY = 0; 
	sumXX = 0;
	for(index = 0; index < ErrorHisLen; index++)
	{
		tickTemp = LocXISPID.LastErrortick[index] - LocXISPID.LastErrortick[ErrorHisLen - 1];
		sumXY += tickTemp * LocXISPID.LastError[index];
		sumX += tickTemp;
		sumXX += tickTemp * tickTemp;
		sumY += LocXISPID.LastError[index];
	}
	errorChangeRateX = (ErrorHisLen * sumXY - sumX * sumY) / (ErrorHisLen * sumXX - sumX * sumX);
	
	//计算微分强度
	if(LocXISPID.error > 0)
	{
		if(LocXISPID.error > DEThread)
		{
			DRate = 1;
		}
		else
		{
			DRate = LocXISPID.error * LocXISPID.error / DEThread / DEThread;
		}
		LocXISPID.Dout = LocXISPID.D * (errorChangeRateX + DECRCenter) * DRate;
	}
	else
	{
		if(LocXISPID.error < -DEThread)
		{
			DRate = 1;
		}
		else
		{
			DRate = LocXISPID.error * LocXISPID.error / DEThread / DEThread;
		}
		LocXISPID.Dout = LocXISPID.D * (errorChangeRateX -	 DECRCenter) * DRate;
	}
	
	
	//静差分析(I)
	//积分强度
	EDER2 = (LocXISPID.LastError[0] - LocXISPID.LastError[2]) / (LocXISPID.LastErrortick[0] - LocXISPID.LastErrortick[2])
			- (LocXISPID.LastError[1] - LocXISPID.LastError[3]) / (LocXISPID.LastErrortick[1] - LocXISPID.LastErrortick[3]);
//	if((LocXISPID.error < MaxIntThread) && (LocXISPID.error > 0))
	//0至MaxIntThread为积分范围
//	{
//		if(errorChangeRateX > 0)
//		//误差在增加
//		{
//			
//		}
//		else
//		{
//			
//		}
//	}
	
//	if((LocXISPID.error < MaxIntThread) && (LocXISPID.error > -MaxIntThread))
//	{
//		LocXISPID.Iout += LocXISPID.I * LocXISPID.error * (1 - EDER2 / EDER2Thread);
//	}
	LocXISPID.Iout += LocXISPID.I * LocXISPID.error;
	
//	if(LocXISPID.LastError[0] * LocXISPID.LastError[1] < 0)
//	{
//		LocXISPID.Iout = 0;
//	}
	
//	if((LocXISPID.error < 2) && (LocXISPID.error > -2))
//	{
//		LocXISPID.Iout = 0;
//	}
	
	LocXISPID.Iout = LocXISPID.Iout > LocXISPID.IMax ? LocXISPID.IMax : LocXISPID.Iout;
	LocXISPID.Iout = LocXISPID.Iout <-LocXISPID.IMax ?-LocXISPID.IMax : LocXISPID.Iout;
	
	//sum PID
	LocXISPID.PIDout = LocXISPID.Pout + LocXISPID.Dout + LocXISPID.Iout;
	
	LocXISPID.PIDout = LocXISPID.PIDout > LocXISPID.PIDMax ? LocXISPID.PIDMax : LocXISPID.PIDout;
	LocXISPID.PIDout = LocXISPID.PIDout <-LocXISPID.PIDMax ?-LocXISPID.PIDMax : LocXISPID.PIDout;
	
	/***************************************	Y	*********************************************/
	
	//计算当前误差
	LocYISPID.error = T[1] - BallSpeed[1];
	LocYISPID.error = DebugSpeed[1] - BallSpeed[1];
	
	//历史数据记录整理
	for(index = ErrorHisLen - 1; index > 0; index--)
	{
		LocYISPID.LastError[index] = LocYISPID.LastError[index-1];
		LocYISPID.LastErrortick[index] = LocYISPID.LastErrortick[index-1];
	}
	LocYISPID.LastError[0] = LocYISPID.error;
	LocYISPID.LastErrortick[0] = tick;
	
	//简单P处理
	LocYISPID.Pout = LocYISPID.P * LocYISPID.error;
	
	//最小二乘法计算误差变化率(D)
	sumXY = 0; 
	sumX = 0; 
	sumY = 0; 
	sumXX = 0;
	for(index = 0; index < ErrorHisLen; index++)
	{
		tickTemp = LocYISPID.LastErrortick[index] - LocYISPID.LastErrortick[ErrorHisLen - 1];
		sumXY += tickTemp * LocYISPID.LastError[index];
		sumX += tickTemp;
		sumXX += tickTemp * tickTemp;
		sumY += LocYISPID.LastError[index];
	}
	errorChangeRateX = (ErrorHisLen * sumXY - sumX * sumY) / (ErrorHisLen * sumXX - sumX * sumX);
	
	//计算微分强度
	if(LocYISPID.error > 0)
	{
		if(LocYISPID.error > DEThread)
		{
			DRate = 1;
		}
		else
		{
			DRate = LocYISPID.error * LocYISPID.error / DEThread / DEThread;
		}
		LocYISPID.Dout = LocYISPID.D * (errorChangeRateX + DECRCenter) * DRate;
	}
	else
	{
		if(LocYISPID.error < -DEThread)
		{
			DRate = 1;
		}
		else
		{
			DRate = LocYISPID.error * LocYISPID.error / DEThread / DEThread;
		}
		LocYISPID.Dout = LocYISPID.D * (errorChangeRateX -	 DECRCenter) * DRate;
	}
	
	
	//静差分析(I)
	//积分强度
	EDER2 = (LocYISPID.LastError[0] - LocYISPID.LastError[2]) / (LocYISPID.LastErrortick[0] - LocYISPID.LastErrortick[2])
			- (LocYISPID.LastError[1] - LocYISPID.LastError[3]) / (LocYISPID.LastErrortick[1] - LocYISPID.LastErrortick[3]);
//	if((LocYISPID.error < MaxIntThread) && (LocYISPID.error > 0))
	//0至MaxIntThread为积分范围
//	{
//		if(errorChangeRateX > 0)
//		//误差在增加
//		{
//			
//		}
//		else
//		{
//			
//		}
//	}
	
//	if((LocYISPID.error < MaxIntThread) && (LocYISPID.error > -MaxIntThread))
//	{
//		LocYISPID.Iout += LocYISPID.I * LocYISPID.error * (1 - EDER2 / EDER2Thread);
//	}
	LocYISPID.Iout += LocYISPID.I * LocYISPID.error;
	
//	if(LocYISPID.LastError[0] * LocYISPID.LastError[1] < 0)
//	{
//		LocYISPID.Iout = 0;
//	}
	
//	if((LocYISPID.error < 2) && (LocYISPID.error > -2))
//	{
//		LocYISPID.Iout = 0;
//	}
	
	LocYISPID.Iout = LocYISPID.Iout > LocYISPID.IMax ? LocYISPID.IMax : LocYISPID.Iout;
	LocYISPID.Iout = LocYISPID.Iout <-LocYISPID.IMax ?-LocYISPID.IMax : LocYISPID.Iout;
	
	//sum PID
	LocYISPID.PIDout = LocYISPID.Pout + LocYISPID.Dout + LocYISPID.Iout;
	
	LocYISPID.PIDout = LocYISPID.PIDout > LocYISPID.PIDMax ? LocYISPID.PIDMax : LocYISPID.PIDout;
	LocYISPID.PIDout = LocYISPID.PIDout <-LocYISPID.PIDMax ?-LocYISPID.PIDMax : LocYISPID.PIDout;
	
	///////////////////
	A[0] = LocXISPID.PIDout;
	A[1] = LocYISPID.PIDout;
}



/**
  * @brief  清空PID积分
  * @param  void
  * @retval void
  */
void Ball_ClearInt(void)
{
//	LocXOPID.Iout = 0;
//	LocXIPID.Iout = 0;
//	LocYOPID.Iout = 0;
//	LocYIPID.Iout = 0;
	LocXISPID.Iout = 0;
	LocYISPID.Iout = 0;
}



