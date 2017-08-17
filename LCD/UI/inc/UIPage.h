#ifndef __UIPAGE_H
#define __UIPAGE_H

#include "UI.h"
#include "UIDataStruction.h"
#include "UIControl.h"
#include "UIButton.h"
#include "UIPositioningPanel.h"
#include "UIIME.h"


//�ؼ�����ڵ�ṹ��
typedef struct ControlsChainNode_Type
{
	struct ControlsChainNode_Type *previous;
	struct ControlsChainNode_Type *next;
	Control_Type control;
	ui2 ID;				//�ؼ�ID����1��ʼ����bottom��ʼ����
	ui1 needFresh;		//1��Ҫˢ�� 0����Ҫˢ��
}ControlsChainNode_Type;


//�ؼ������ܽṹ��
typedef struct ControlsChain_Type
{
	struct ControlsChainNode_Type *top;
	struct ControlsChainNode_Type *bottom;
	ui1 counter;
}ControlsChain_Type;

//mode 0ȡ�����˳�		1 ȷ�����˳�
typedef void (*Page_ExitIMECallBack)(uint8_t mode, float data);

//ҳ�ṹ��
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

