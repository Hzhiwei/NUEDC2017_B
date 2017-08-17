#ifndef __DRIVER_SRAM_H
#define __DRIVER_SRAM_H


#include "stm32f4xx.h"


#define SRAM_BASE_ADDR	((uint32_t)0x68000000)


uint8_t SRAM_IntConfig(void);
void SRAM_WriteByte(uint8_t *S, uint8_t *R, uint32_t Length);
void SRAM_WriteHalfWord(uint16_t *S, uint16_t *R, uint32_t Length);
void SRAM_WriteWord(uint32_t *S, uint32_t *R, uint32_t Length);
void SRAM_ReadByte(uint8_t *S, uint8_t *R, uint32_t Length);
void SRAM_ReadHalfWord(uint16_t *S, uint16_t *R, uint32_t Length);
void SRAM_ReadWord(uint32_t *S, uint32_t *R, uint32_t Length);




#endif
