/*
 *  @brief    Timer.c
 *  @details  Source file for the Display Library
 *  @date     14.04.2022
 *  @author   Meriton Aliu
 */

#include "../inc/Timer.h"

//global variable for the timer interrupts
volatile uint8_t mytimer0flag;
volatile uint8_t mytimer1flag;

/**
 *  @brief    TIMER0_IRQHandler function
 *  @details  Clears the Int Flag, turns global flag to 1 and it could run IRQ Code
**/
void TIMER0_IRQHandler(void){
  //clear interrupt flag at begin
  TIMER_IntClear(TIMER0, TIMER_IFC_OF);
  mytimer0flag = 1;
  //IRQ Timer Code...
}

/**
 *  @brief    TIMER1_IRQHandler function
 *  @details  Clears the Int Flag, turns global flag to 1 and it could run IRQ Code
**/
void TIMER1_IRQHandler(void){
  //clear interrupt flag at begin
  TIMER_IntClear(TIMER1, TIMER_IFC_OF);
  mytimer1flag = 1;
  //IRQ Timer Code...
}

/**
 *  @brief    timer0Init500ms function
 *  @details  Initialisation of the timer0 500ms
**/
void timer0Init500ms(void){
  CMU_ClockEnable(cmuClock_TIMER0, true);
  /* calculation
   * lower prescale = higher resolution and higher energy consumption
   *
   * 24MHz / timerPrescale256 = 93.75kHz || 1/93.75kHz = 1.06666667×10^-5
   * 0.5s/1.06666667×10^-5 = 46874 (topTime)
   */
  //Select TIMER0 parameters
   const TIMER_Init_TypeDef timerInit =
   {
     .enable     = true,
     .debugRun   = true,
     .prescale   = timerPrescale256,
     .clkSel     = timerClkSelHFPerClk,
     .fallAction = timerInputActionNone,
     .riseAction = timerInputActionNone,
     .mode       = timerModeUp,
     .dmaClrAct  = false,
     .quadModeX4 = false,
     .oneShot    = false,
     .sync       = false,
   };
  /* Enable TIMER0 IRQ on Overflow */
  TIMER_IntEnable(TIMER0, TIMER_IF_OF);

  /* Enable TIMER0 interrupt in NVIC */
  NVIC_EnableIRQ(TIMER0_IRQn);

  ///Set the toptime counter
  TIMER_TopSet(TIMER0, 46875);

  //Init the Timer
  TIMER_Init(TIMER0, &timerInit);
}

/**
 *  @brief    timer1Init1ms function
 *  @details  Initialisation of the timer1 1ms
**/
void timer1Init1ms(void){
  CMU_ClockEnable(cmuClock_TIMER1, true);
  //calculation
  /* lower prescale = higher resolution and higher energy consumption
   *
   * 24MHz / timerPrescale256 = 93.75kHz || 1/93.75kHz = 1.06666667×10^-5
   * 0.001s/1.06666667×10^-5 = 94 (topTime)
   */

  //Select TIMER1 parameters
   const TIMER_Init_TypeDef timerInit =
   {
     .enable     = true,
     .debugRun   = true,
     .prescale   = timerPrescale256,
     .clkSel     = timerClkSelHFPerClk,
     .fallAction = timerInputActionNone,
     .riseAction = timerInputActionNone,
     .mode       = timerModeUp,
     .dmaClrAct  = false,
     .quadModeX4 = false,
     .oneShot    = false,
     .sync       = false,
   };
  /* Enable TIMER1 IRQ on Overflow */
  TIMER_IntEnable(TIMER1, TIMER_IF_OF);

  /* Enable TIMER1 interrupt in NVIC */
  NVIC_EnableIRQ(TIMER1_IRQn);

  //Set the toptime counter
  TIMER_TopSet(TIMER1, 93); //

  //Init the Timer
  TIMER_Init(TIMER1, &timerInit);
}







