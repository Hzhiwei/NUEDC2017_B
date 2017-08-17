#ifndef __UIDRAWRAM_H
#define __UIDRAWRAM_H


#include "stm32f4xx.h"
#include "UI.h"
#include "UIDataStruction.h"


void DrawRAM_Point(uint16_t *RAM, uint16_t x, uint16_t y, uint16_t color);
void DrawRAM_Line(uint16_t *RAM, int16_t sx, int16_t sy, int16_t ex, int16_t ey, uint16_t color, uint8_t thickness);
void DrawRAM_Rect(uint16_t *RAM, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color, uint8_t thickness, uint8_t mode);
void DrawRAM_ASCII(uint16_t *RAM, uint16_t x, uint16_t y, char word, FontEnum font, uint16_t color, uint16_t backcolor, uint8_t mode);
void DrawRAM_ASCIIStr(uint16_t *RAM, uint16_t x, uint16_t y, char *word, FontEnum font, uint16_t color, uint16_t backcolor, uint8_t mode);
void DrawRAM_Circle(uint16_t *RAM, uint16_t X, uint16_t Y, uint16_t R, uint16_t Color, uint8_t mode);


#endif
