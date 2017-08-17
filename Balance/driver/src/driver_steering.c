#include "driver_steering.h"
#include <math.h>


#define ANGLELIMIT	5


float XPWMPerAngle = 7.08;
float YPWMPerAngle = 7.599;

float XAlpha0 = 4.3181 * 3.1415927 / 180;
float XL1 = 258.75;
float XL2 = 55.5;
float XL3 = 22;
float XDx = 279.5;
float XDy = -39;

float YAlpha0 = 4.1093 * 3.1415927 / 180;
float YL1 = 258.25;
float YL2 = 55;
float YL3 = 22;
float YDx = 280;
float YDy = -36.5;



/**
  * @brief  舵机初始化
  * @param  void
  * @brief  void
  */
void steering_InitConfig(void)
{
	TIM3->CCR4 = XSTEERINGLIMIT_CENTER;
	TIM3->CCR3 = YSTEERINGLIMIT_CENTER;
}	


/**
  * @brief  舵机角度设置
  * @param  舵机编号
  * @param  舵机角度
  * @retval void
  */
void steering_AngleControl(char S, float Angle)
{
	int16_t temp;
	float t;
	float Bx, By;
	float L4;
	float A1, A2;
	float XX, YY;
	float servoAngle;
	
	Angle = Angle > ANGLELIMIT ? ANGLELIMIT : Angle;
	Angle = Angle < -ANGLELIMIT ? -ANGLELIMIT : Angle;
	
	Angle = Angle * 3.1415927 / 180;
	
	if(S == 'X')
	{
		t = XAlpha0 + Angle;
		Bx = XL1 * cos(t);
		By = XL1 * sin(t);
		XX = Bx - XDx;
		XX = XX * XX;
		YY = By - XDy;
		YY = YY * YY;
		L4 = sqrt(XX + YY);
		
		A1 = acos((XL3 * XL3 + L4 * L4 - XL2 * XL2) / (2 * XL3 * L4));
		A2 = -atan((By - XDy) / (Bx - XDx));
		servoAngle = A2 - A1;
		servoAngle = servoAngle * 180 / 3.1415927;
		
		temp = 1500 + servoAngle * XPWMPerAngle;
		
		TIM3->CCR4 = temp;
	}
	else if(S == 'Y')
	{
		t = YAlpha0 + Angle;
		Bx = YL1 * cos(t);
		By = YL1 * sin(t);
		XX = Bx - YDx;
		XX = XX * XX;
		YY = By - YDy;
		YY = YY * YY;
		L4 = sqrt(XX + YY);
		
		A1 = acos((YL3 * YL3 + L4 * L4 - YL2 * YL2) / (2 * YL3 * L4));
		A2 = -atan((By - YDy) / (Bx - YDx));
		servoAngle = A2 - A1;
		servoAngle = servoAngle * 180 / 3.1415927;
		
		temp = 1500 + servoAngle * YPWMPerAngle;
		
		TIM3->CCR3 = temp;
	}
}
