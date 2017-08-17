#include "task_BallControl.h"
#include "OSinclude.h"
#include "Config.h"
#include "driver_BallControl.h"
#include "task_UART3DMAReceive.h"


uint16_t UARTBuffer[4];				//���ڻ���
uint32_t FrameCount = 0;			//֡��ͳ��
float BallSpeed[2];					//����ٶ�
float BallPostion[2][HisLength];	//��ʷ����
int dataTick[HisLength];			//�����Ӧʱ��
int HisPoint;						//����ָ�룬ָ�����»���
float BallOffset[2] = {-106,-108};	//���ƫ��
uint8_t FindBall = 0;				//1 ����   0 û��


float TargetLoction[2] = {0, 0};

extern xQueueHandle BallControl_Handler;
extern float AngleTarget[2];
extern VisionReceive_Type VisionReceiveBuffer;
extern uint8_t AlignFlag;


/**
  * @brief  ���������
  * @param  unused
  * @retval void
  */
void task_BallControl(void *param)
{
	portBASE_TYPE status;
	TickType_t CurrentTick;
	float speedTemp[2];
	uint16_t lostFlag = 0;		//1 ȷ�϶�ʧ
	
	while(1)
	{
		vTaskDelayUntil(&CurrentTick, 50);
		CurrentTick = xTaskGetTickCount();
		//����ʱ����ʱ����������˴�PID
		if(CurrentTick - dataTick[HisPoint] > 60 * HisLength)
		{
			AngleTarget[0] = 0;
			AngleTarget[1] = 0;
			Ball_ClearInt();
			continue;
		}
		
		if(!VisionReceiveBuffer.found)
		{
			if(lostFlag < 200)
			{
				lostFlag++;
			}
		}
		else
		{
			lostFlag = 0;
		}
		
		if(lostFlag > 5)
		{
			AngleTarget[0] = 0;
			AngleTarget[1] = 0;
			Ball_ClearInt();
			continue;
		}
		
		if(AlignFlag)
		{
			AngleTarget[0] = 0;
			AngleTarget[1] = 0;
		}
		else
		{
			Ball_LocPID(TargetLoction, speedTemp);
			AngleTarget[0] = speedTemp[0];
			AngleTarget[1] = speedTemp[1];
		}
	}
}










