/*
 *  @brief    Display.c
 *  @details  Source file for the Display Library
 *  @date     31.03.2022
 *  @author   Meriton Aliu
 */


#include "../inc/Display.h"

//global variable for the display
static GLIB_Context_t glibcontext;

/**
 *  @brief  displayInit function
 *  @details  This function loads all the important things to initialize the display.
**/
void displayInit(void)
{
   /*status variable for the display*/
   uint32_t status;

   /* Enable the memory lcd */
   status = sl_board_enable_display();
   EFM_ASSERT(status == SL_STATUS_OK);

   /* Initialize the DMD support for memoryc lcd display */
   status = DMD_init(0);
   EFM_ASSERT(status == DMD_OK);

   /* Initialize the glib context */
   status = GLIB_contextInit(&glibcontext);
   EFM_ASSERT(status == GLIB_OK);

   //setting of the back/foreground color
   glibcontext.backgroundColor = Black;
   glibcontext.foregroundColor = White;

   //setting the font
   GLIB_setFont(&glibcontext, (GLIB_Font_t *) &GLIB_FontNarrow6x8);
   displayClear(); // clearing the old stuff on the display
}

/**
 *  @brief  displayWrite function
 *  @details  This function is used to write and display any text in any line.
 *  @param  char *text   => string of text to write on to the display
 *  @param  uint8_t line => line to write the text
**/
void displayWriteTextLine(char *text, uint8_t line)
{
  GLIB_drawStringOnLine(&glibcontext, text, line, GLIB_ALIGN_LEFT, 0,0, true);
  DMD_updateDisplay();
}

/**
 *  @brief  displayWrite function
 *  @details  This function is used to write and display any text in any line.
 *  @param  char *text   => string of text to write on to the display
 *  @param  uint8_t line => line to write the text
**/
void displayWriteTextXY(char *text,uint8_t x, uint8_t y)
{
   GLIB_drawStringOnLine(&glibcontext, text, 0, GLIB_ALIGN_LEFT, x, y, true);
   DMD_updateDisplay();
}

/**
 *  @brief  displayClear function
 *  @details  With this function the whole lcd can be emptied once.
**/
void displayClear(void)
{
  GLIB_clear(&glibcontext);
  DMD_updateDisplay();
}



