#include "driver_SRAM.h"


/**
  * @brief  SRAM��ʼ��
  * @param  void
  * @retval 0 ��ʼ���ɹ�		else ʧ��
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
  * @brief  д��SRAMָ����ַָ������8λ����
  * @param  SRAM��ַ(��0��ʼ)
  * @param  �ڴ��ַ
  * @param  ������
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
  * @brief  д��SRAMָ����ַָ������16λ����
  * @param  SRAM��ַ(��0��ʼ)
  * @param  �ڴ��ַ
  * @param  ������
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
  * @brief  д��SRAMָ����ַָ������32λ����
  * @param  SRAM��ַ(��0��ʼ)
  * @param  �ڴ��ַ
  * @param  ������
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
  * @brief  д��SRAMָ����ַָ������8λ����
  * @param  SRAM��ַ(��0��ʼ)
  * @param  �ڴ��ַ
  * @param  ������
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
  * @brief  д��SRAMָ����ַָ������16λ����
  * @param  SRAM��ַ(��0��ʼ)
  * @param  �ڴ��ַ
  * @param  ������
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
  * @brief  д��SRAMָ����ַָ������32λ����
  * @param  SRAM��ַ(��0��ʼ)
  * @param  �ڴ��ַ
  * @param  ������
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






