
#ifndef _SIM_IIC_H
#define _SIM_IIC_H

#include "stm32f4xx.h"


uint8_t IIC_SingleSend(uint8_t addr, uint8_t reg, uint8_t data);
uint8_t IIC_SingleRead(uint8_t addr, uint8_t reg, uint8_t *data);
uint8_t IIC_SendBuffer(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data);
uint8_t IIC_ReadBuffer(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data);



#endif
