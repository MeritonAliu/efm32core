/*
 *  @brief    coreTimer.h
 *  @details  Header file for the Display Library
 *  @date     07.04.2022
 *  @author   Meriton Aliu
 */

#ifndef TIMER_H_
#define TIMER_H_


#include "em_cmu.h"
#include "em_gpio.h"
#include "em_timer.h"
#include "GPIO.h"


void timer0Init500ms(void);
void timer1Init1ms(void);

#endif /* CORETIMER_H_ */
