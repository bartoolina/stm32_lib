#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

typedef struct 
{
    uint8_t dummy;
}I2C_HandleTypeDef;

void HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t mem, uint8_t i, uint8_t *data, uint8_t, uint8_t);

#endif