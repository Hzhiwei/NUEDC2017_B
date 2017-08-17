#include "UIDrawRAM.h"
#include "UIConfig.h"

extern ui2 * const VRAM;
extern const uint8_t FontASCII0816[][16];
extern const uint8_t FontASCII1020[][40];
extern const uint8_t FontASCII1224[][48];
extern const uint8_t FontASCII1633[][66];
extern const uint8_t FontASCII2448[][144];
extern const uint8_t FontASCII3264[][256];

#define DRAWPOINT(R,x,y,C)	((R)[(uint16_t)(x)+(uint16_t)(y)*UI_WIDTH]=((uint16_t)C))

/**
  * @brief  �Դ���Ƶ�
  * @param  RAM��ַ
  * @param  x
  * @param  y
  * @param  ��ɫ
  * @retval void
  */
void DrawRAM_Point(uint16_t *RAM, uint16_t x, uint16_t y, uint16_t color)
{
	RAM[x + y * UI_WIDTH] = color;
}


/**
  * @brief  �Դ����ֱ��
  * @param  RAM��ַ
  * @param  ���x
  * @param  ���y
  * @param  �յ�x
  * @param  �յ�y
  * @param  ����ɫ
  * @retval void
  */
void DrawRAM_Line(uint16_t *RAM, int16_t sx, int16_t sy, int16_t ex, int16_t ey, uint16_t color, uint8_t thickness)
{ 
	float delta, b;
	uint32_t i, j, k;
	
	if(sx > ex)
	//����ʹsx<ex
	{
		i = sx;
		sx = ex;
		ex = i;
		i = sy;
		sy = ey;
		ey = i;
	}
	
	if(sy == ey)
	//ˮƽ��
	{
		i = sy * UI_WIDTH + sx;
		for(j = sx; j <= ex; j++)
		{
			for(k = 0; k < thickness; k++)
			{
				RAM[i + k * UI_WIDTH] = color;
			}
			i++;
		}
	}
	else if(sx == ex)
	//��ֱ��
	{
		if(sy < ey)
		{
			i = sy * UI_WIDTH + sx;
			for(j = sy; j <= ey; j++)
			{
				for(k = 0; k < thickness; k++)
				{
					RAM[i + k] = color;
				}
				i += UI_WIDTH;
			}
		}
		else
		{
			i = ey * UI_WIDTH + sx;
			for(j = ey; j <= sy; j++)
			{
				for(k = 0; k < thickness; k++)
				{
					RAM[i + k] = color;
				}
				i += UI_WIDTH;
			}
		}
	}
	else
	//б��
	{
		delta = ((float)(ey - sy)) / (ex - sx);
		b = ey - delta * ex;
		
		if((delta <= 1) && (delta >= -1))
		//xΪȡֵ��
		{
			for(i = sx; i <= ex; i++)
			{
				for(k = 0; k < thickness; k++)
				{
					DRAWPOINT(RAM, i, i * delta + b + k, color);
				}
			}
		}
		else if(delta > 1)
		//yΪȡֵ��
		{
			for(i = sy; i <= ey; i++)
			{
				for(k = 0; k < thickness; k++)
				{
					DRAWPOINT(RAM, (i - b) / delta + k, i, color);
				}
			}
		}
		else
		//yΪȡֵ��
		{
			for(i = ey; i <= sy; i++)
			{
				for(k = 0; k < thickness; k++)
				{
					DRAWPOINT(RAM, (i - b) / delta + k, i, color);
				}
			}
		}
	}
}


/**
  * @brief  �Դ���ƾ���
  * @param  RAM��ַ
  * @param  ���Ͻ�x
  * @param  ���Ͻ�y
  * @param  ���
  * @param  ����
  * @param  �߿���ɫ
  * @param  1 ʵ��		0 ����
  * @retval void
  */
void DrawRAM_Rect(uint16_t *RAM, int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color, uint8_t thickness, uint8_t mode)
{
	uint16_t i, j;
	uint16_t *point;
	
	if(!mode)
	{
		DrawRAM_Line(RAM, x, y, x + w, y, color, thickness);
		DrawRAM_Line(RAM, x, y + h - thickness + 1, x + w, y + h - thickness + 1, color, thickness);
		DrawRAM_Line(RAM, x, y, x, y + h, color, thickness);
		DrawRAM_Line(RAM, x + w, y, x + w, y + h, color, thickness);
	}
	else
	{
		for(i = y; i < y + h; i++)
		{
			point = RAM + i * UI_WIDTH + x;
			for(j = 0; j < w; j++)
			{
				*(point++) = color;
			}
		}
	}
}


/**
  * @brief  �Դ�ָ��λ�û��Ƶ���ASCII�ַ�
  * @param  RAM��ַ
  * @param  x
  * @param  y
  * @param  �ַ�����ַ
  * @param  ��ʾ��С
  * @param  ��ɫ
  * @param  ������ɫ
  * @param  ģʽ 1������͸��	0����͸��
  * @retval void
  */
void DrawRAM_ASCII(uint16_t *RAM, uint16_t x, uint16_t y, char word, FontEnum font, uint16_t color, uint16_t backcolor, uint8_t mode)
{
	uint16_t i, j, k;
	uint16_t *point;
	
	if(mode)
	{
		if(font == Font0816)
		{
			for(i = 0; i < 16; i++)
			{
				point = RAM + (y + i) * UI_WIDTH + x;
				
				for(j = 0; j < 8; j++)
				{
					if((0x80 >> j) & FontASCII0816[word - ' '][i])
					{
						*(point++) = color;
					}
					else
					{
						*(point++) = backcolor;
					}
				}
			}
		}
		else if(font == Font1020)
		{
			for(i = 0; i < 20; i++)
			{
				point = RAM + (y + i) * UI_WIDTH + x;
				
				for(j = 0; j < 8; j++)
				{
					if((0x80 >> j) & FontASCII1020[word - ' '][i * 2])
					{
						*(point++) = color;
					}
					else
					{
						*(point++) = backcolor;
					}
				}
				for(j = 0; j < 2; j++)
				{
					if((0x80 >> j) & FontASCII1020[word - ' '][i * 2 + 1])
					{
						*(point++) = color;
					}
					else
					{
						*(point++) = backcolor;
					}
				}
			}
		}
		else if(font == Font1224)
		{
			for(i = 0; i < 24; i++)
			{
				point = RAM + (y + i) * UI_WIDTH + x;
				
				for(j = 0; j < 8; j++)
				{
					if((0x80 >> j) & FontASCII1224[word - ' '][i * 2])
					{
						*(point++) = color;
					}
					else
					{
						*(point++) = backcolor;
					}
				}
				for(j = 0; j < 4; j++)
				{
					if((0x80 >> j) & FontASCII1224[word - ' '][i * 2 + 1])
					{
						*(point++) = color;
					}
					else
					{
						*(point++) = backcolor;
					}
				}
			}
		}
		else if(font == Font1633)
		{
			for(i = 0; i < 33; i++)
			{
				point = RAM + (y + i) * UI_WIDTH + x;
				
				for(j = 0; j < 8; j++)
				{
					if((0x80 >> j) & FontASCII1633[word - ' '][i * 2])
					{
						*(point++) = color;
					}
					else
					{
						*(point++) = backcolor;
					}
				}
				for(j = 0; j < 8; j++)
				{
					if((0x80 >> j) & FontASCII1633[word - ' '][i * 2 + 1])
					{
						*(point++) = color;
					}
					else
					{
						*(point++) = backcolor;
					}
				}
			}
		}
		else if(font == Font2448)
		{
			for(i = 0; i < 48; i++)
			{
				point = RAM + (y + i) * UI_WIDTH + x;
				
				for(k = 0; k < 3; k++)
				{
					for(j = 0; j < 8; j++)
					{
						if((0x80 >> j) & FontASCII2448[word - ' '][i * 3 + k])
						{
							*(point++) = color;
						}
						else
						{
							*(point++) = backcolor;
						}
					}
				}
			}
		}
		else if(font == Font3264)
		{
			for(i = 0; i < 64; i++)
			{
				point = RAM + (y + i) * UI_WIDTH + x;
				
				for(k = 0; k < 4; k++)
				{
					for(j = 0; j < 8; j++)
					{
						if((0x80 >> j) & FontASCII3264[word - ' '][i * 4 + k])
						{
							*(point++) = color;
						}
						else
						{
							*(point++) = backcolor;
						}
					}
				}
			}
		}
	}
	else
	//����͸��
	{
		if(font == Font0816)
		{
			for(i = 0; i < 16; i++)
			{
				point = RAM + (y + i) * UI_WIDTH + x;
				
				for(j = 0; j < 8; j++)
				{
					if((0x80 >> j) & FontASCII0816[word - ' '][i])
					{
						*point = color;
					}
					point++;
				}
			}
		}
		else if(font == Font1020)
		{
			for(i = 0; i < 20; i++)
			{
				point = RAM + (y + i) * UI_WIDTH + x;
				
				for(j = 0; j < 8; j++)
				{
					if((0x80 >> j) & FontASCII1020[word - ' '][i * 2])
					{
						*point = color;
					}
					point++;
				}
				for(j = 0; j < 2; j++)
				{
					if((0x80 >> j) & FontASCII1020[word - ' '][i * 2 + 1])
					{
						*point = color;
					}
					point++;
				}
			}
		}
		else if(font == Font1224)
		{
			for(i = 0; i < 24; i++)
			{
				point = RAM + (y + i) * UI_WIDTH + x;
				
				for(j = 0; j < 8; j++)
				{
					if((0x80 >> j) & FontASCII1224[word - ' '][i * 2])
					{
						*point = color;
					}
					point++;
				}
				for(j = 0; j < 4; j++)
				{
					if((0x80 >> j) & FontASCII1224[word - ' '][i * 2 + 1])
					{
						*point = color;
					}
					point++;
				}
			}
		}
		else if(font == Font1633)
		{
			for(i = 0; i < 33; i++)
			{
				point = RAM + (y + i) * UI_WIDTH + x;
				
				for(j = 0; j < 8; j++)
				{
					if((0x80 >> j) & FontASCII1633[word - ' '][i * 2])
					{
						*point = color;
					}
					point++;
				}
				for(j = 0; j < 8; j++)
				{
					if((0x80 >> j) & FontASCII1633[word - ' '][i * 2 + 1])
					{
						*point = color;
					}
					point++;
				}
			}
		}
		else if(font == Font2448)
		{
			for(i = 0; i < 48; i++)
			{
				point = RAM + (y + i) * UI_WIDTH + x;
				
				for(k = 0; k < 3; k++)
				{
					for(j = 0; j < 8; j++)
					{
						if((0x80 >> j) & FontASCII2448[word - ' '][i * 3 + k])
						{
							*point = color;
						}
					point++;
					}
				}
			}
		}
		else if(font == Font3264)
		{
			for(i = 0; i < 64; i++)
			{
				point = RAM + (y + i) * UI_WIDTH + x;
				
				for(k = 0; k < 4; k++)
				{
					for(j = 0; j < 8; j++)
					{
						if((0x80 >> j) & FontASCII3264[word - ' '][i * 4 + k])
						{
							*point = color;
						}
						point++;
					}
				}
			}
		}
	}
}


/**
  * @brief  �Դ�ָ��λ�û��Ƶ���ASCII�ַ�
  * @param  RAM��ַ
  * @param  x
  * @param  y
  * @param  �ַ�����ַ
  * @param  ��ʾ��С
  * @param  ��ɫ
  * @param  ������ɫ
  * @param  ģʽ 1������͸��	0����͸��
  * @retval void
  */
void DrawRAM_ASCIIStr(uint16_t *RAM, uint16_t x, uint16_t y, char *word, FontEnum font, uint16_t color, uint16_t backcolor, uint8_t mode)
{
	uint16_t textWidth;
	
	switch(font)
	{
		case Font0816 : textWidth =  8; break;
		case Font1020 : textWidth = 10; break;
		case Font1224 : textWidth = 12; break;
		case Font1633 : textWidth = 16; break;
		case Font2448 : textWidth = 24; break;
		case Font3264 : textWidth = 32; break;
	}
	
	while(*word)
	{
		DrawRAM_ASCII(RAM, x, y, *word, font, color, backcolor, mode);
		x += textWidth;
		word++;
	}
}


/**
  * @brief  �Դ�ָ��λ�û���Բ
  * @param  RAM��ַ
  * @param  Բ��X
  * @param  Բ��Y
  * @param  �뾶
  * @param  ��ɫ
  * @param  ģʽ 1����	0ʵ��
  * @retval void
  */
void DrawRAM_Circle(uint16_t *RAM, uint16_t X, uint16_t Y, uint16_t R, uint16_t Color, uint8_t mode)
{
	int a, b;
	int di;
	a = 0;
	b = R;	  
	di = 3 - (R << 1);             //�ж��¸���λ�õı�־
	while(a <= b)
	{
		DRAWPOINT(RAM, X + a, Y - b, Color);             //5
 		DRAWPOINT(RAM, X + b, Y - a, Color);             //0           
		DRAWPOINT(RAM, X + b, Y + a, Color);             //4               
		DRAWPOINT(RAM, X + a, Y + b, Color);             //6 
		DRAWPOINT(RAM, X - a, Y + b, Color);             //1       
 		DRAWPOINT(RAM, X - b, Y + a, Color);             
		DRAWPOINT(RAM, X - a, Y - b, Color);             //2             
  		DRAWPOINT(RAM, X - b, Y - a, Color);             //7     	         
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)
		{
			di += 4 * a + 6;	
		}			
		else
		{
			di += 10 + 4 * (a - b);   
			b--;
		} 						    
	}
}





