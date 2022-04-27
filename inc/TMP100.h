/*
 *  @brief    TMP100.h
 *  @details  Header file for the TMP100 Library
 *  @date     31.03.2022
 *  @author   Meriton Aliu
 */


#ifndef TMP100_H_
#define TMP100_H_

#include "includes.h"
#include "I2C.h"
#include "Display.h"
#include "em_i2c.h"

#define TMP100_ADDR   0x48<<1 // Address of the TMP100
#define TMP100_RESOLUTIONDEL 0x9F

typedef enum{ //resolutions
  TMP100_12BIT = 0x60,
  TMP100_11BIT = 0x40,
  TMP100_10BIT = 0x20,
  TMP100_9BIT  = 0x00
}TMP100_RESOULTION;

typedef enum
{                              // typedef enum for the register
  tempsensRegTemp   =     0,   // Temperature register (read-only)
  tempsensRegConfig =     1,   // Configuration register
  tempsensRegTLow   =     2,   // Hysteresis register
  tempsensRegTHigh  =     3    // Overtemperature shutdown register
} TEMPSENS_Register_TypeDef;

typedef struct TEMPSENS_Temp_TypeDef  // typedef prototype for the return of the temperature
{
  int16_t i;                          // i = integer part
  int16_t f;                          // f = fractional part in 1/10000
}TEMPSENS_Temp_TypeDef_t;

void Tmp100ShowTemperature(uint8_t y);
void Tmp100SetResolution(uint8_t resolution);

#endif /* INC_TMP100_H_ */
