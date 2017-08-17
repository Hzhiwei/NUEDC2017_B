#ifndef __UIBUTTON_H
#define __UIBUTTON_H

#include "stm32f4xx.h"
#include "UIDataStruction.h"
#include "UIControl.h"


typedef struct
{
	char *text;						//����
	FontEnum textSize;				//�����ֺ�
	uint8_t withFrame;				//1 �б߿�	0 �ޱ߿�
}ButtonBody_Type;


void ButtonInitDefault(Control_Type *Button);
void Button_Draw(ui2 *Buffer, Control_Type *Button);
void Button_Pushed(Control_Type *Button, PointI_Type Pos);
void Button_Lift(Control_Type *Button, PointI_Type Pos);
uint8_t Button_SetText(Control_Type *Button, char *Text);
void Button_SetFont(Control_Type *Button, FontEnum F);


#endif
