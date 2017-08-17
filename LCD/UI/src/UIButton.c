#include "UIButton.h"
#include "UIDrawRAM.h"
#include "OSinclude.h"


void ButtonInitDefault(Control_Type *Button)
{
	//λ�óߴ���ɫ��ʼ��
	Button->backColor = 0xFFFF;
	Button->frontColor = 0x0000;
	Button->frameColor = 0xF800;
	((ButtonBody_Type *)Button->body)->text = NULL;
	((ButtonBody_Type *)Button->body)->textSize = Font0816;
	((ButtonBody_Type *)(Button->body))->withFrame = 1;
	Button->OnPush = NULL;
	Button->OnLift = NULL;
}


//���ƿؼ�
void Button_Draw(ui2 *Buffer, Control_Type *Button)
{
	uint16_t singleTextWidth, textWidth, textHeight, startx, starty, textNum, index;
	char *textPoint;
	
	DrawRAM_Rect(Buffer, Button->pos.x, Button->pos.y, Button->size.x, Button->size.y, Button->backColor, 2, 1);
	
	if(((ButtonBody_Type *)(Button->body))->withFrame)
	{
		DrawRAM_Rect(Buffer, Button->pos.x, Button->pos.y, Button->size.x, Button->size.y, Button->frameColor, 2, 0);
	}
	
	textPoint = ((ButtonBody_Type *)(Button->body))->text;
	for(textNum = 0; *(textPoint++) != 0; textNum++);
	
	
	switch(((ButtonBody_Type *)(Button->body))->textSize)
	{
		case Font0816 : singleTextWidth =  8; textHeight = 16; break;
		case Font1020 : singleTextWidth = 10; textHeight = 20; break;
		case Font1224 : singleTextWidth = 12; textHeight = 24; break;
		case Font1633 : singleTextWidth = 16; textHeight = 33; break;
		case Font2448 : singleTextWidth = 24; textHeight = 48; break;
		case Font3264 : singleTextWidth = 32; textHeight = 64; break;
	}
	textWidth = singleTextWidth * textNum;
	
	if(textWidth < Button->size.x)
	{
		startx = (Button->size.x - textWidth) / 2 + Button->pos.x;
	}
	else
	{
		startx = Button->pos.x;
	}
	
	if(textHeight < Button->size.y)
	{
		starty = (Button->size.y - textHeight) / 2 + Button->pos.y;
	}
	else
	{
		starty = Button->pos.y;
	}
	
	textPoint = ((ButtonBody_Type *)(Button->body))->text;
//	for(textNum = 0; *textPoint != 0; textNum++)
//	{
		DrawRAM_ASCIIStr(Buffer, startx, starty, textPoint, ((ButtonBody_Type *)(Button->body))->textSize, Button->frontColor, Button->backColor, 1);
//		textPoint++;
//		startx += singleTextWidth;
//	}
}

//��������
uint8_t Button_SetText(Control_Type *Button, char *Text)
{
	uint16_t textLen, index;
	char *newStr, *newRAM, *newRAMTemp;
	
	//��ȡ�ַ�������
	newStr = Text;
	for(textLen = 0; *(newStr++) != 0; textLen++);
	textLen++;
	
	//�����ڴ�
	newRAM = pvPortMalloc(textLen);
	
	//ʧ�ܷ���
	if(newRAM == NULL)
	{
		return 1;
	}
	
	//�������ַ���
	newRAMTemp = newRAM;
	newStr = Text;
	for(index = 0; index < textLen; index++)
	{
		*(newRAMTemp++) = *(newStr++);
	}
	
	//�ͷž��ڴ�
	if(((ButtonBody_Type *)(Button->body))->text != NULL)
	{
		vPortFree(((ButtonBody_Type *)(Button->body))->text);
	}
	
	//ָ�����ַ���
	((ButtonBody_Type *)(Button->body))->text = newRAM;
}


//��������
void Button_SetFont(Control_Type *Button, FontEnum F)
{
	((ButtonBody_Type *)(Button->body))->textSize = F;
}


//�ؼ������¼�
//param:���µľ���λ��
void Button_Pushed(Control_Type *Button, PointI_Type Pos)
{

}

//�ؼ����º��ɿ��¼�
//param:�ɿ��ľ���λ��
void Button_Lift(Control_Type *Button, PointI_Type Pos)
{

}
