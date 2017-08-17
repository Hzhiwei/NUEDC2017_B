#ifndef __UIBUTTON_H
#define __UIBUTTON_H

#include "stm32f4xx.h"
#include "UIDataStruction.h"
#include "UIControl.h"


typedef struct
{
	char *text;						//ÎÄ×Ö
	FontEnum textSize;				//ÎÄ×Ö×ÖºÅ
	uint8_t withFrame;				//1 ÓÐ±ß¿ò	0 ÎÞ±ß¿ò
}ButtonBody_Type;


void ButtonInitDefault(Control_Type *Button);
void Button_Draw(ui2 *Buffer, Control_Type *Button);
void Button_Pushed(Control_Type *Button, PointI_Type Pos);
void Button_Lift(Control_Type *Button, PointI_Type Pos);
uint8_t Button_SetText(Control_Type *Button, char *Text);
void Button_SetFont(Control_Type *Button, FontEnum F);


#endif
