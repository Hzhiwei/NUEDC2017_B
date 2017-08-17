#ifndef __DRIVER_LED_H
#define __DRIVER_LED_H


#include "stm32f4xx.h"


#define FLASH_TICK		200			//LED��˸����


#define FLASH_NONE 		0x01		//����
#define FLASH_INIT 		0x02		//��ʼ������ɫ������˸
#define FLASH_WORKING	0x04		//�����������̵���˸
#define FLASH_LOSTIMU	0x08		//�����Ƕ�ʧ

#define FLASH_UARTDATA	0x80		//�������� ����������	��˸������


void LED_InitConfig(void);
void LED_Control(uint8_t Num, uint8_t Status);
void LED_ControlRGB(uint8_t Status);
void LED_SetFlash(uint8_t Status);


#endif
