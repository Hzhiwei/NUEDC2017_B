#include "driver_SRAM.h"


/**
  * @brief  SRAM初始化
  * @param  void
  * @retval 0 初始化成功		else 失败
  */
uint8_t SRAM_IntConfig(void)
{
	uint16_t temp;
	
	for(temp = 0; temp < 256; temp++)
	{
		*(uint8_t *)(SRAM_BASE_ADDR + temp * 1024) = temp;
	}
	for(temp = 0; temp < 256; temp++)
	{
		if(*(uint8_t *)(SRAM_BASE_ADDR + temp * 1024) != temp)
		{
			return 1;
		}
	}
	return 0;
}


/**
  * @brief  写入SRAM指定地址指定长度8位数据
  * @param  SRAM地址(从0开始)
  * @param  内存地址
  * @param  数据量
  * @retval void
  */
void SRAM_WriteByte(uint8_t *S, uint8_t *R, uint32_t Length)
{
	uint32_t index;
	uint8_t *point = (uint8_t *)((uint32_t)S + SRAM_BASE_ADDR);
	
	for(index = 0; index < Length; index++)
	{
		*(point++) = *(R++);
	}
}


/**
  * @brief  写入SRAM指定地址指定长度16位数据
  * @param  SRAM地址(从0开始)
  * @param  内存地址
  * @param  数据量
  * @retval void
  */
void SRAM_WriteHalfWord(uint16_t *S, uint16_t *R, uint32_t Length)
{
	uint32_t index;
	uint16_t *point = (uint16_t *)((uint32_t)S + SRAM_BASE_ADDR);
	
	for(index = 0; index < Length; index++)
	{
		*(point++) = *(R++);
	}
}


/**
  * @brief  写入SRAM指定地址指定长度32位数据
  * @param  SRAM地址(从0开始)
  * @param  内存地址
  * @param  数据量
  * @retval void
  */
void SRAM_WriteWord(uint32_t *S, uint32_t *R, uint32_t Length)
{
	uint32_t index;
	uint32_t *point = (uint32_t *)((uint32_t)S + SRAM_BASE_ADDR);
	
	for(index = 0; index < Length; index++)
	{
		*(point++) = *(R++);
	}
}


/**
  * @brief  写入SRAM指定地址指定长度8位数据
  * @param  SRAM地址(从0开始)
  * @param  内存地址
  * @param  数据量
  * @retval void
  */
void SRAM_ReadByte(uint8_t *S, uint8_t *R, uint32_t Length)
{
	uint32_t index;
	uint8_t *point = (uint8_t *)((uint32_t)S + SRAM_BASE_ADDR);
	
	for(index = 0; index < Length; index++)
	{
		*(R++) = *(point++);
	}
}


/**
  * @brief  写入SRAM指定地址指定长度16位数据
  * @param  SRAM地址(从0开始)
  * @param  内存地址
  * @param  数据量
  * @retval void
  */
void SRAM_ReadHalfWord(uint16_t *S, uint16_t *R, uint32_t Length)
{
	uint32_t index;
	uint16_t *point = (uint16_t *)((uint32_t)S + SRAM_BASE_ADDR);
	
	for(index = 0; index < Length; index++)
	{
		*(R++) = *(point++);
	}
}


/**
  * @brief  写入SRAM指定地址指定长度32位数据
  * @param  SRAM地址(从0开始)
  * @param  内存地址
  * @param  数据量
  * @retval void
  */
void SRAM_ReadWord(uint32_t *S, uint32_t *R, uint32_t Length)
{
	uint32_t index;
	uint32_t *point = (uint32_t *)((uint32_t)S + SRAM_BASE_ADDR);
	
	for(index = 0; index < Length; index++)
	{
		*(R++) = *(point++);
	}
}






