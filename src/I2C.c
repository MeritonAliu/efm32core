/*
 *  @brief    I2C.c
 *  @details  Source file for the I2C library
 *  @date     31.03.2022
 *  @author   Meriton Aliu
 */

#include "../inc/I2C.h"

/**
 *  @brief    i2cInitTmp100 function
 *  @details  This function initialize all the needed functions for the I2C communication with the TMP100
**/
void I2CInit(void)
{
  I2C_Init_TypeDef i2cinit = I2C_INIT_DEFAULT;
  CMU_ClockEnable(cmuClock_I2C0, true);
  I2C_SlaveAddressSet(I2C0, TMP100_ADDR);
  // sets GPIO Pins on PortE, SCL to 13 and SDA to 12
  gpioI2CSet();

  /* Enable pins at location x (which is used on the DVK) */
  I2C0->ROUTE = I2C_ROUTE_SDAPEN | I2C_ROUTE_SCLPEN | (I2C0_ROUTE_LOC << _I2C_ROUTE_LOCATION_SHIFT);

  I2C_Init(I2C0, &i2cinit);
  I2C_Enable(I2C0, 1);

  /* Clear and enable interrupt from I2C module */
  //NVIC_ClearPendingIRQ(I2C0_IRQn);
  // NVIC_EnableIRQ(I2C0_IRQn);
}

/**
 *  @brief    I2CWrite function
 *  @details  Use to send a write sequence with I2C.
 *  @param    uint8_t   address      => address from slave
 *  @param    uint8_t   *datawrite  => data to write
 *  @param    uint16_t  lenwrite    => length of data to write in bytes
 *  @return   return I2C_Status;    => control status
**/
I2C_TransferReturn_TypeDef I2CWrite(uint8_t address, uint8_t *datawrite, uint16_t lenwrite){
  I2C_TransferReturn_TypeDef I2C_Status;
  I2C_TransferSeq_TypeDef seq;

  seq.addr = address;
  seq.flags = I2C_FLAG_WRITE;
  seq.buf[0].data = datawrite;
  seq.buf[0].len = lenwrite;
  I2C_Status = I2C_TransferInit(I2C0, &seq);
  while (I2C_Status == i2cTransferInProgress)
  {
     I2C_Status = I2C_Transfer(I2C0);
  }

  return I2C_Status;
}

/**
 *  @brief    I2CWriteRead function
 *  @details  Use to send a write and read sequence with I2C.
 *  @param    uint8_t   address      => address from slave
 *  @param    uint8_t   *datawrite  => data to write
 *  @param    uint16_t  lenwrite    => length of data to write in bytes
 *  @param    uint8_t   *dataread   => data to read
 *  @param    uint16_t  lenread     => length of data to read in bytes
 *  @return   return I2C_Status;    => control status
**/
I2C_TransferReturn_TypeDef I2CWriteRead(uint8_t address, uint8_t *datawrite, uint16_t lenwrite, uint8_t *dataread, uint16_t lenread){
  I2C_TransferReturn_TypeDef I2C_Status;
  I2C_TransferSeq_TypeDef seq;

  seq.addr = address;
  seq.flags = I2C_FLAG_WRITE_READ;
  seq.buf[0].data = &datawrite[0];
  seq.buf[0].len = lenwrite;
  seq.buf[1].data = &dataread[0];
  seq.buf[1].len = lenread;
  I2C_Status = I2C_TransferInit(I2C0, &seq);

  while (I2C_Status == i2cTransferInProgress)
  {
      I2C_Status = I2C_Transfer(I2C0);
  }
  return I2C_Status;
}

/**
 *  @brief    I2CRead function
 *  @details  Use to send a read sequence with I2C.
 *  @param    uint8_t   address      => address from slave
 *  @param    uint8_t   *dataread   => data to read
 *  @param    uint16_t  lenread     => length of data to read in bytes
 *  @return   return I2C_Status;    => control status
**/
I2C_TransferReturn_TypeDef I2CRead(uint8_t address, uint8_t *dataread, uint16_t lenread){
  I2C_TransferReturn_TypeDef I2C_Status;
  I2C_TransferSeq_TypeDef seq;

  seq.addr = address;
  seq.flags = I2C_FLAG_READ;
  seq.buf[0].data = dataread;
  seq.buf[0].len = lenread;
  I2C_Status = I2C_TransferInit(I2C0, &seq);

  while (I2C_Status == i2cTransferInProgress)
  {
      I2C_Status = I2C_Transfer(I2C0);
  }
  return I2C_Status;
}















