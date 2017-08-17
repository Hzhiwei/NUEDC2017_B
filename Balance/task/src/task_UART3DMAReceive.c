#include "task_UART3DMAReceive.h"
#include "OSinclude.h"
#include "Config.h"


VisionReceive_Type VisionReceiveBuffer;


extern uint16_t UARTBuffer[4];			//串口缓存
extern uint32_t FrameCount;				//帧数统计
extern float BallSpeed[2];				//球的速度
extern float BallPostion[2][HisLength];	//历史缓存
extern int dataTick[HisLength];			//缓存对应时间
extern int HisPoint;					//缓存指针，指向最新缓存
extern float BallOffset[2];				//球的偏移
extern uint8_t FindBall;				//1 有球   0 没;

extern int16_t IndexNode[9][2];

extern xQueueHandle UART3IDLE_Handler;
extern xQueueHandle BallControl_Handler;


void task_UART3DMAReceive(void *param)
{
	uint8_t index;
	while(1)
	{
		//等待串口信号量
		xSemaphoreTake(UART3IDLE_Handler, portMAX_DELAY);
		
		HisPoint = (HisPoint + 1) % HisLength;
		BallPostion[0][HisPoint] = VisionReceiveBuffer.ball[0];
		BallPostion[1][HisPoint] = VisionReceiveBuffer.ball[1];
		BallSpeed[0] = (BallPostion[0][HisPoint] - BallPostion[0][(HisPoint + 1) % HisLength]) * 2 / HisLength;
		BallSpeed[1] = (BallPostion[1][HisPoint] - BallPostion[1][(HisPoint + 1) % HisLength]) * 2 / HisLength;
		FindBall = VisionReceiveBuffer.found;
		dataTick[HisPoint] = xTaskGetTickCount();
		
		for(index = 0; index < 9; index++)
		{
			IndexNode[index][0] = VisionReceiveBuffer.index[index][0];
			IndexNode[index][1] = VisionReceiveBuffer.index[index][1];
		}
		
		FrameCount++;
		xSemaphoreGiveFromISR(BallControl_Handler, NULL);
	}
}














