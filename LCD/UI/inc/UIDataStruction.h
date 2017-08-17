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

	


//��ṹ
typedef struct
{
	ui2 x;
	ui2 y;
}PointI_Type;


//����
typedef enum
{
	Font0816,
	Font1020,
	Font1224,
	Font1633,
	Font2448,
	Font3264
}FontEnum;


//�ؼ�����
#warning �ؼ��������
typedef enum 
{
	Control_Button,			//����
	Control_IME,			//���뷨
	Control_PositionPanel,	//λ����ʾ�ؼ�
//	Control_TextLine,	//�����ı���
//	Control_TextBox,	//�ı���
//	Control_ProgressBar,//������
//	Control_PicBox,		//ͼƬ��
//	Control_Indicator	//ָʾ��
}Control_Enum;

struct Control_Type;	//����ȫ������ΪTouchCallBack׼��
//���»ص�����	Status:1���� 0̧��
typedef void (*TouchCallBack)(struct Control_Type *Control, uint8_t Status, uint16_t PosX, uint16_t PosY);


//�ؼ��ṹ��
typedef struct Control_Type
{
	Control_Enum type;				//�ؼ�����
	PointI_Type pos;				//���Ͻ�λ��
	PointI_Type size;				//����
	ui2 backColor;					//����ɫ
	ui2 frontColor;					//ǰ��ɫ
	ui2 frameColor;					//�߿�ɫ
	void *body;		  				//�ؼ���������
	TouchCallBack OnPush;			//���»ص�����
	TouchCallBack OnLift;			//�ɿ��ص�����
	uint8_t visiable;				//1�ɼ� 0���ɼ�
}Control_Type;





#endif
