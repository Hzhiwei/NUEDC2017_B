#ifndef __UIIME_H
#define __UIIME_H


#include "stm32f4xx.h"
#include "UIDataStruction.h"


#define IMEMAXCHARNUM	10
typedef struct
{
	char text[IMEMAXCHARNUM + 1];	//输入字符
	uint8_t textNum;				//字符数量
	FontEnum textSize;				//文字字号
	float data;						//文字字号
}IMEBody_Type;


void IMEInitDefault(Control_Type *IME);
void IME_Draw(ui2 *Buffer, Control_Type *IME);
void IME_OnPush(Control_Type *IME, uint8_t Status, uint16_t PosX, uint16_t PosY);



#endif
