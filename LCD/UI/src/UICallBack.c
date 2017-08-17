#include "UICallback.h"
#include "UIPage.h"
#include "task_UARTDMASend.h"
#include <stdio.h>


#define FUNCNUM	8
#define XDIEMAX	100
#define XDIEMIN	-100
#define YDIEMAX	100
#define YDIEMIN	-100


extern Page_Type *Page;
extern UploadData_Type UARTSendBuffer;


float CallBackDataTemp[5] = {0, 1, 2, 3, 4};
uint8_t CallBackTranslateDataTemp[5] = {0, 1, 2, 3, 4};
Control_Type *CallBackControlTemp[5];


void SetModeExitCallBack(uint8_t Status, float Data);
void SetAExitCallBack(uint8_t Status, float Data);
void SetBExitCallBack(uint8_t Status, float Data);
void SetCExitCallBack(uint8_t Status, float Data);
void SetDExitCallBack(uint8_t Status, float Data);



//设置模式
void SetModeCallBack(Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY)
{
	Page_GetIMEData(Page, &CallBackDataTemp[0], SetModeExitCallBack);
	CallBackControlTemp[0] = Control;
}
void SetModeExitCallBack(uint8_t Status, float Data)
{
	if(Status)
	{
		CallBackDataTemp[0] = CallBackDataTemp[0] > FUNCNUM ? FUNCNUM : CallBackDataTemp[0];
		CallBackDataTemp[0] = CallBackDataTemp[0] < 0 ? 0 : CallBackDataTemp[0];
		
		CallBackTranslateDataTemp[0] = CallBackDataTemp[0];
		
		sprintf(((ButtonBody_Type *)(CallBackControlTemp[0]->body))->text, "%d", CallBackTranslateDataTemp[0]);
	}
}

//设置A点编号
void SetACallBack(Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY)
{
	Page_GetIMEData(Page, &CallBackDataTemp[1], SetAExitCallBack);
	CallBackControlTemp[1] = Control;
}
void SetAExitCallBack(uint8_t Status, float Data)
{
	if(Status)
	{
		CallBackDataTemp[1] = CallBackDataTemp[1] > 9 ? 9 : CallBackDataTemp[1];
		CallBackDataTemp[1] = CallBackDataTemp[1] < 1 ? 1 : CallBackDataTemp[1];
		
		CallBackTranslateDataTemp[1] = CallBackDataTemp[1];
		
		sprintf(((ButtonBody_Type *)(CallBackControlTemp[1]->body))->text, "%d", CallBackTranslateDataTemp[1]);
	}
}

//设置B点编号
void SetBCallBack(Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY)
{
	Page_GetIMEData(Page, &CallBackDataTemp[2], SetBExitCallBack);
	CallBackControlTemp[2] = Control;
}
void SetBExitCallBack(uint8_t Status, float Data)
{
	if(Status)
	{
		CallBackDataTemp[2] = CallBackDataTemp[2] > 9 ? 9 : CallBackDataTemp[2];
		CallBackDataTemp[2] = CallBackDataTemp[2] < 1 ? 1 : CallBackDataTemp[2];
		
		CallBackTranslateDataTemp[2] = CallBackDataTemp[2];
		
		sprintf(((ButtonBody_Type *)(CallBackControlTemp[2]->body))->text, "%d", CallBackTranslateDataTemp[2]);
	}
}

//设置C点编号
void SetCCallBack(Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY)
{
	Page_GetIMEData(Page, &CallBackDataTemp[3], SetCExitCallBack);
	CallBackControlTemp[3] = Control;
}
void SetCExitCallBack(uint8_t Status, float Data)
{
	if(Status)
	{
		CallBackDataTemp[3] = CallBackDataTemp[3] > 9 ? 9 : CallBackDataTemp[3];
		CallBackDataTemp[3] = CallBackDataTemp[3] < 1 ? 1 : CallBackDataTemp[3];
		
		CallBackTranslateDataTemp[3] = CallBackDataTemp[3];
		
		sprintf(((ButtonBody_Type *)(CallBackControlTemp[3]->body))->text, "%d", CallBackTranslateDataTemp[3]);
	}
}

//设置D点编号
void SetDCallBack(Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY)
{
	Page_GetIMEData(Page, &CallBackDataTemp[4], SetDExitCallBack);
	CallBackControlTemp[4] = Control;
}
void SetDExitCallBack(uint8_t Status, float Data)
{
	if(Status)
	{
		CallBackDataTemp[4] = CallBackDataTemp[4] > 9 ? 9 : CallBackDataTemp[4];
		CallBackDataTemp[4] = CallBackDataTemp[4] < 1 ? 1 : CallBackDataTemp[4];
		
		CallBackTranslateDataTemp[4] = CallBackDataTemp[4];
		
		sprintf(((ButtonBody_Type *)(CallBackControlTemp[4]->body))->text, "%d", CallBackTranslateDataTemp[4]);
	}
}

//确认fasong数据
void ConfirmCallBack(Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY)
{
	UARTSendBuffer.mode = CallBackDataTemp[0];
	UARTSendBuffer.fourNode[0] = CallBackDataTemp[1];
	UARTSendBuffer.fourNode[1] = CallBackDataTemp[2];
	UARTSendBuffer.fourNode[2] = CallBackDataTemp[3];
	UARTSendBuffer.fourNode[3] = CallBackDataTemp[4];
}

//X+校准
void XPlusAlignCallBack(Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY)
{
	if(UARTSendBuffer.align & 0x08)
	{
		UARTSendBuffer.align &= 0xF7;
	}
	else
	{
		UARTSendBuffer.align |= 0x08;
	}
}

//X-校准
void XMinusAlignCallBack(Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY)
{
	if(UARTSendBuffer.align & 0x04)
	{
		UARTSendBuffer.align &= 0xFB;
	}
	else
	{
		UARTSendBuffer.align |= 0x04;
	}
}

//Y+校准
void YPlusAlignCallBack(Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY)
{
	if(UARTSendBuffer.align & 0x02)
	{
		UARTSendBuffer.align &= 0xFD;
	}
	else
	{
		UARTSendBuffer.align |= 0x02;
	}
}

//Y-校准
void YMinusAlignCallBack(Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY)
{
	if(UARTSendBuffer.align & 0x01)
	{
		UARTSendBuffer.align &= 0xFE;
	}
	else
	{
		UARTSendBuffer.align |= 0x01;
	}
}


