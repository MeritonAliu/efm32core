/*
 *  @brief    Display.h
 *  @details  Header file for the Display Library
 *  @date     31.03.2022
 *  @author   Meriton Aliu
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "includes.h"
#include "dmd.h"
#include "glib.h"
#include "sl_board_control.h"
#include <sl_status.h>
#include "sl_udelay.h"
#include "em_assert.h"

void displayInit(void);
void displayWriteTextLine(char *text, uint8_t line);
void displayWriteTextXY(char *text,uint8_t x, uint8_t y);
void displayClear(void);

#endif /* DISPLAY_H_ */
