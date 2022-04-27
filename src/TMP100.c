/*
 *  @brief    TMP100.c
 *  @details  Source file for the TMP100 Library
 *  @date     Created on: 31.03.2022
 *  @author   Meriton Aliu
 */

#include "../inc/TMP100.h"


/**
 *  @brief    Tmp100GetTemperature function
 *  @details  This function gets the register value for the temperature out of the TMP100
 *  @return   uint16_t tempreg => temperature value form the register
**/
static uint16_t Tmp100GetTemperature()
{
  uint8_t readdata[2] = {0,0}; // arr
  uint8_t writedata = tempsensRegTemp;

  I2CWriteRead(TMP100_ADDR, &writedata, 1, &readdata[0], 2);

  return (((uint16_t) (readdata[0])) << 8) | readdata[1];
}

/**
 *  @brief    Tmp100RegToCelsius function
 *  @details  This function calculates the register output of the TMP100 to celsius
 *  @param    uint16_t tempreg => register output variable (return value of getTemperature function)
 *  @return   TEMPSENS_Temp_TypeDef_t tmp => temperature value in celsius
**/
static void Tmp100RegToCelsius(uint16_t *tempreg, TEMPSENS_Temp_TypeDef_t *tempcelsius, uint8_t *negative)
{
  *tempreg = (uint32_t)(*tempreg >> 4);

  /* If negative number, convert using 2s complement */
  if (*tempreg & 0x800) // -
  {
      *negative = 1;
      *tempreg = (~*tempreg + 1) & 0xfff;
      tempcelsius->i = - (int16_t)(*tempreg >> 4);
      tempcelsius->f = - (int16_t)((*tempreg & 0xf) * 625);
  }
  else{ // +
      *negative = 0;
      tempcelsius->i = (int16_t)(*tempreg >> 4);
      tempcelsius->f = (int16_t)((*tempreg & 0xf) * 625);
  }
}

/**
 *  @brief    Tmp100DisplayTemperatureUpdate function
 *  @details  This function is used to display a temperature at a desired line
 *  @param    TEMPSENS_Temp_TypeDef_t *temp   -> temperature to write on the display
 *  @param    uint8_t y                       -> y coordinate to write the temperature
**/
static void Tmp100DisplayTemperatureUpdate(const TEMPSENS_Temp_TypeDef_t *temp, uint8_t y, uint8_t *negative)
{
  int8_t text[8];
  uint8_t index = 0;
  TEMPSENS_Temp_TypeDef_t dtemp = *temp;

  memset(text, ' ', sizeof(text) - 1);
  text[sizeof(text) - 1] = 0;

  if(*negative){ // negativ
      text[index] = '-';
  }else{ // positiv
      text[index] = '+';
  }

  index++;
  /* 100s */
  if (abs(dtemp.i) >= 100){
    text[index] = '0' + (abs(dtemp.i) / 100);
    index++;
  }
  /* 10s */
  if (abs(dtemp.i) >= 10){
    text[index] = '0' + ((abs(dtemp.i) % 100) / 10);
  }
  index++;

  /* 1s */
  text[index] = '0' + (abs(dtemp.i) % 10);

  //check if there are 0.1s?
  if((abs(dtemp.f) / 1000)){
      index++;
      text[index] = '.'; // point
      index++;
      /* 0.1s */
      text[index] = '0' + (abs(dtemp.f) / 1000); // 6250 / 1000 = 6.25
      index++;
      //check if there are 0.01s?
      if(((abs(dtemp.f) % 1000) / 100)){
          /* 0.01s */
          text[index] = '0' + ((abs(dtemp.f) % 1000) / 100);// 6250 % 1000 = 250 / 100 = 2.5...
          index++;
          //check if there are 0.01s?
          if(((abs(dtemp.f) % 100) / 10)){
              /* 0.001s */
              text[index] = '0' + ((abs(dtemp.f) % 100) / 10);
              index++;
          }else{
              displayWriteTextXY("           ", 120, y); // clear rest
          }
     }else{
          displayWriteTextXY("           ", 120, y);// clear rest
      }
  }else{
      displayWriteTextXY("           ", 120, y);// clear rest
      index++;
      text[index] = '.'; // point
      index++;
  }
  text[index] = 'C'; // grade celsius

  displayWriteTextXY("Temperature: ", 0, y);

  displayWriteTextXY((char *)text, 80, y); // 80
}

/**
 *  @brief    Tmp100GetConfig function
 *  @details  This function is used to get the config register from the tmp100
 *  @return   uint8_t data[0]; -> value of the config register
**/
static uint8_t Tmp100GetConfig()
{
  uint8_t data;
  uint8_t sendregister = tempsensRegConfig;
  I2CWriteRead(TMP100_ADDR, &sendregister, 1, &data, 1);

  return data;
}

/**
 *  @brief    Tmp100SetConfig function
 *  @details  This function is used to set the config register from the tmp100
 *  @param    uint8_t config_value -> value to set the config register
**/
static void Tmp100SetConfig(uint8_t config_value)
{
  uint8_t datawrite[2] = {tempsensRegConfig, config_value};
  I2CWrite(TMP100_ADDR, &datawrite, 2);
}


/**
 *  @brief    Tmp100SetResolution function
 *  @details  With this function you can choose in which resolution the tmp100 is going to output its temperature
 *  @param    uint8_t resolution -> wished temperature resolution
**/
void Tmp100SetResolution(uint8_t resolution)
{
  static uint8_t config_value;
  Tmp100GetConfig(&config_value); // config lesen
  config_value &= TMP100_RESOLUTIONDEL; // config löschen
  config_value |= resolution; //config manipulieren
  Tmp100SetConfig(config_value);
}

/**
 *  @brief    Tmp100ShowTemperature function
 *  @details  This function controls all the temperature communication from the TMP100 and shows it on to the display
 *  @param    uint8_t y => y coordinate to show out the temperature
**/
void Tmp100ShowTemperature(uint8_t y)
{
  //variables for the temp and register
  TEMPSENS_Temp_TypeDef_t tempcelsius;
  uint16_t tempreg;
  uint8_t negative;
  tempreg = Tmp100GetTemperature(I2C0);             // gets the temperature from the register
  Tmp100RegToCelsius(&tempreg, &tempcelsius, &negative);
  Tmp100DisplayTemperatureUpdate(&tempcelsius, y, &negative);  // shows the temperature on to the display
}





