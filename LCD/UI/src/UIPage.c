#include "UIPage.h"
#include "OSinclude.h"


//新建一个空页面
//param:显存
//返回页面地址 NULL创建失败
Page_Type *Page_New(ui2 *Buffer)
{
	Page_Type *temp = NULL;

	temp = (Page_Type *)pvPortMalloc(sizeof(Page_Type));
	if (temp == NULL)
	{
		return NULL;
	}

	temp->VRAM = Buffer;
	temp->backColor = 0xFFFF;
	temp->IMEmode = 0;
	temp->controlChain.top = NULL;
	temp->controlChain.bottom = NULL;
	temp->controlChain.counter = 0;

	return temp;
}

//在指定页面最上层上增加一个控件
//参数控件类型
//返回控件地址
Control_Type *Page_AddControl(Page_Type *P, Control_Enum CT, PointI_Type L, PointI_Type S)
{
	ControlsChainNode_Type *controlNodeTemp;	//新控件结点
	void *controlBodyTemp;						//新控件Body
	ControlsChainNode_Type *temp;				//临时变量

	//申请结点内存
	controlNodeTemp = (ControlsChainNode_Type *)pvPortMalloc(sizeof(ControlsChainNode_Type));
	if (controlNodeTemp == NULL)
	{
		return NULL;
	}

	//申请控件body内存
#warning 控件种类相关
	switch (CT)
	{
		case Control_Button: 
		{
			controlBodyTemp = (void *)pvPortMalloc(sizeof(ButtonBody_Type));	
			break;
		}
		case Control_IME :
		{
			controlBodyTemp = (void *)pvPortMalloc(sizeof(IMEBody_Type));	
			break;
		}
		case Control_PositionPanel :
		{
			controlBodyTemp = (void *)pvPortMalloc(sizeof(PositionPanelBody_Type));	
			break;
		}
		default:
		{
			controlBodyTemp = NULL;  
			break;
		}
	}
	if (controlBodyTemp == NULL)
	{
		vPortFree(controlNodeTemp);
		return NULL;
	}
	//将body连接上控件结点结构
	controlNodeTemp->control.body = controlBodyTemp;
	//顶层控件的privious必定是BULL
	controlNodeTemp->previous = NULL;
	//设置ID
	controlNodeTemp->ID = P->controlChain.counter + 1;
	//需要刷新
	controlNodeTemp->needFresh = 1;
	//共有初始化
	controlNodeTemp->control.pos.x = L.x;
	controlNodeTemp->control.pos.y = L.y;
	controlNodeTemp->control.size.x = S.x;
	controlNodeTemp->control.size.y = S.y;
	controlNodeTemp->control.type = CT;
	controlNodeTemp->control.visiable = 1;

	//控件初始化
#warning 控件种类相关
	switch (CT)
	{
		case Control_Button : 
		{
			ButtonInitDefault(&(controlNodeTemp->control));
			break;
		}
		case Control_IME:
		{
			IMEInitDefault(&(controlNodeTemp->control));
			break;
		}
		case Control_PositionPanel :
		{
			PositionPanelInitDefault(&(controlNodeTemp->control));
			break;
		}
		default:
			break;
	}

	//控件链表修改
	if (P->controlChain.top == NULL)
	{
		//没有下一个控件
		controlNodeTemp->next = NULL;
		//总节点顶指针与底指针都是新控件
		P->controlChain.top = controlNodeTemp;
		P->controlChain.bottom = controlNodeTemp;
	}//增加前无控件
	else
	{
		//新结点加入修改相关指针
		temp = P->controlChain.top;
		temp->previous = controlNodeTemp;
		controlNodeTemp->next = temp;
		P->controlChain.top = controlNodeTemp;
	}//增加前有控件
	//控件数量加一
	P->controlChain.counter++;

	return &(controlNodeTemp->control);
}


//删除控件 
//param:控件ID
//retval:  0删除成功  1无此控件
ui1 Page_DelateControlByID(Page_Type *P, ui2 ID)
{
	ControlsChainNode_Type *temp[3];
	ui1 controlExistFlag = 0;
	ui1 IDtemp = 0;

	//查找控件
	for (temp[1] = P->controlChain.top; temp[1] != NULL; temp[1] = temp[1]->next)
	{
		if (temp[1]->ID == ID)
		{
			controlExistFlag = 1;
			break;
		}
	}

	//控件不存在
	if (controlExistFlag == 0)
	{
		return 1;
	}

	temp[0] = temp[1]->previous;
	temp[2] = temp[1]->next;

	//重新连接节点
	if (temp[0] == NULL)
	{
		P->controlChain.top = temp[2];
	}
	else
	{
		temp[0]->next = temp[2];
	}
	if (temp[2] == NULL)
	{
		P->controlChain.bottom = temp[0];
	}
	else
	{
		temp[2]->previous = temp[0];
	}

	//释放控件节点
	//控件body内部申请的内存释放
#warning 控件种类相关
	switch (temp[1]->control.type)
	{
		case Control_Button :
		{
			if(((ButtonBody_Type *)(temp[1]->control.body))->text != NULL)
			{
				vPortFree(((ButtonBody_Type *)(temp[1]->control.body))->text);
			}
			break;
		}
		case Control_IME:
		{
			//body内未申请内存，无需释放
			break;
		}
		case Control_PositionPanel:
		{
			//body内未申请内存，无需释放
			break;
		}
		default:
			break;
	}
	vPortFree(temp[1]->control.body);
	vPortFree(temp[1]);

	//控件重新编号
	IDtemp = 1;
	for (temp[1] = P->controlChain.bottom; temp[1] != NULL; temp[1] = temp[1]->previous)
	{
		temp[1]->ID = IDtemp++;
	}

	P->controlChain.counter--;

	return 0;
}


//通过控件节点指针获取控件ID
//返回0说明此控件不在此Page中
ui2 Page_GetControlIDbyPoint(Page_Type *P, ControlsChainNode_Type *C)
{
	ControlsChainNode_Type *temp;

	for (temp = P->controlChain.top; temp != NULL; temp = temp->next)
	{
		if (temp == C)
		{
			return temp->ID;
		}
	}
	return 0;
}


//通过控件ID获取控件节点指针
//返回0说明此控件不在此Page中
ControlsChainNode_Type *Page_GetControlPointbyID(Page_Type *P, ui2 ID)
{
	ControlsChainNode_Type *temp;

	for (temp = P->controlChain.top; temp != NULL; temp = temp->next)
	{
		if (temp->ID == ID)
		{
			return temp;
		}
	}
	return NULL;
}


//刷新显存
void Page_FreshBuffer(Page_Type *P)
{
//	ControlsChainNode_Type *temp[2];
//	PointI_Type center[2];
//	i4 index;
//	ui1 flag;
//	ui1 *freahFlagT2B = (ui1 *)pvPortMalloc(sizeof(P->controlChain.counter));	//存储刷新标志的缓存1
//	ui1 *freahFlagB2T = (ui1 *)pvPortMalloc(sizeof(P->controlChain.counter));	//存储刷新标志的缓存2

//	//记录一遍FreshFlag
//	for (temp[0] = P->controlChain.top; temp[0] != NULL; temp[0] = temp[0]->next)
//	{
//		*freahFlagB2T = temp[0]->needFresh;
//	}

//	//根据覆盖关系找需更新的控件
//	while(1)
//	{
//		//从top到bottom依次判断需刷新的控件
//		for (temp[0] = P->controlChain.top; temp[0] != NULL; temp[0] = temp[0]->next)
//		{
//			//needFresh置位则必须刷新
//			if (temp[0]->needFresh)
//			{
//				continue;
//			}

//			//检测上层所有需刷新控件与当前控件是否有叠加部分并确定当前控件是否需要刷新
//			for (temp[1] = P->controlChain.top; temp[1] > temp[0]; temp[1] = temp[1]->next)
//			{
//				//temp[1]needFresh则判断对当前控件是否有影响
//				if (temp[1]->needFresh)
//				{
//					//求两矩形中心
//					center[0].x = temp[0]->control.pos.x + temp[0]->control.size.x / 2;
//					center[0].y = temp[0]->control.pos.y + temp[0]->control.size.y / 2;
//					center[1].x = temp[1]->control.pos.x + temp[1]->control.size.x / 2;
//					center[1].y = temp[1]->control.pos.y + temp[1]->control.size.y / 2;

//					//判断是否有重叠部分,有则直接置位needFresh并结束此次循环
//					if ((center[0].x <= center[1].x) && (center[0].y <= center[1].y))
//					{
//						if ((temp[0]->control.pos.x + temp[0]->control.size.x > temp[1]->control.pos.x)
//							&& (temp[0]->control.pos.y + temp[0]->control.size.y > temp[1]->control.pos.y))
//						{
//							temp[0]->needFresh = 1;
//							break;
//						}
//					}
//					else if ((center[0].x >= center[1].x) && (center[0].y <= center[1].y))
//					{
//						if ((temp[0]->control.pos.x < temp[1]->control.pos.x + temp[1]->control.size.x)
//							&& (temp[0]->control.pos.y + temp[0]->control.size.y > temp[1]->control.pos.y))
//						{
//							temp[0]->needFresh = 1;
//							break;
//						}
//					}
//					else if ((center[0].x >= center[1].x) && (center[0].y >= center[1].y))
//					{
//						if ((temp[0]->control.pos.x < temp[1]->control.pos.x + temp[1]->control.size.x)
//							&& (temp[0]->control.pos.y < temp[1]->control.pos.y + temp[1]->control.size.y))
//						{
//							temp[0]->needFresh = 1;
//							break;
//						}
//					}
//					else if ((center[0].x <= center[1].x) && (center[0].y >= center[1].y))
//					{
//						if ((temp[0]->control.pos.x + temp[0]->control.size.x > temp[1]->control.pos.x)
//							&& (temp[0]->control.pos.y < temp[1]->control.pos.y + temp[1]->control.size.y))
//						{
//							temp[0]->needFresh = 1;
//							break;
//						}
//					}
//				}
//			}
//		}
//		//记录新FreshFlag序列
//		for (temp[0] = P->controlChain.top; temp[0] != NULL; temp[0] = temp[0]->next)
//		{
//			*freahFlagT2B = temp[0]->needFresh;
//		}
//		//检测是否有新刷新标志
//		flag = 0;
//		for (index = 0; index < P->controlChain.counter; index++)
//		{
//			if (freahFlagT2B[index] != freahFlagB2T[index])
//			{
//				flag = 1;
//				break;
//			}
//		}
//		if (flag == 0)
//		{
//			break;
//		}


//		//从bottom到top依次判断需刷新的控件
//		for (temp[0] = P->controlChain.bottom; temp[0] != NULL; temp[0] = temp[0]->previous)
//		{
//			//needFresh置位则必须刷新
//			if (temp[0]->needFresh)
//			{
//				continue;
//			}

//			//检测上层所有需刷新控件与当前控件是否有叠加部分并确定当前控件是否需要刷新
//			for (temp[1] = P->controlChain.bottom; temp[1] > temp[0]; temp[1] = temp[1]->previous)
//			{
//				//temp[1]needFresh则判断对当前控件是否有影响
//				if (temp[1]->needFresh)
//				{
//					//求两矩形中心
//					center[0].x = temp[0]->control.pos.x + temp[0]->control.size.x / 2;
//					center[0].y = temp[0]->control.pos.y + temp[0]->control.size.y / 2;
//					center[1].x = temp[1]->control.pos.x + temp[1]->control.size.x / 2;
//					center[1].y = temp[1]->control.pos.y + temp[1]->control.size.y / 2;

//					//判断是否有重叠部分,有则直接置位needFresh并结束此次循环
//					if ((center[0].x <= center[1].x) && (center[0].y <= center[1].y))
//					{
//						if ((temp[0]->control.pos.x + temp[0]->control.size.x > temp[1]->control.pos.x)
//							&& (temp[0]->control.pos.y + temp[0]->control.size.y > temp[1]->control.pos.y))
//						{
//							temp[0]->needFresh = 1;
//							break;
//						}
//					}
//					else if ((center[0].x >= center[1].x) && (center[0].y <= center[1].y))
//					{
//						if ((temp[0]->control.pos.x < temp[1]->control.pos.x + temp[1]->control.size.x)
//							&& (temp[0]->control.pos.y + temp[0]->control.size.y > temp[1]->control.pos.y))
//						{
//							temp[0]->needFresh = 1;
//							break;
//						}
//					}
//					else if ((center[0].x >= center[1].x) && (center[0].y >= center[1].y))
//					{
//						if ((temp[0]->control.pos.x < temp[1]->control.pos.x + temp[1]->control.size.x)
//							&& (temp[0]->control.pos.y < temp[1]->control.pos.y + temp[1]->control.size.y))
//						{
//							temp[0]->needFresh = 1;
//							break;
//						}
//					}
//					else if ((center[0].x <= center[1].x) && (center[0].y >= center[1].y))
//					{
//						if ((temp[0]->control.pos.x + temp[0]->control.size.x > temp[1]->control.pos.x)
//							&& (temp[0]->control.pos.y < temp[1]->control.pos.y + temp[1]->control.size.y))
//						{
//							temp[0]->needFresh = 1;
//							break;
//						}
//					}
//				}
//			}
//		}
//		//记录新FreshFlag序列
//		for (temp[0] = P->controlChain.top; temp[0] != NULL; temp[0] = temp[0]->next)
//		{
//			*freahFlagB2T = temp[0]->needFresh;
//		}
//		//检测是否有新刷新标志
//		flag = 0;
//		for (index = 0; index < P->controlChain.counter; index++)
//		{
//			if (freahFlagT2B[index] != freahFlagB2T[index])
//			{
//				flag = 1;
//				break;
//			}
//		}
//		if (flag == 0)
//		{
//			break;
//		}

//	}

//	//更新控件至RAM
//	for (temp[0] = P->controlChain.bottom; temp[0] != NULL; temp[0] = temp[0]->previous)
//	{
//		if (temp[0]->needFresh)
//		{
//			Control_Draw(P->VRAM, &(temp[0]->control));
//		}
//	}
	
	
	ControlsChainNode_Type *temp;
	
	for(uint32_t index = UI_HEIGHT * UI_WIDTH; index > 0; index--)
	{
		(P->VRAM)[index] = P->backColor;
	}
	for (temp = P->controlChain.bottom; temp != NULL; temp = temp->previous)
	{
		if(temp->control.visiable)
		{
			Control_Draw(P->VRAM, &(temp->control));
		}
	}
}


/**
  * @brief  Page被按下函数
  * @param  Page
  * @param  x坐标
  * @param  y坐标
  * @retval void
  */
void Page_OnPush(Page_Type *P, uint16_t X, uint16_t Y)
{
	ControlsChainNode_Type *temp;
	
	if(P->IMEmode)
	{
		if(((P->controlChain.top->control.pos.x < X) && (P->controlChain.top->control.pos.x + P->controlChain.top->control.size.x > X))
			&& ((P->controlChain.top->control.pos.y < Y) && (P->controlChain.top->control.pos.y + P->controlChain.top->control.size.y > Y)))
		{
			if(P->controlChain.top->control.OnPush != NULL)
			{
				(P->controlChain.top->control.OnPush)(&(P->controlChain.top->control), 1, X, Y);
			}
		}
	}
	else
	{
		for (temp = P->controlChain.bottom; temp != NULL; temp = temp->previous)
		{
			if(temp->control.visiable)
			{
				if(((temp->control.pos.x < X) && (temp->control.pos.x + temp->control.size.x > X))
					&& ((temp->control.pos.y < Y) && (temp->control.pos.y + temp->control.size.y > Y)))
				{
					if(temp->control.OnPush != NULL)
					{
						(temp->control.OnPush)(&(temp->control), 1, X, Y);
					}
					break;
				}
			}
		}
	}
}


///**
//  * @brief  Page离开函数
//  * @param  Page
//  * @param  void
//  * @retval void
//  */
//void Page_OnLift(Page_Type *P)
//{
//	ControlsChainNode_Type *temp;
//	
//	for (temp = P->controlChain.bottom; temp != NULL; temp = temp->previous)
//	{
//		if(temp->control.visiable)
//		{
//			if(((temp->control.pos.x < X) && (temp->control.pos.x + temp->control.size.x < X))
//				&& ((temp->control.pos.y < Y) && (temp->control.pos.y + temp->control.size.y < Y)))
//			{
//				if(temp->control.OnPush != NULL)
//				{
//					(temp->control.OnPush)(1, X, Y);
//				}
//			}
//		}
//	}
//}



void Page_GetIMEData(Page_Type *P, float *data, Page_ExitIMECallBack Exit)
{
	PointI_Type L, S;
	L.x = 100;
	L.y = 50;
	S.x = 200;
	S.y = 100;
	
	P->IMEmode = 1;
	P->IMEdate = data;
	P->ExitIME = Exit;
	Page_AddControl(P, Control_IME, L, S);
}









