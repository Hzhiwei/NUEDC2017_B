#include "UIControl.h"
#include "UIButton.h"
#include "UIPositioningPanel.h"
#include "UIIME.h"


//绘制控件
void Control_Draw(ui2 *Buffer, Control_Type *C)
{
	//根据控件调用相应绘制函数
#warning 控件种类相关
	switch (C->type)
	{
		case Control_Button : 
		{
			Button_Draw(Buffer, C);
			break;
		}
		case Control_IME :
		{
			IME_Draw(Buffer, C);
			break;
		}
		case Control_PositionPanel :
		{
			PositionPanel_Draw(Buffer, C);
			break;
		}
	}
}






