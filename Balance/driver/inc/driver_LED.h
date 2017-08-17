#ifndef __DRIVER_LED_H
#define __DRIVER_LED_H


#include "stm32f4xx.h"


#define FLASH_TICK		200			//LED闪烁周期


#define FLASH_NONE 		0x01		//不亮
#define FLASH_INIT 		0x02		//初始化，三色轮流闪烁
#define FLASH_WORKING	0x04		//正常工作，绿灯闪烁
#define FLASH_LOSTIMU	0x08		//陀螺仪丢失

#define FLASH_UARTDATA	0x80		//串口数据 常量有数据	闪烁无数据


void LED_InitConfig(void);
void LED_Control(uint8_t Num, uint8_t Status);
void LED_ControlRGB(uint8_t Status);
void LED_SetFlash(uint8_t Status);


#endif
