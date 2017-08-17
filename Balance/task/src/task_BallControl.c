#include "task_BallControl.h"
#include "OSinclude.h"
#include "Config.h"
#include "driver_BallControl.h"
#include "task_UART3DMAReceive.h"


uint16_t UARTBuffer[4];				//串口缓存
uint32_t FrameCount = 0;			//帧数统计
float BallSpeed[2];					//球的速度
float BallPostion[2][HisLength];	//历史缓存
int dataTick[HisLength];			//缓存对应时间
int HisPoint;						//缓存指针，指向最新缓存
float BallOffset[2] = {-106,-108};	//球的偏移
uint8_t FindBall = 0;				//1 有球   0 没球


float TargetLoction[2] = {0, 0};

extern xQueueHandle BallControl_Handler;
extern float AngleTarget[2];
extern VisionReceive_Type VisionReceiveBuffer;
extern uint8_t AlignFlag;


/**
  * @brief  球控制任务
  * @param  unused
  * @retval void
  */
void task_BallControl(void *param)
{
	portBASE_TYPE status;
	TickType_t CurrentTick;
	float speedTemp[2];
	uint16_t lostFlag = 0;		//1 确认丢失
	
	while(1)
	{
		vTaskDelayUntil(&CurrentTick, 50);
		CurrentTick = xTaskGetTickCount();
		//数据时间间隔时间过长跳过此次PID
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










