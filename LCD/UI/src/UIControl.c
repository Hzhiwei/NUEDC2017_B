#include "UIControl.h"
#include "UIButton.h"
#include "UIPositioningPanel.h"
#include "UIIME.h"


//���ƿؼ�
void Control_Draw(ui2 *Buffer, Control_Type *C)
{
	//���ݿؼ�������Ӧ���ƺ���
#warning �ؼ��������
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






