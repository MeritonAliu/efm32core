/*
 *  @brief    GPIO.h
 *  @details  Header file for the GPIO Library
 *  @date     31.03.2022
 *  @author   Meriton Aliu
 */


#ifndef GPIO_H_
#define GPIO_H_

#define GPIO_CLEAR_FLAG_EVEN 0x5555
#define GPIO_CLEAR_FLAG_ODD 0xAAAA

#include "includes.h"
#include <em_gpio.h>
#include "em_cmu.h"

//definition of push button 0
#define PUSHBUTTON_0_PORT gpioPortC
#define PUSHBUTTON_0_PIN  8

//definition of push button 1
#define PUSHBUTTON_1_PORT gpioPortC
#define PUSHBUTTON_1_PIN  9

//definition of LED 0
#define LED_0_PORT        gpioPortC
#define LED_0_PIN         10

//definition of LED 0
#define LED_1_PORT        gpioPortC
#define LED_1_PIN         11

// definition of I2C0 SCL on PE13
#define I2C0_SCL_PORT     gpioPortE
#define I2C0_SCL_PIN      13
#define I2C0_ROUTE_LOC    6

// definition of I2C0 SDA on PE12
#define I2C0_SDA_PORT     gpioPortE
#define I2C0_SDA_PIN      12

void GPIO_EVEN_IRQHandler(void);
void GPIO_ODD_IRQHandler(void);
void gpioInitInterruptPB0(void);
void gpioInitInterruptPB1(void);
void gpioInitInputPB0(void);
void gpioInitInputPB1(void);
void gpioInitInput(void);
void gpioInitLEDS(void);
void gpioI2CSet(void);
int8_t gpioGetPushButton(uint8_t button);
void gpioSetLedOn(uint8_t led);
void gpioSetLedOff(uint8_t led);
void gpioToggleLed(uint8_t led);

#endif /* GPIO_H_ */








