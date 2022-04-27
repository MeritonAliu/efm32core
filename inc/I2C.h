/*
 *  @brief    I2C.h
 *  @details  Header file for the I2C library
 *  @date     31.03.2022
 *  @author   Meriton Aliu
 */

#ifndef I2C_H_
#define I2C_H_

#include "includes.h"
#include "Display.h"
#include "GPIO.h"
#include "em_i2c.h"
#include "em_cmu.h"

#define TMP100_ADDR 0x48<<1 // Address of the TMP100

void I2CInit(void);
I2C_TransferReturn_TypeDef I2CWrite(uint8_t address, uint8_t *datawrite, uint16_t lenwrite);
I2C_TransferReturn_TypeDef I2CWriteRead(uint8_t address, uint8_t *datawrite, uint16_t lenwrite, uint8_t *dataread, uint16_t lenread);

#endif /* I2C_H_ */

