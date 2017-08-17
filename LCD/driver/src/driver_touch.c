#include "driver_touch.h"


static void Touch_Delay(uint16_t delay);
static void Touch_SendByte(uint8_t data);
static void Touch_GetADC(uint16_t *X, uint16_t *Y);


uint16_t TouchX, TouchY;

static float TouchVar[2][2] = {{-0.12903, 503.8797}, {0.0875, -15}};


/**
  * @brief  触摸屏初始化
  * @param  void
  * @retval void
  */
void Touch_InitConfig(void)
{
	
}


/**
  * @brief  触摸屏初始化
  * @param  void
  * @retval void
  */
void Touch_GetPos(uint16_t *X, uint16_t *Y)
{
	uint16_t tempX, tempY;
	Touch_ReadXY(&tempX, &tempY);
	TouchX = TouchVar[0][0] * tempX + TouchVar[0][1];
	TouchY = TouchVar[1][0] * tempY + TouchVar[1][1];
	*X = TouchX;
	*Y = TouchY;
}


#define READ_TIMES 5 	//读取次数
#define LOST_VAL 1	  	//丢弃值
uint8_t Touch_ReadXY(uint16_t *X, uint16_t *Y)
{
	uint16_t i, j, k;
	uint16_t buf[READ_TIMES][2];
	uint16_t sum=0;
	uint16_t temp;
	
	for(i = 0; i < READ_TIMES; i++)
	{
		Touch_GetADC(&(buf[i][0]), &(buf[i][1]));
	}		
	for(i = 0 ;i < READ_TIMES - 1; i++)//排序
	{
		for(k = 0; k < 2; k++)
		{
			for(j = i + 1; j < READ_TIMES; j++)
			{
				if(buf[i][k] > buf[j][k])//升序排列
				{
					temp = buf[i][k];
					buf[i][k] = buf[j][k];
					buf[j][k] = temp;
				}
			}
		}
	}

	sum = 0;
	for(i = LOST_VAL ;i < READ_TIMES - LOST_VAL; i++)
	{
		sum += buf[i][0];
	}
	*X = sum / (READ_TIMES - 2 * LOST_VAL);

	sum = 0;
	for(i = LOST_VAL ;i < READ_TIMES - LOST_VAL; i++)
	{
		sum += buf[i][1];
	}
	*Y = sum / (READ_TIMES - 2 * LOST_VAL);
} 


/**
  * @brief  读取一次XY ADC
  * @param  X存储地址
  * @param  Y存储地址
  * @retval void
  */
static void Touch_GetADC(uint16_t *X, uint16_t *Y)
{
	uint8_t count = 0; 	  
	uint16_t Num = 0; 
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
	GPIO_ResetBits(GPIOF, GPIO_Pin_11);
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);
	Touch_SendByte(0x90);
	Touch_Delay(60);
	GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
	Touch_Delay(10);
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	Touch_Delay(10);
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);      	    
	for(count = 0; count < 16; count++)
	{ 				  
		Num <<= 1; 	 
		GPIO_ResetBits(GPIOB, GPIO_Pin_0);
		Touch_Delay(10);
		GPIO_SetBits(GPIOB, GPIO_Pin_0); 
 		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2))
		{
			Num++;
		}
	}  	
	Num >>= 4;
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
	*X = Num;

	GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
	GPIO_ResetBits(GPIOF, GPIO_Pin_11);
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);
	Touch_SendByte(0xD0);
	Touch_Delay(60);
	GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
	Touch_Delay(10);
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	Touch_Delay(10);
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);      	    
	for(count=0;count<16;count++)
	{ 				  
		Num <<= 1; 	 
		GPIO_ResetBits(GPIOB, GPIO_Pin_0);
		Touch_Delay(10);
		GPIO_SetBits(GPIOB, GPIO_Pin_0); 
 		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2))
		{
			Num++;
		}			
	}  	
	Num >>= 4;
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
	*Y = Num;
}


/**
  * @brief  发送一次数据
  * @param  要发送的数据
  * @retval void
  */
static void Touch_SendByte(uint8_t data)
{
	uint8_t count = 0;   
	for(count = 0; count < 8; count++)  
	{ 	  
		if(data & 0x80)
		{
			GPIO_SetBits(GPIOF, GPIO_Pin_11);
		}			
		else
		{
			GPIO_ResetBits(GPIOF, GPIO_Pin_11);
		}			
		data <<= 1;    
		GPIO_ResetBits(GPIOB, GPIO_Pin_0); 
		Touch_Delay(10);
		GPIO_SetBits(GPIOB, GPIO_Pin_0);       
	}
}


/**
  * @brief  延时
  * @param  时常
  * @retval void
  */
static void Touch_Delay(uint16_t delay)
{
	delay *= 100;
	while(delay--);
}

