#ifndef __UICALLBACK_H
#define __UICALLBACK_H


#include "stm32f4xx.h"
#include "UIDataStruction.h"


void SetModeCallBack(Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY);
void SetACallBack(Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY);
void SetBCallBack(Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY);
void SetCCallBack(Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY);
void SetDCallBack(Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY);
void ConfirmCallBack(Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY);
void XPlusAlignCallBack(Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY);
void XMinusAlignCallBack(Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY);
void YPlusAlignCallBack(Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY);
void YMinusAlignCallBack(Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY);




#endif
