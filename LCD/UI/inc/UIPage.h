#ifndef __UIPAGE_H
#define __UIPAGE_H

#include "UI.h"
#include "UIDataStruction.h"
#include "UIControl.h"
#include "UIButton.h"
#include "UIPositioningPanel.h"
#include "UIIME.h"


//控件链表节点结构体
typedef struct ControlsChainNode_Type
{
	struct ControlsChainNode_Type *previous;
	struct ControlsChainNode_Type *next;
	Control_Type control;
	ui2 ID;				//控件ID，从1开始，从bottom开始计数
	ui1 needFresh;		//1需要刷新 0不需要刷新
}ControlsChainNode_Type;


//控件链表总结构体
typedef struct ControlsChain_Type
{
	struct ControlsChainNode_Type *top;
	struct ControlsChainNode_Type *bottom;
	ui1 counter;
}ControlsChain_Type;

//mode 0取消型退出		1 确认型退出
typedef void (*Page_ExitIMECallBack)(uint8_t mode, float data);

//页结构体
typedef struct
{
	ui2 backColor;
	ui2 *VRAM;
	ControlsChain_Type controlChain;
	uint8_t IMEmode;
	float *IMEdate;
	Page_ExitIMECallBack ExitIME;
}Page_Type;


Page_Type *Page_New(ui2 *Buffer);
Control_Type *Page_AddControl(Page_Type *P, Control_Enum CT, PointI_Type L, PointI_Type S);
ui1 Page_DelateControlByID(Page_Type *P, ui2 ID);
ui2 Page_GetControlIDbyPoint(Page_Type *P, ControlsChainNode_Type *C);
ControlsChainNode_Type *Page_GetControlPointbyID(Page_Type *P, ui2 ID);
void Page_FreshBuffer(Page_Type *P);
void Page_OnPush(Page_Type *P, uint16_t X, uint16_t Y);
void Page_GetIMEData(Page_Type *P, float *data, Page_ExitIMECallBack Exit);



#endif

