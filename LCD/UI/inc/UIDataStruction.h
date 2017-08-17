#ifndef __UIDATASTRUCTION_H
#define __UIDATASTRUCTION_H


#include "stm32f4xx.h"


#define NULL	((void *)0)


typedef unsigned char  ui1;
typedef signed char    i1;
typedef unsigned short ui2;
typedef short          i2;
typedef unsigned int   ui4;
typedef int            i4;

	


//点结构
typedef struct
{
	ui2 x;
	ui2 y;
}PointI_Type;


//字体
typedef enum
{
	Font0816,
	Font1020,
	Font1224,
	Font1633,
	Font2448,
	Font3264
}FontEnum;


//控件类型
#warning 控件种类相关
typedef enum 
{
	Control_Button,			//按键
	Control_IME,			//输入法
	Control_PositionPanel,	//位置显示控件
//	Control_TextLine,	//单行文本框
//	Control_TextBox,	//文本框
//	Control_ProgressBar,//进度条
//	Control_PicBox,		//图片框
//	Control_Indicator	//指示灯
}Control_Enum;

struct Control_Type;	//不完全声明，为TouchCallBack准备
//按下回调函数	Status:1按下 0抬起
typedef void (*TouchCallBack)(struct Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY);


//控件结构体
typedef struct Control_Type
{
	Control_Enum type;				//控件类型
	PointI_Type pos;				//左上角位置
	PointI_Type size;				//长宽
	ui2 backColor;					//背景色
	ui2 frontColor;					//前景色
	ui2 frameColor;					//边框色
	void *body;		  				//控件特征部分
	TouchCallBack OnPush;			//按下回调函数
	TouchCallBack OnLift;			//松开回调函数
	uint8_t visiable;				//1可见 0不可见
}Control_Type;





#endif
