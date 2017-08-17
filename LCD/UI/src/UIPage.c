#include "UIPage.h"
#include "OSinclude.h"


//�½�һ����ҳ��
//param:�Դ�
//����ҳ���ַ NULL����ʧ��
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

//��ָ��ҳ�����ϲ�������һ���ؼ�
//�����ؼ�����
//���ؿؼ���ַ
Control_Type *Page_AddControl(Page_Type *P, Control_Enum CT, PointI_Type L, PointI_Type S)
{
	ControlsChainNode_Type *controlNodeTemp;	//�¿ؼ����
	void *controlBodyTemp;						//�¿ؼ�Body
	ControlsChainNode_Type *temp;				//��ʱ����

	//�������ڴ�
	controlNodeTemp = (ControlsChainNode_Type *)pvPortMalloc(sizeof(ControlsChainNode_Type));
	if (controlNodeTemp == NULL)
	{
		return NULL;
	}

	//����ؼ�body�ڴ�
#warning �ؼ��������
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
	//��body�����Ͽؼ����ṹ
	controlNodeTemp->control.body = controlBodyTemp;
	//����ؼ���privious�ض���BULL
	controlNodeTemp->previous = NULL;
	//����ID
	controlNodeTemp->ID = P->controlChain.counter + 1;
	//��Ҫˢ��
	controlNodeTemp->needFresh = 1;
	//���г�ʼ��
	controlNodeTemp->control.pos.x = L.x;
	controlNodeTemp->control.pos.y = L.y;
	controlNodeTemp->control.size.x = S.x;
	controlNodeTemp->control.size.y = S.y;
	controlNodeTemp->control.type = CT;
	controlNodeTemp->control.visiable = 1;

	//�ؼ���ʼ��
#warning �ؼ��������
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

	//�ؼ������޸�
	if (P->controlChain.top == NULL)
	{
		//û����һ���ؼ�
		controlNodeTemp->next = NULL;
		//�ܽڵ㶥ָ�����ָ�붼���¿ؼ�
		P->controlChain.top = controlNodeTemp;
		P->controlChain.bottom = controlNodeTemp;
	}//����ǰ�޿ؼ�
	else
	{
		//�½������޸����ָ��
		temp = P->controlChain.top;
		temp->previous = controlNodeTemp;
		controlNodeTemp->next = temp;
		P->controlChain.top = controlNodeTemp;
	}//����ǰ�пؼ�
	//�ؼ�������һ
	P->controlChain.counter++;

	return &(controlNodeTemp->control);
}


//ɾ���ؼ� 
//param:�ؼ�ID
//retval:  0ɾ���ɹ�  1�޴˿ؼ�
ui1 Page_DelateControlByID(Page_Type *P, ui2 ID)
{
	ControlsChainNode_Type *temp[3];
	ui1 controlExistFlag = 0;
	ui1 IDtemp = 0;

	//���ҿؼ�
	for (temp[1] = P->controlChain.top; temp[1] != NULL; temp[1] = temp[1]->next)
	{
		if (temp[1]->ID == ID)
		{
			controlExistFlag = 1;
			break;
		}
	}

	//�ؼ�������
	if (controlExistFlag == 0)
	{
		return 1;
	}

	temp[0] = temp[1]->previous;
	temp[2] = temp[1]->next;

	//�������ӽڵ�
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

	//�ͷſؼ��ڵ�
	//�ؼ�body�ڲ�������ڴ��ͷ�
#warning �ؼ��������
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
			//body��δ�����ڴ棬�����ͷ�
			break;
		}
		case Control_PositionPanel:
		{
			//body��δ�����ڴ棬�����ͷ�
			break;
		}
		default:
			break;
	}
	vPortFree(temp[1]->control.body);
	vPortFree(temp[1]);

	//�ؼ����±��
	IDtemp = 1;
	for (temp[1] = P->controlChain.bottom; temp[1] != NULL; temp[1] = temp[1]->previous)
	{
		temp[1]->ID = IDtemp++;
	}

	P->controlChain.counter--;

	return 0;
}


//ͨ���ؼ��ڵ�ָ���ȡ�ؼ�ID
//����0˵���˿ؼ����ڴ�Page��
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


//ͨ���ؼ�ID��ȡ�ؼ��ڵ�ָ��
//����0˵���˿ؼ����ڴ�Page��
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


//ˢ���Դ�
void Page_FreshBuffer(Page_Type *P)
{
//	ControlsChainNode_Type *temp[2];
//	PointI_Type center[2];
//	i4 index;
//	ui1 flag;
//	ui1 *freahFlagT2B = (ui1 *)pvPortMalloc(sizeof(P->controlChain.counter));	//�洢ˢ�±�־�Ļ���1
//	ui1 *freahFlagB2T = (ui1 *)pvPortMalloc(sizeof(P->controlChain.counter));	//�洢ˢ�±�־�Ļ���2

//	//��¼һ��FreshFlag
//	for (temp[0] = P->controlChain.top; temp[0] != NULL; temp[0] = temp[0]->next)
//	{
//		*freahFlagB2T = temp[0]->needFresh;
//	}

//	//���ݸ��ǹ�ϵ������µĿؼ�
//	while(1)
//	{
//		//��top��bottom�����ж���ˢ�µĿؼ�
//		for (temp[0] = P->controlChain.top; temp[0] != NULL; temp[0] = temp[0]->next)
//		{
//			//needFresh��λ�����ˢ��
//			if (temp[0]->needFresh)
//			{
//				continue;
//			}

//			//����ϲ�������ˢ�¿ؼ��뵱ǰ�ؼ��Ƿ��е��Ӳ��ֲ�ȷ����ǰ�ؼ��Ƿ���Ҫˢ��
//			for (temp[1] = P->controlChain.top; temp[1] > temp[0]; temp[1] = temp[1]->next)
//			{
//				//temp[1]needFresh���ж϶Ե�ǰ�ؼ��Ƿ���Ӱ��
//				if (temp[1]->needFresh)
//				{
//					//������������
//					center[0].x = temp[0]->control.pos.x + temp[0]->control.size.x / 2;
//					center[0].y = temp[0]->control.pos.y + temp[0]->control.size.y / 2;
//					center[1].x = temp[1]->control.pos.x + temp[1]->control.size.x / 2;
//					center[1].y = temp[1]->control.pos.y + temp[1]->control.size.y / 2;

//					//�ж��Ƿ����ص�����,����ֱ����λneedFresh�������˴�ѭ��
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
//		//��¼��FreshFlag����
//		for (temp[0] = P->controlChain.top; temp[0] != NULL; temp[0] = temp[0]->next)
//		{
//			*freahFlagT2B = temp[0]->needFresh;
//		}
//		//����Ƿ�����ˢ�±�־
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


//		//��bottom��top�����ж���ˢ�µĿؼ�
//		for (temp[0] = P->controlChain.bottom; temp[0] != NULL; temp[0] = temp[0]->previous)
//		{
//			//needFresh��λ�����ˢ��
//			if (temp[0]->needFresh)
//			{
//				continue;
//			}

//			//����ϲ�������ˢ�¿ؼ��뵱ǰ�ؼ��Ƿ��е��Ӳ��ֲ�ȷ����ǰ�ؼ��Ƿ���Ҫˢ��
//			for (temp[1] = P->controlChain.bottom; temp[1] > temp[0]; temp[1] = temp[1]->previous)
//			{
//				//temp[1]needFresh���ж϶Ե�ǰ�ؼ��Ƿ���Ӱ��
//				if (temp[1]->needFresh)
//				{
//					//������������
//					center[0].x = temp[0]->control.pos.x + temp[0]->control.size.x / 2;
//					center[0].y = temp[0]->control.pos.y + temp[0]->control.size.y / 2;
//					center[1].x = temp[1]->control.pos.x + temp[1]->control.size.x / 2;
//					center[1].y = temp[1]->control.pos.y + temp[1]->control.size.y / 2;

//					//�ж��Ƿ����ص�����,����ֱ����λneedFresh�������˴�ѭ��
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
//		//��¼��FreshFlag����
//		for (temp[0] = P->controlChain.top; temp[0] != NULL; temp[0] = temp[0]->next)
//		{
//			*freahFlagB2T = temp[0]->needFresh;
//		}
//		//����Ƿ�����ˢ�±�־
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

//	//���¿ؼ���RAM
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
  * @brief  Page�����º���
  * @param  Page
  * @param  x����
  * @param  y����
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
//  * @brief  Page�뿪����
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









