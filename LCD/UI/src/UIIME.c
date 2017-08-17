#include "UIIME.h"
#include "UIDrawRAM.h"
#include "UIPage.h"

extern Page_Type *Page;

char IMECharTable[4][4] =
{
	{'1', '2', '3', 'E'},
	{'4', '5', '6', '<'},
	{'7', '8', '9', 'C'},
	{'-', '0', '.', '='},
};


void IMEInitDefault(Control_Type *IME)
{
	IME->backColor = 0xFFF0;
	IME->frontColor = 0xF800;
	IME->frameColor = 0x001F;
	IME->pos.x = 50;
	IME->pos.y = 30;
	IME->size.x = 380;
	IME->size.y = 260;
	
	IME->OnPush = IME_OnPush;
	
	((IMEBody_Type *)(IME->body))->text[0] = '0';
	((IMEBody_Type *)(IME->body))->text[1] = 0;
	((IMEBody_Type *)(IME->body))->textNum = 1;
	((IMEBody_Type *)(IME->body))->textSize = Font2448;
}



//绘制控件
void IME_Draw(ui2 *Buffer, Control_Type *IME)
{
	uint16_t sx, sy, ex, ey;
	int16_t dx, dy;
	uint16_t index;
	uint16_t textWidth, textHeight;
	uint16_t i, j;
	uint8_t indexX, indexY;
	char *charTemp;
	
	//绘制背景色
	DrawRAM_Rect(Buffer, IME->pos.x, IME->pos.y, IME->size.x, IME->size.y, IME->backColor, 1, 1);
	
	//绘制边框
	sx = IME->pos.x;
	sy = IME->pos.y;
	ex = IME->pos.x + IME->size.x;
	ey = IME->pos.y;
	DrawRAM_Line(Buffer, sx, sy, ex, ey, IME->frameColor, 4);
	sy = IME->pos.y + IME->size.y;
	ey = IME->pos.y + IME->size.y;
	DrawRAM_Line(Buffer, sx, sy, ex + 3, ey, IME->frameColor, 4);
	sx = IME->pos.x;
	sy = IME->pos.y;
	ex = IME->pos.x;
	ey = IME->pos.y + IME->size.y;
	DrawRAM_Line(Buffer, sx, sy, ex, ey, IME->frameColor, 4);
	sx = IME->pos.x + IME->size.x;
	ex = IME->pos.x + IME->size.x;
	DrawRAM_Line(Buffer, sx, sy, ex, ey, IME->frameColor, 4);
	
	dx = IME->size.x / 4;
	dy = IME->size.y / 5;
	
	//绘制内部水平格线
	sx = IME->pos.x;
	sy = IME->pos.y + dy;
	ex = IME->pos.x + IME->size.x;
	ey = IME->pos.y + dy;
	for(index = 0; index < 4; index++, sy += dy, ey += dy)
	{
		DrawRAM_Line(Buffer, sx, sy, ex, ey, IME->frameColor, 2);
	}
	
	//绘制内部垂直格线
	switch(((IMEBody_Type *)(IME->body))->textSize)
	{
		case Font0816 : textWidth =  8; textHeight = 16; break;
		case Font1020 : textWidth = 10; textHeight = 20; break;
		case Font1224 : textWidth = 12; textHeight = 24; break;
		case Font1633 : textWidth = 16; textHeight = 33; break;
		case Font2448 : textWidth = 24; textHeight = 48; break;
		case Font3264 : textWidth = 32; textHeight = 64; break;
	}
	
	sx = IME->pos.x + dx;
	sy = IME->pos.y + dy;
	ex = IME->pos.x + dx;
	ey = IME->pos.y + IME->size.y;
	for(index = 0; index < 3; index++, sx += dx, ex += dx)
	{
		DrawRAM_Line(Buffer, sx, sy, ex, ey, IME->frameColor, 2);
	}
	
	//绘制键盘字符
	for(indexY = 0, i = IME->pos.y + dy + (dy - textHeight) / 2; indexY < 4; indexY++, i += dy)
	{
		for(indexX = 0, j = IME->pos.x + (dx - textWidth) / 2; indexX < 4; indexX++, j += dx)
		{
			DrawRAM_ASCII(Buffer, j, i, IMECharTable[indexY][indexX], ((IMEBody_Type *)(IME->body))->textSize, IME->frontColor, 0, 0);
		}
	}
	
	//绘制数据
	//获取数据长度
	DrawRAM_ASCIIStr(Buffer, IME->pos.x + IME->size.x - 5 - textWidth * ((IMEBody_Type *)(IME->body))->textNum, IME->pos.y + (dy - textHeight) / 2, ((IMEBody_Type *)(IME->body))->text, ((IMEBody_Type *)(IME->body))->textSize, IME->frontColor, 0, 0);
}


//IME按下回掉函数
void IME_OnPush(Control_Type *IME, uint8_t Status, uint16_t PosX, uint16_t PosY)
{
	uint16_t oppositeX, oppositeY;
	uint8_t pushX, pushY;
	uint8_t index, flag;
	char *temp;
	uint8_t minuesFlag, floatFlag;
	uint8_t floatBits;
	float Num;
	float exponent;
	
	if(PosX > IME->pos.x)
	{
		oppositeX = PosX - IME->pos.x;
	}
	else
	{
		oppositeX = 0;
	}
	if(PosY > IME->pos.y + IME->size.y / 5)
	{
		oppositeY = PosY - IME->pos.y - IME->size.y / 5;
	}
	else
	//按到显示栏
	{
		return;
	}
	
	pushX = oppositeX / (IME->size.x / 4);
	pushY = oppositeY / (IME->size.y / 5);
	
	switch(IMECharTable[pushY][pushX])
	{
		case '0':
		case '1' :
		case '2' :
		case '3' :
		case '4' :
		case '5' :
		case '6' :
		case '7' :
		case '8' :
		case '9' :
		{
			if(((IMEBody_Type *)(IME->body))->textNum < IMEMAXCHARNUM - 1)
			{
				if((((IMEBody_Type *)(IME->body))->textNum == 1) && (((IMEBody_Type *)(IME->body))->text[0] == '0'))
				//只有一个数,且为0
				{
					((IMEBody_Type *)(IME->body))->text[0] = IMECharTable[pushY][pushX];
				}
				else
				//直接增补
				{
					((IMEBody_Type *)(IME->body))->text[((IMEBody_Type *)(IME->body))->textNum] = IMECharTable[pushY][pushX];
					((IMEBody_Type *)(IME->body))->text[((IMEBody_Type *)(IME->body))->textNum + 1] = 0;
					((IMEBody_Type *)(IME->body))->textNum++;
				}
			}
			break;
		}
		case '-' :
		{
			if(!((((IMEBody_Type *)(IME->body))->textNum == 1) && (((IMEBody_Type *)(IME->body))->text[0] == '0')))
			//非只有一个0
			{
				//负与非负互换
				if(((IMEBody_Type *)(IME->body))->text[0] == '-')
				{
					for(index = 0; index < IMEMAXCHARNUM; index++)
					{
						((IMEBody_Type *)(IME->body))->text[index] = ((IMEBody_Type *)(IME->body))->text[index + 1];
					}
					((IMEBody_Type *)(IME->body))->textNum--;
				}
				else
				{
					for(index = IMEMAXCHARNUM; index > 0; index--)
					{
						((IMEBody_Type *)(IME->body))->text[index] = ((IMEBody_Type *)(IME->body))->text[index - 1];
					}
					((IMEBody_Type *)(IME->body))->textNum++;
					((IMEBody_Type *)(IME->body))->text[0] = '-';
				}
			}
			break;
		}
		case '.' :
		{
			if(((IMEBody_Type *)(IME->body))->textNum < IMEMAXCHARNUM - 1)
			{
				//查找是否存在小数点
				flag = 1;
				for(temp = ((IMEBody_Type *)(IME->body))->text; *temp != 0; temp++)
				{
					if(*temp == '.')
					{
						flag = 0;
						break;
					}
				}
				if(flag)
				//之前没有小数点
				{
					((IMEBody_Type *)(IME->body))->text[((IMEBody_Type *)(IME->body))->textNum] = '.';
					((IMEBody_Type *)(IME->body))->text[((IMEBody_Type *)(IME->body))->textNum + 1] = 0;
					((IMEBody_Type *)(IME->body))->textNum++;
				}
			}
			break;
		}
		case '<' :
		{
			if(((IMEBody_Type *)(IME->body))->textNum == 1)
			//只剩一个字符直接归零
			{
				((IMEBody_Type *)(IME->body))->text[0] = '0';
			}
			else if((((IMEBody_Type *)(IME->body))->textNum == 2) && (((IMEBody_Type *)(IME->body))->text[0] == '-'))
			{
				((IMEBody_Type *)(IME->body))->text[0] = '0';
				((IMEBody_Type *)(IME->body))->text[1] = 0;
				((IMEBody_Type *)(IME->body))->textNum = 1;
			}
			else
			{
				((IMEBody_Type *)(IME->body))->text[--(((IMEBody_Type *)(IME->body))->textNum)] = 0;
			}
			break;
		}
		case 'C' :
		{
			((IMEBody_Type *)(IME->body))->text[0] = '0';
			((IMEBody_Type *)(IME->body))->text[1] = 0;
			((IMEBody_Type *)(IME->body))->textNum = 1;
			break;
		}
		case 'E' :
		{
			Page_DelateControlByID(Page, Page->controlChain.counter);
			if(Page->ExitIME != NULL)
			{
				Page->ExitIME(0, 0);
			}
			Page->IMEmode = 0;
			break;
		}
		case '=' :
		{
			temp = ((IMEBody_Type *)(IME->body))->text;
			//负数标志
			if(((IMEBody_Type *)(IME->body))->text[0] == '-')
			{
				minuesFlag = 1;
				temp++;
			}
			else
			{
				minuesFlag = 0;
			}
			
			floatBits = 0;
			floatFlag = 0;
			Num = 0;
			for(;*temp !=0; temp++)
			{
				if(*temp == '.')
				{
					floatFlag = 1;
				}
				else
				{
					Num = Num * 10 + *temp - '0';
					if(floatFlag)
					{
						floatBits++;
					}
				}
			}
			
			exponent = 1;
			for(index = 0; index < floatBits; index++)
			{
				exponent *= 10;
			}
			
			if(minuesFlag)
			{
				*(Page->IMEdate) = -Num / exponent;
			}
			else
			{
				*(Page->IMEdate) = Num / exponent;
			}
			
			Page_DelateControlByID(Page, Page->controlChain.counter);
			if(Page->ExitIME != NULL)
			{
				Page->ExitIME(1, *(Page->IMEdate));
			}
			Page->IMEmode = 0;
			break;
		}
	}
}



