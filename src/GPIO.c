/*
 *  @brief    GPIO.c
 *  @details  Source file for the GPIO Library
 *  @date     31.03.2022
 *  @author   Meriton Aliu
 */

#include "../inc/GPIO.h"

volatile uint8_t myevengpioflag; // flag which is turned on at GPIO_EVEN_IRQHandler
volatile uint8_t myoddgpioflag;  // flag which is turned on at GPIO_ODD_IRQHandler

/**
 * @brief   GPIO_EVEN_IRQHandler function
 * @details Interrupt Handler for the EVEN Buttons
**/
void GPIO_EVEN_IRQHandler(void) // PB0
{
  // Clear all even pin interrupt flags
  GPIO_IntClear(GPIO_CLEAR_FLAG_EVEN);
  myevengpioflag = 1;
  // your IRQ code...
  // example Toggle LED0
}

/**
 * @brief   GPIO_ODD_IRQHandler function
 * @details Interrupt Handler for the ODD Buttons
**/
void GPIO_ODD_IRQHandler(void) //PB1
{
  // Clear all even pin interrupt flags
  GPIO_IntClear(GPIO_CLEAR_FLAG_ODD);
  myoddgpioflag = 1;
  // your IRQ code...
  // example Toggle LED1
    //gpioToggleLed(1);

}

/**
 * @brief   gpioInitInterruptPB0 function
 * @details This function is used initialize the button 0 as interrupt input
**/
void gpioInitInterruptPB0(void)
{
  // Enable GPIO clock
  CMU_ClockEnable(cmuClock_GPIO, true);

  // Configure PB0 and PB1 as input with glitch filter enabled
  GPIO_PinModeSet(PUSHBUTTON_0_PORT, PUSHBUTTON_0_PIN, gpioModeInputPullFilter, 1);

  // Configure LED0 and LED1 as output
  gpioInitLEDS();
  // Enable IRQ for even numbered GPIO pins
  NVIC_EnableIRQ(GPIO_EVEN_IRQn);

  // Enable falling-edge interrupts for PB pins
  GPIO_ExtIntConfig(PUSHBUTTON_0_PORT, PUSHBUTTON_0_PIN, PUSHBUTTON_0_PIN, 0, 1, true);
}

/**
 * @brief   gpioInitInterruptPB0 function
 * @details This function is used initialize the button 0 as interrupt input
**/
void gpioInitInterruptPB1(void)
{
  // Enable GPIO clock
  CMU_ClockEnable(cmuClock_GPIO, true);

  // Configure PB0 and PB1 as input with glitch filter enabled
  GPIO_PinModeSet(PUSHBUTTON_1_PORT, PUSHBUTTON_1_PIN, gpioModeInputPullFilter, 1);

  // Configure LED0 and LED1 as output

  // Enable IRQ for odd numbered GPIO pins
  NVIC_EnableIRQ(GPIO_ODD_IRQn);;

  // Enable falling-edge interrupts for PB pins
  GPIO_ExtIntConfig(PUSHBUTTON_1_PORT, PUSHBUTTON_1_PIN, PUSHBUTTON_1_PIN, 0, 1, true);
}

/**
 * @brief   gpioInitInputPB0 function
 * @details This function is used initialize the button 0 as normal input
**/

void gpioInitInputPB0(void)
{
  GPIO_PinModeSet(PUSHBUTTON_0_PORT, PUSHBUTTON_0_PIN, gpioModeInput, 1);
}

/**
 * @brief   gpioInitInputPB1 function
 * @details This function is used initialize the button 1 as normal input
**/
void gpioInitInputPB1(void)
{
  GPIO_PinModeSet(PUSHBUTTON_1_PORT, PUSHBUTTON_1_PIN, gpioModeInput, 1);
}

/**
 * @brief   gpioInitInput function
 * @details This function is used initialize the button 0 and 1 as normal input
**/
void gpioInitInput(void)
{
  gpioInitInputPB1();
  gpioInitInputPB0();
}

/**
 * @brief   gpioInitLEDS function
 * @details This function is used initialize the LEDS as outputs
**/
void gpioInitLEDS(void)
{
  GPIO_PinModeSet(LED_1_PORT, LED_1_PIN, gpioModePushPull, 0);
  GPIO_PinModeSet(LED_0_PORT, LED_0_PIN, gpioModePushPull, 0);
}

/**
 *  @brief    gpioI2CSet function
 *  @details  This function is used to set the I2C GPIO Pins
**/
void gpioI2CSet(void)
{
  GPIO_PinModeSet(I2C0_SCL_PORT, I2C0_SCL_PIN, gpioModeWiredAndPullUpFilter, 1);
  GPIO_PinModeSet(I2C0_SDA_PORT, I2C0_SDA_PIN, gpioModeWiredAndPullUpFilter, 1);
}

/**
 *  @brief    gpioGetPushButton function
 *  @details  This function is used to get the value of a button
 *  @param    uint8_t button  => indicates which button to return
 *  @return   int8_t => state of the push button
**/
int8_t gpioGetPushButton(uint8_t button)
{
  //returns wished push button value
  if(button == 0){
     return GPIO_PinInGet(PUSHBUTTON_0_PORT, PUSHBUTTON_0_PIN);
  }
  else if(button == 1){
      return GPIO_PinInGet(PUSHBUTTON_1_PORT, PUSHBUTTON_1_PIN);
  }
  else{
      while(1);//This button doesn't exist
  }
}

/**
 *  @brief    gpioSetLedOn function
 *  @details  This function is used to turn on an led
 *  @param    uint8_t led => indicates which LED to turn on
**/
void gpioSetLedOff(uint8_t led)
{
  //turns wished led off
  if(led == 0){
      GPIO_PinOutClear(LED_0_PORT, LED_0_PIN);
  }
  else if(led == 1){
      GPIO_PinOutClear(LED_1_PORT, LED_1_PIN);
  }
  else{
      while(1);//This led doesn't exist
  }
}


/**
 *  @brief    gpioSetLedOff function
 *  @details  This function is used to turn off an led
 *  @param    uint8_t led => indicates which LED to turn off
**/
void gpioSetLedOn(uint8_t led)
{
  //turns wished led on
  if(led == 0){
      GPIO_PinOutSet(LED_0_PORT, LED_0_PIN);
  }
  else if(led == 1){
      GPIO_PinOutSet(LED_1_PORT, LED_1_PIN);
  }
  else
    {
      while(1);//This led doesn't exist
  }
}

/**
 *  @brief    gpioToggleLed function
 *  @details  This function is used to toggle an led
 *  @param    uint8_t led => indicates which LED to toggle
**/
void gpioToggleLed(uint8_t led)
{
  //toggles wished led on
  if(led == 0){
      GPIO_PinOutToggle(LED_0_PORT, LED_0_PIN);
  }
  else if(led == 1){
      GPIO_PinOutToggle(LED_1_PORT, LED_1_PIN);
  }
  else
    {
      while(1);//This led doesn't exist
  }

}










