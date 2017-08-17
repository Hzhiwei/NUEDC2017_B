#ifndef __DRIVER_LCD5310_H
#define __DRIVER_LCD5310_H


#include "stm32f4xx.h"


#define LCD_WIDTH	480
#define LCD_HEIGHT	320



uint8_t LCD_InitConfig(void);
void  LCD_Clear(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height, uint16_t point);
void  LCD_Fill(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height, uint16_t * const point);


#endif

