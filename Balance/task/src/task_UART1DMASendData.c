#include "task_UART1DMASendData.h"
#include "BSP_DMA.h"
#include "OSinclude.h"
#include "Config.h"


#define SENDDATAPERIOD	50

extern float BallSpeed[2];				//����ٶ�
extern float BallPostion[2][HisLength];	//��ʷ����
extern int HisPoint;					//����ָ�룬ָ�����»���
extern uint8_t FindBall;				//1 ����   0 û;

extern uint8_t RealMode;


//�������ݷ��ͻ���
UploadData_Type	UART1SendBuffer;


/**
  * @brief  �����Է��Ϳ�������
  * @param  unused
  * @retval void
  */
void task_UART1DMASendData(void *param)
{
	while(1)
	{
		UART1SendBuffer.Loc[0] = BallPostion[0][HisPoint];
		UART1SendBuffer.Loc[1] = BallPostion[1][HisPoint];
		UART1SendBuffer.Speed[0] = BallSpeed[0];
		UART1SendBuffer.Speed[1] = BallSpeed[1];
		UART1SendBuffer.found = FindBall;
		UART1SendBuffer.currentMode = RealMode;
		
		UART1_DMASend((uint8_t *)(&UART1SendBuffer), sizeof(UploadData_Type));
		
		vTaskDelay(SENDDATAPERIOD);
	}
}










