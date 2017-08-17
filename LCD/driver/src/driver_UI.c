#include "driver_UI.h"
#include "driver_LCD5310.h"
#include "UIPage.h"
#include "UI.h"
#include "UICallback.h"

#include "UIDrawRAM.h"


Page_Type *Page;
Control_Type *PageControl[20];

extern ui2 *VRAM;


/**
  * @brief  UI初始化
  * @param  void
  * @retval void
  */
void UI_InitConfig(void)
{
	uint16_t *temp = VRAM;
	uint32_t index;
	Control_Type *C;
	PointI_Type L, S;
	
	UI_Init();
	Page = Page_New(VRAM);
	for(index = UI_HEIGHT * UI_WIDTH; index > 0; index--)
	{
		*(temp++) = 0xFFFF;
	}
	
	//界面控件新建
	/*	实际坐标	*/
	//X标签
	L.x = 25;
	L.y = 0;
	S.x = 25;
	S.y = 30;
	PageControl[0] = Page_AddControl(Page, Control_Button, L, S);
	Button_SetText(PageControl[0], "X:");
	Button_SetFont(PageControl[0], Font1224);
	((ButtonBody_Type*)(PageControl[0]->body))->withFrame = 0;
	PageControl[0]->frontColor = 0xF800;
	
	//X参数
	L.x = 50;
	L.y = 0;
	S.x = 70;
	S.y = 30;
	PageControl[1] = Page_AddControl(Page, Control_Button, L, S);
	Button_SetText(PageControl[1], "-");
	Button_SetFont(PageControl[1], Font1224);
	((ButtonBody_Type*)(PageControl[1]->body))->withFrame = 0;
	PageControl[1]->frontColor = 0x0000;
	
	//Y标签
	L.x = 25;
	L.y = 27;
	S.x = 25;
	S.y = 30;
	PageControl[2] = Page_AddControl(Page, Control_Button, L, S);
	Button_SetText(PageControl[2], "Y:");
	Button_SetFont(PageControl[2], Font1224);
	((ButtonBody_Type*)(PageControl[2]->body))->withFrame = 0;
	PageControl[2]->frontColor = 0xF800;
	
	//Y参数
	L.x = 50;
	L.y = 27;
	S.x = 70;
	S.y = 30;
	PageControl[3] = Page_AddControl(Page, Control_Button, L, S);
	Button_SetText(PageControl[3], "-");
	Button_SetFont(PageControl[3], Font1224);
	((ButtonBody_Type*)(PageControl[3]->body))->withFrame = 0;
	PageControl[3]->frontColor = 0x0000;
	
	
	/*	设定四个点	*/
	//A标签
	L.x = 25;
	L.y = 85;
	S.x = 30;
	S.y = 55;
	PageControl[4] = Page_AddControl(Page, Control_Button, L, S);
	Button_SetText(PageControl[4], "A:");
	Button_SetFont(PageControl[4], Font2448);
	((ButtonBody_Type*)(PageControl[4]->body))->withFrame = 0;
	PageControl[4]->frontColor = 0xB9FF;
	
	//A参数
	L.x = 75;
	L.y = 85;
	S.x = 30;
	S.y = 55;
	PageControl[5] = Page_AddControl(Page, Control_Button, L, S);
	Button_SetText(PageControl[5], "1");
	Button_SetFont(PageControl[5], Font2448);
	((ButtonBody_Type*)(PageControl[5]->body))->withFrame = 0;
	PageControl[5]->frontColor = 0x0000;
	PageControl[5]->OnPush = SetACallBack;
	
	//B标签
	L.x = 25;
	L.y = 130;
	S.x = 30;
	S.y = 55;
	PageControl[6] = Page_AddControl(Page, Control_Button, L, S);
	Button_SetText(PageControl[6], "B:");
	Button_SetFont(PageControl[6], Font2448);
	((ButtonBody_Type*)(PageControl[6]->body))->withFrame = 0;
	PageControl[6]->frontColor = 0xB9FF;
	
	//B参数
	L.x = 75;
	L.y = 130;
	S.x = 30;
	S.y = 55;
	PageControl[7] = Page_AddControl(Page, Control_Button, L, S);
	Button_SetText(PageControl[7], "2");
	Button_SetFont(PageControl[7], Font2448);
	((ButtonBody_Type*)(PageControl[7]->body))->withFrame = 0;
	PageControl[7]->frontColor = 0x0000;
	PageControl[7]->OnPush = SetBCallBack;
	
	//C标签
	L.x = 25;
	L.y = 175;
	S.x = 30;
	S.y = 55;
	PageControl[8] = Page_AddControl(Page, Control_Button, L, S);
	Button_SetText(PageControl[8], "C:");
	Button_SetFont(PageControl[8], Font2448);
	((ButtonBody_Type*)(PageControl[8]->body))->withFrame = 0;
	PageControl[8]->frontColor = 0xB9FF;
	
	//C参数
	L.x = 75;
	L.y = 175;
	S.x = 30;
	S.y = 55;
	PageControl[9] = Page_AddControl(Page, Control_Button, L, S);
	Button_SetText(PageControl[9], "3");
	Button_SetFont(PageControl[9], Font2448);
	((ButtonBody_Type*)(PageControl[9]->body))->withFrame = 0;
	PageControl[9]->frontColor = 0x0000;
	PageControl[9]->OnPush = SetCCallBack;
	
	//D标签
	L.x = 25;
	L.y = 220;
	S.x = 30;
	S.y = 55;
	PageControl[10] = Page_AddControl(Page, Control_Button, L, S);
	Button_SetText(PageControl[10], "D:");
	Button_SetFont(PageControl[10], Font2448);
	((ButtonBody_Type*)(PageControl[10]->body))->withFrame = 0;
	PageControl[10]->frontColor = 0xB9FF;
	
	//D参数
	L.x = 75;
	L.y = 220;
	S.x = 30;
	S.y = 55;
	PageControl[11] = Page_AddControl(Page, Control_Button, L, S);
	Button_SetText(PageControl[11], "4");
	Button_SetFont(PageControl[11], Font2448);
	((ButtonBody_Type*)(PageControl[11]->body))->withFrame = 0;
	PageControl[11]->frontColor = 0x0000;
	PageControl[11]->OnPush = SetDCallBack;
	
	//设置按钮
	L.x = 25;
	L.y = 270;
	S.x = 80;
	S.y = 40;
	PageControl[12] = Page_AddControl(Page, Control_Button, L, S);
	Button_SetText(PageControl[12], "Set");
	Button_SetFont(PageControl[12], Font1633);
	((ButtonBody_Type*)(PageControl[12]->body))->withFrame = 1;
	PageControl[12]->backColor = 0xFEA0;
	PageControl[12]->frontColor = 0x7760;
	PageControl[12]->OnPush = ConfirmCallBack;
	
	//模式按钮
	L.x = 25;
	L.y = 58;
	S.x = 90;
	S.y = 32;
	PageControl[13] = Page_AddControl(Page, Control_Button, L, S);
	Button_SetText(PageControl[13], "0");
	Button_SetFont(PageControl[13], Font1633);
	((ButtonBody_Type*)(PageControl[13]->body))->withFrame = 1;
	PageControl[13]->backColor = 0xFEA0;
	PageControl[13]->frontColor = 0x8A20;
	PageControl[13]->OnPush = SetModeCallBack;
	
	//位置图
	L.x = 165;
	L.y = 10;
	S.x = 250;
	S.y = 250;
	PageControl[14] = Page_AddControl(Page, Control_PositionPanel, L, S);
	
	//当前模式
	L.x = 115;
	L.y = 5;
	S.x = 30;
	S.y = 50;
	PageControl[15] = Page_AddControl(Page, Control_Button, L, S);
	Button_SetText(PageControl[15], "0");
	Button_SetFont(PageControl[15], Font2448);
	((ButtonBody_Type*)(PageControl[15]->body))->withFrame = 0;
	PageControl[15]->frontColor = 0x07E0;
	
	//X-校准
	L.x = 430;
	L.y = 40;
	S.x = 40;
	S.y = 60;
	PageControl[16] = Page_AddControl(Page, Control_Button, L, S);
	Button_SetText(PageControl[16], "-");
	Button_SetFont(PageControl[16], Font1633);
	((ButtonBody_Type*)(PageControl[16]->body))->withFrame = 1;
	PageControl[16]->backColor = 0xFEA0;
	PageControl[16]->frontColor = 0x8A20;
	PageControl[16]->OnPush = XMinusAlignCallBack;
	
	//X+校准
	L.x = 430;
	L.y = 170;
	S.x = 40;
	S.y = 60;
	PageControl[17] = Page_AddControl(Page, Control_Button, L, S);
	Button_SetText(PageControl[17], "+");
	Button_SetFont(PageControl[17], Font1633);
	((ButtonBody_Type*)(PageControl[17]->body))->withFrame = 1;
	PageControl[17]->backColor = 0xFEA0;
	PageControl[17]->frontColor = 0x8A20;
	PageControl[17]->OnPush = XPlusAlignCallBack;
	
	//Y-校准
	L.x = 200;
	L.y = 270;
	S.x = 60;
	S.y = 40;
	PageControl[16] = Page_AddControl(Page, Control_Button, L, S);
	Button_SetText(PageControl[16], "-");
	Button_SetFont(PageControl[16], Font1633);
	((ButtonBody_Type*)(PageControl[16]->body))->withFrame = 1;
	PageControl[16]->backColor = 0xFEA0;
	PageControl[16]->frontColor = 0x8A20;
	PageControl[16]->OnPush = YMinusAlignCallBack;
	
	//Y+校准
	L.x = 330;
	L.y = 270;
	S.x = 60;
	S.y = 40;
	PageControl[17] = Page_AddControl(Page, Control_Button, L, S);
	Button_SetText(PageControl[17], "+");
	Button_SetFont(PageControl[17], Font1633);
	((ButtonBody_Type*)(PageControl[17]->body))->withFrame = 1;
	PageControl[17]->backColor = 0xFEA0;
	PageControl[17]->frontColor = 0x8A20;
	PageControl[17]->OnPush = YPlusAlignCallBack;
	
	//计时器
	L.x = 115;
	L.y = 275;
	S.x = 70;
	S.y = 40;
	PageControl[18] = Page_AddControl(Page, Control_Button, L, S);
	Button_SetText(PageControl[18], "0");
	Button_SetFont(PageControl[18], Font1633);
	((ButtonBody_Type*)(PageControl[18]->body))->withFrame = 0;
	PageControl[18]->backColor = 0xFFFF;
	PageControl[18]->frontColor = 0x0000;
	PageControl[18]->OnPush = NULL;
}


/**
  * @brief  刷新显存至LCD
  * @param  void
  * @retval void
  */
void UI_Refresh(void)
{
	LCD_Fill(0, 0, LCD_WIDTH, LCD_HEIGHT, VRAM);
}


