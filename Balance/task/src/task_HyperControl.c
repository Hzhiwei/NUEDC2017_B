#include "task_HyperControl.h"
#include "task_UART1DMAReceive.h"
#include "task_UART3DMAReceive.h"
#include "OSinclude.h"
#include "Config.h"


#define JUDGECOUNTER	4
#define STOPSPEEDLIMIT	5
#define STOPPOSILIMIT	7

#define ADDITONTICK		500;

uint8_t RealMode = 0;

uint8_t AlignFlag = 0;

int16_t PathNode[15][2];		//运动节点序列
uint8_t PathLenght;				//节点数量（除起点外）
uint8_t TargetNode;				//当前目标节点
//9个核心点
int16_t IndexNode[9][2];		//标志圆位置


extern float TargetLoction[2];
extern DownloadData_Type UART1ReceiveBuffer;
extern float BallPostion[2][HisLength];
extern float BallSpeed[2];
extern int HisPoint;

extern VisionReceive_Type VisionReceiveBuffer;
extern DownloadData_Type	UART1ReceiveBuffer;

extern float AngleXOffset;
extern float AngleYOffset;


static uint8_t HyperControl_BallArriveJudge(uint8_t Mode);
static void SetTargetTo(uint8_t Num);


uint8_t ArriveTarget = 0;
void HyperControl_Mode0(uint8_t FristInto);
void HyperControl_Mode1(uint8_t FristInto);
void HyperControl_Mode2(uint8_t FristInto);
void HyperControl_Mode3(uint8_t FristInto, uint32_t Tick);
void HyperControl_Mode4(uint8_t FristInto, uint32_t Tick);
void HyperControl_Mode5(uint8_t FristInto, uint32_t Tick);
void HyperControl_Mode6(uint8_t FristInto, uint32_t Tick);
void HyperControl_Mode7(uint8_t FristInto, uint32_t Tick);
static uint8_t Routing(uint8_t startIndex, uint8_t endIndex, int16_t Point[][2]);




/**
  * @brief  顶层控制任务
  * @param  unused
  * @retval void
  */
void task_HyperControl(void *param)
{
	static uint8_t CurrentReceiveMode = 0, LastReceiveMode = 0;	//模式
	static uint8_t ChangeModeCounter = 0;
	uint8_t fristInt = 0;
	
	while(1)
	{
		CurrentReceiveMode = UART1ReceiveBuffer.mode;
		
		//模式切换(防抖)
		if(CurrentReceiveMode != RealMode)
		{
			if(CurrentReceiveMode == LastReceiveMode)
			{
				ChangeModeCounter++;
			}
			else
			{
				ChangeModeCounter = 0;
			}
			if(ChangeModeCounter > 5)
			{
				RealMode = CurrentReceiveMode;
				fristInt = 1;
			}
			else
			{
				if((fristInt == 1) && (!VisionReceiveBuffer.found))
				{
					fristInt = 1;
				}
				else
				{
					fristInt = 0;
				}
			}
		}
		else
		{
			if((fristInt == 1) && (!VisionReceiveBuffer.found))
			{
				fristInt = 1;
			}
			else
			{
				fristInt = 0;
			}
		}
		LastReceiveMode = CurrentReceiveMode;

		switch(RealMode)
		{
			case 0 : HyperControl_Mode0(fristInt); AlignFlag = 1; break;
			case 1 : HyperControl_Mode1(fristInt); AlignFlag = 0; break;
			case 2 : HyperControl_Mode2(fristInt); AlignFlag = 0; break;
			case 3 : HyperControl_Mode3(fristInt, xTaskGetTickCount()); AlignFlag = 0; break;
			case 4 : HyperControl_Mode4(fristInt, xTaskGetTickCount()); AlignFlag = 0; break;
			case 5 : HyperControl_Mode5(fristInt, xTaskGetTickCount()); AlignFlag = 0; break;
			case 6 : HyperControl_Mode6(fristInt, xTaskGetTickCount()); AlignFlag = 0; break;
			case 7 : HyperControl_Mode7(fristInt, xTaskGetTickCount()); AlignFlag = 0; break;
			default: break;
		}
		

		vTaskDelay(50);
	}
}

/**
  * @brief  判断球是否达到目标位置
  * @param  0 停留		1 精确经过	2 粗略经过
  * @retval 1 是  0 否
  */
uint8_t HyperControl_BallArriveJudge(uint8_t Mode)
{
	static uint8_t counter = 0;
	
	float xError, yError;
	
	xError = BallPostion[0][HisPoint] - TargetLoction[0];
	yError = BallPostion[1][HisPoint] - TargetLoction[1];
	
	if(Mode == 0)
	{
		if((BallSpeed[0] > -STOPSPEEDLIMIT) && (BallSpeed[0] < STOPSPEEDLIMIT)
			&& (BallSpeed[1] > -STOPSPEEDLIMIT) && (BallSpeed[1] < STOPSPEEDLIMIT)
			&& (xError < STOPPOSILIMIT) && (xError > -STOPPOSILIMIT)
			&& (yError < STOPPOSILIMIT) && (yError > -STOPPOSILIMIT))
		{
			counter++;
		}
		else
		{
			counter = 0;
		}
		if(counter > JUDGECOUNTER)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if(Mode == 1)
	{
		if((xError < STOPPOSILIMIT) && (xError > -STOPPOSILIMIT)
			&& (yError < STOPPOSILIMIT) && (yError > -STOPPOSILIMIT))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if(Mode == 2)
	{
		if((xError < STOPPOSILIMIT * 4) && (xError > -STOPPOSILIMIT * 4)
			&& (yError < STOPPOSILIMIT * 4) && (yError > -STOPPOSILIMIT * 4))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}


//模式0
void HyperControl_Mode0(uint8_t FristInto)
{
	static uint8_t lastAlign = 0;
		
	if((lastAlign & 0x08) != (UART1ReceiveBuffer.align & 0x08))
	{
		AngleXOffset += 0.1;
	}
	if((lastAlign & 0x04) != (UART1ReceiveBuffer.align & 0x04))
	{
		AngleXOffset -= 0.1;
	}
	if((lastAlign & 0x02) != (UART1ReceiveBuffer.align & 0x02))
	{
		AngleYOffset += 0.1;
	}
	if((lastAlign & 0x01) != (UART1ReceiveBuffer.align & 0x01))
	{
		AngleYOffset -= 0.1;
	}
	lastAlign = UART1ReceiveBuffer.align;
}


//模式1
void HyperControl_Mode1(uint8_t FristInto)
{
	SetTargetTo(1);
}


//模式2
void HyperControl_Mode2(uint8_t FristInto)
{
	SetTargetTo(4);
}

//模式3
void HyperControl_Mode3(uint8_t FristInto, uint32_t Tick)
{
	static uint32_t leaveTick = 0;
	static uint8_t KeepMove = 0;	//1 运动   0 保持
	
	//由其他模式进入此模式
	if(FristInto)
	{
		leaveTick = 0;
		
		PathNode[0][0] = IndexNode[3][0];
		PathNode[0][1] = IndexNode[3][1];
		PathNode[1][0] = IndexNode[4][0];
		PathNode[1][1] = IndexNode[4][1];
		
		PathLenght = 2;
		TargetNode = 0;
		SetTargetTo(3);
		KeepMove = 1;
	}
	
	if(KeepMove)
	//正在运动
	{
		if(HyperControl_BallArriveJudge(0))
		//到达位置，变为保持
		{
			KeepMove = 0;
			leaveTick = Tick + 2000 + ADDITONTICK;
		}
	}
	else
	{
		if(leaveTick <= Tick)
		//保持时间结束
		{
			if(TargetNode + 1 < PathLenght)
			//路径未结束
			{
				TargetNode++;
				KeepMove = 1;
				TargetLoction[0] = PathNode[TargetNode][0];
				TargetLoction[1] = PathNode[TargetNode][1];
			}
		}
	}
}

//模式4
void HyperControl_Mode4(uint8_t FristInto, uint32_t Tick)
{
	static uint32_t leaveTick = 0;
	static uint8_t KeepMove = 0;	//1 运动   0 保持
	
	//由其他模式进入此模式
	if(FristInto)
	{
		leaveTick = 0;
		
		PathNode[0][0] = (IndexNode[1][0] + IndexNode[4][0]) / 2;
		PathNode[0][1] = (IndexNode[1][1] + IndexNode[4][1]) / 2;
		PathNode[1][0] = (IndexNode[4][0] + IndexNode[5][0]) / 2;
		PathNode[1][1] = (IndexNode[4][1] + IndexNode[5][1]) / 2;
		PathNode[2][0] = IndexNode[8][0];
		PathNode[2][1] = IndexNode[8][1];
		
		TargetLoction[0] = PathNode[0][0];
		TargetLoction[1] = PathNode[0][1];
		
		PathLenght = 3;
		TargetNode = 0;
		KeepMove = 1;
	}
	
	if(KeepMove)
	//正在运动
	{
		if(HyperControl_BallArriveJudge(2))
		//到达位置，变为保持
		{
			KeepMove = 0;
//			if((TargetNode == 0)
//				|| (TargetNode == 1))
//			{
//				leaveTick = Tick + 2000 + ADDITONTICK;
//			}
		}
	}
	else
	{
		if(leaveTick <= Tick)
		//保持时间结束
		{
			if(TargetNode + 1 < PathLenght)
			//路径未结束
			{
				TargetNode++;
				KeepMove = 1;
				TargetLoction[0] = PathNode[TargetNode][0];
				TargetLoction[1] = PathNode[TargetNode][1];
			}
		}
	}
}

//模式5
void HyperControl_Mode5(uint8_t FristInto, uint32_t Tick)
{
	static uint32_t leaveTick = 0;
	static uint8_t KeepMove = 0;	//1 运动   0 保持
	
	//由其他模式进入此模式
	if(FristInto)
	{
		leaveTick = 0;
		
		PathNode[0][0] = IndexNode[1][0];
		PathNode[0][1] = IndexNode[1][1];
		PathNode[1][0] = IndexNode[5][0];
		PathNode[1][1] = IndexNode[5][1];
		PathNode[2][0] = IndexNode[8][0];
		PathNode[2][1] = IndexNode[8][1];
		
		TargetLoction[0] = PathNode[0][0];
		TargetLoction[1] = PathNode[0][1];
		
		PathLenght = 3;
		TargetNode = 0;
		KeepMove = 1;
	}
	
	if(KeepMove)
	//正在运动
	{
		if(HyperControl_BallArriveJudge(1))
		//到达位置，变为保持
		{
			KeepMove = 0;
		}
	}
	else
	{
		if(leaveTick <= Tick)
		//保持时间结束
		{
			if(TargetNode + 1 < PathLenght)
			//路径未结束
			{
				TargetNode++;
				KeepMove = 1;
				TargetLoction[0] = PathNode[TargetNode][0];
				TargetLoction[1] = PathNode[TargetNode][1];
			}
		}
	}
}

//模式6
void HyperControl_Mode6(uint8_t FristInto, uint32_t Tick)
{
	static uint32_t leaveTick = 0;
	static uint8_t KeepMove = 0;	//1 运动   0 保持
	static uint8_t accuracyFlag[20];
	uint8_t nodeNum;
	int16_t nodeBuffer[3][2];
	uint8_t nodePoint = 0;
	uint8_t i;
	
	//由其他模式进入此模式
	if(FristInto)
	{
		leaveTick = 0;
		
		nodePoint = 0;
		
		for(i = 0; i < 3; i++)
		{
			nodeNum = Routing(UART1ReceiveBuffer.fourNode[i] - 1, UART1ReceiveBuffer.fourNode[i + 1] - 1, nodeBuffer);
			
			if(nodeNum == 0)
			{
				PathNode[nodePoint][0] = nodeBuffer[0][0];
				PathNode[nodePoint][1] = nodeBuffer[0][1];
				accuracyFlag[nodePoint] = 1;
				nodePoint++;
			}
			else if(nodeNum == 1)
			{
				PathNode[nodePoint][0] = nodeBuffer[0][0];
				PathNode[nodePoint][1] = nodeBuffer[0][1];
				accuracyFlag[nodePoint] = 0;
				nodePoint++;
				PathNode[nodePoint][0] = nodeBuffer[1][0];
				PathNode[nodePoint][1] = nodeBuffer[1][1];
				accuracyFlag[nodePoint] = 1;
				nodePoint++;
			}
			else if(nodeNum == 2)
			{
				PathNode[nodePoint][0] = nodeBuffer[0][0];
				PathNode[nodePoint][1] = nodeBuffer[0][1];
				accuracyFlag[nodePoint] = 0;
				nodePoint++;
				PathNode[nodePoint][0] = nodeBuffer[1][0];
				PathNode[nodePoint][1] = nodeBuffer[1][1];
				accuracyFlag[nodePoint] = 0;
				nodePoint++;
				PathNode[nodePoint][0] = nodeBuffer[2][0];
				PathNode[nodePoint][1] = nodeBuffer[2][1];
				accuracyFlag[nodePoint] = 1;
				nodePoint++;
			}
		}
		
		TargetLoction[0] = PathNode[0][0];
		TargetLoction[1] = PathNode[0][1];
		
		PathLenght = nodePoint;
		TargetNode = 0;
		KeepMove = 1;
	}
	
	if(KeepMove)
	//正在运动
	{
//		if(accuracyFlag[TargetNode])
//		{
			if(HyperControl_BallArriveJudge(1))
			//到达位置，变为保持
			{
				KeepMove = 0;
			}
//		}
//		else
//		{
//			if(HyperControl_BallArriveJudge(2))
//			//到达位置，变为保持
//			{
//				KeepMove = 0;
//			}
//		}
	}
	else
	{
		if(leaveTick <= Tick)
		//保持时间结束
		{
			if(TargetNode + 1 < PathLenght)
			//路径未结束
			{
				TargetNode++;
				KeepMove = 1;
				TargetLoction[0] = PathNode[TargetNode][0];
				TargetLoction[1] = PathNode[TargetNode][1];
			}
		}
	}
}



//模式7
void HyperControl_Mode7(uint8_t FristInto, uint32_t Tick)
{
	static uint32_t leaveTick = 0;
	static uint8_t KeepMove = 0;	//1 运动   0 保持
	int16_t tempPoint[4][2];
	
	//由其他模式进入此模式
	if(FristInto)
	{
		leaveTick = 0;
		
		tempPoint[0][0] = (IndexNode[1][0] + IndexNode[4][0]) / 2;
		tempPoint[0][1] = (IndexNode[1][1] + IndexNode[4][1]) / 2;
		tempPoint[1][0] = (IndexNode[3][0] + IndexNode[4][0]) / 2;
		tempPoint[1][1] = (IndexNode[3][1] + IndexNode[4][1]) / 2;
		tempPoint[2][0] = (IndexNode[4][0] + IndexNode[7][0]) / 2;
		tempPoint[2][1] = (IndexNode[4][1] + IndexNode[7][1]) / 2;
		tempPoint[3][0] = (IndexNode[4][0] + IndexNode[5][0]) / 2;
		tempPoint[3][1] = (IndexNode[4][1] + IndexNode[5][1]) / 2;
		
		PathNode[0][0] = tempPoint[2][0];
		PathNode[0][1] = tempPoint[2][1];
		PathNode[1][0] = tempPoint[3][0];
		PathNode[1][1] = tempPoint[3][1];
		PathNode[2][0] = tempPoint[0][0];
		PathNode[2][1] = tempPoint[0][1];
		PathNode[3][0] = tempPoint[1][0];
		PathNode[3][1] = tempPoint[1][1];
		PathNode[4][0] = tempPoint[2][0];
		PathNode[4][1] = tempPoint[2][1];
		PathNode[5][0] = tempPoint[3][0];
		PathNode[5][1] = tempPoint[3][1];
		PathNode[6][0] = tempPoint[0][0];
		PathNode[6][1] = tempPoint[0][1];
		PathNode[7][0] = tempPoint[1][0];
		PathNode[7][1] = tempPoint[1][1];
		PathNode[8][0] = tempPoint[2][0];
		PathNode[8][1] = tempPoint[2][1];
		PathNode[9][0] = tempPoint[3][0];
		PathNode[9][1] = tempPoint[3][1];
		PathNode[10][0] = tempPoint[0][0];
		PathNode[10][1] = tempPoint[0][1];
		PathNode[11][0] = tempPoint[1][0];
		PathNode[11][1] = tempPoint[1][1];
		PathNode[12][0] = tempPoint[2][0];
		PathNode[12][1] = tempPoint[2][1];
		PathNode[13][0] = IndexNode[8][0];
		PathNode[13][1] = IndexNode[8][1];
		
		TargetLoction[0] = PathNode[0][0];
		TargetLoction[1] = PathNode[0][1];
		
		PathLenght = 14;
		TargetNode = 0;
		KeepMove = 1;
	}
	
	if(KeepMove)
	//正在运动
	{
		if(HyperControl_BallArriveJudge(2))
		//到达位置，变为保持
		{
			KeepMove = 0;
		}
	}
	else
	{
		if(leaveTick <= Tick)
		//保持时间结束
		{
			if(TargetNode + 1 < PathLenght)
			//路径未结束
			{
				TargetNode++;
				KeepMove = 1;
				TargetLoction[0] = PathNode[TargetNode][0];
				TargetLoction[1] = PathNode[TargetNode][1];
			}
		}
	}
}


//将目标设为某个index
static void SetTargetTo(uint8_t Num)
{
	if((Num > 0) && (Num < 10))
	{
		TargetLoction[0] = IndexNode[Num][0];
		TargetLoction[1] = IndexNode[Num][1];
	}
}


int8_t coord[9][2] =
{
	{0, 0},
	{1, 0},
	{2, 0},
	{0, 1},
	{1, 1},
	{2, 1},
	{0, 2},
	{1, 2},
	{2, 2},
};
//路径规划
static uint8_t Routing(uint8_t startIndex, uint8_t endIndex, int16_t Point[][2])
{
	float fourNode[4][2];
	int8_t start[2], end[2];
	int8_t deltaX, deltaY, absDeltaX, absDeltaY;
	uint8_t nodeNum;
	uint8_t nodeSerial[2];
	uint8_t tempPoint[2][2];
	uint8_t tempIndex[2];
	
	
	//计算坐标
	start[0] = coord[startIndex][0];
	start[1] = coord[startIndex][1];
	end[0] = coord[endIndex][0];
	end[1] = coord[endIndex][1];
	
	//四个过渡节点
	fourNode[0][0] = (IndexNode[1][0] + IndexNode[4][0]) / 2;
	fourNode[0][1] = (IndexNode[1][1] + IndexNode[4][1]) / 2;
	fourNode[1][0] = (IndexNode[3][0] + IndexNode[4][0]) / 2;
	fourNode[1][1] = (IndexNode[3][1] + IndexNode[4][1]) / 2;
	fourNode[2][0] = (IndexNode[4][0] + IndexNode[7][0]) / 2;
	fourNode[2][1] = (IndexNode[4][1] + IndexNode[7][1]) / 2;
	fourNode[3][0] = (IndexNode[4][0] + IndexNode[5][0]) / 2;
	fourNode[3][1] = (IndexNode[4][1] + IndexNode[5][1]) / 2;
	
	deltaX = end[0] - start[0];
	deltaY = end[1] - start[1];
	
	//XY绝对值
	absDeltaX = deltaX > 0 ? deltaX : -deltaX;
	absDeltaY = deltaY > 0 ? deltaY : -deltaY;
	
	if((absDeltaX <= 1) && (absDeltaY <= 1))
	//周围一圈直达
	{
		nodeNum = 0;
	}
	else if(absDeltaX * absDeltaY == 2)
	//XY一个1一个2，直达
	{
//		if((startIndex == 3) && (endIndex == 2))
//		//4->3由于板面不平特殊处理
//		{
//			nodeNum = 2;
//			nodeSerial[0] = 2;
//			nodeSerial[1] = 3;
//		}
//		else
//		{
//			nodeNum = 0;
//		}
		
		if(absDeltaY == 2)
		//Y向
		{
			tempPoint[0][0] = start[0];
			tempPoint[0][1] = (start[1] + end[1]) / 2;
			tempPoint[1][0] = end[0];
			tempPoint[1][1] = (start[1] + end[1]) / 2;
		}
		else
		//X向
		{
			tempPoint[0][0] = (start[0] + end[0]) / 2;
			tempPoint[0][1] = start[1];
			tempPoint[1][0] = (start[0] + end[0]) / 2;
			tempPoint[1][1] = end[1];
		}
		tempIndex[0] = 3 * tempPoint[0][1] + tempPoint[0][0];
		tempIndex[1] = 3 * tempPoint[1][1] + tempPoint[1][0];
		
		if(((tempIndex[0] == 3) && (tempIndex[1] == 4))
			|| ((tempIndex[0] == 4) && (tempIndex[1] == 3)))
		{
			nodeSerial[0] = 1;
		}
		else if(((tempIndex[0] == 1) && (tempIndex[1] == 4))
			|| ((tempIndex[0] == 4) && (tempIndex[1] == 1)))
		{
			nodeSerial[0] = 0;
		}
		else if(((tempIndex[0] == 5) && (tempIndex[1] == 4))
			|| ((tempIndex[0] == 4) && (tempIndex[1] == 5)))
		{
			nodeSerial[0] = 3;
		}
		else if(((tempIndex[0] == 4) && (tempIndex[1] == 7))
			|| ((tempIndex[0] == 7) && (tempIndex[1] == 4)))
		{
			nodeSerial[0] = 2;
		}
		nodeNum = 1;
	}
	else if(absDeltaX == absDeltaY)
	//对角线
	{
		if(startIndex == 0)
		{
			nodeSerial[0] = 0;
			nodeSerial[1] = 3;
		}
		else if(startIndex == 2)
		{
			nodeSerial[0] = 0;
			nodeSerial[1] = 1;
		}
		else if(startIndex == 6)
		{
			nodeSerial[0] = 2;
			nodeSerial[1] = 3;
		}
		else if(startIndex == 8)
		{
			nodeSerial[0] = 2;
			nodeSerial[1] = 1;
		}
		nodeNum = 2;
	}
	else
	//中线
	{
		if(absDeltaX == 2)
		//沿X轴
		{
			if((startIndex == 0)
				|| (startIndex == 2)
				|| (startIndex == 3)
				|| (startIndex == 5))
			{
				nodeSerial[0] = 0;
			}
			else
			{
				nodeSerial[0] = 2;
			}
		}
		else
		//沿Y轴
		{
			if((startIndex == 0)
				|| (startIndex == 1)
				|| (startIndex == 6)
				|| (startIndex == 7))
			{
				nodeSerial[0] = 1;
			}
			else
			{
				nodeSerial[0] = 3;
			}
		}
		nodeNum = 1;
	}
	
	if(nodeNum == 0)
	{
		Point[0][0] = IndexNode[endIndex][0];
		Point[0][1] = IndexNode[endIndex][1];
	}
	else if(nodeNum == 1)
	{
		Point[0][0] = fourNode[nodeSerial[0]][0];
		Point[0][1] = fourNode[nodeSerial[0]][1];
		
		Point[1][0] = IndexNode[endIndex][0];
		Point[1][1] = IndexNode[endIndex][1];
	}
	else if(nodeNum == 2)
	{
		Point[0][0] = fourNode[nodeSerial[0]][0];
		Point[0][1] = fourNode[nodeSerial[0]][1];
		
		Point[1][0] = fourNode[nodeSerial[1]][0];
		Point[1][1] = fourNode[nodeSerial[1]][1];
		
		Point[2][0] = IndexNode[endIndex][0];
		Point[2][1] = IndexNode[endIndex][1];
	}
	
	return nodeNum;
}


