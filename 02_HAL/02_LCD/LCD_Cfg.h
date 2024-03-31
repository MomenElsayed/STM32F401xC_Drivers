 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD_Cfg.h
 *
 * Description: Header file for the ATmega32 LCD driver Configurations
 *
 * Author: Momen Elsayed Shaban
 *
 *******************************************************************************/


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

/*
 * LCD Configuration Constants
 * ------------------------------
 * Define configuration constants for the LCD module, including bit mode, line numbers, character font,
 * display control settings, and LCD dimensions.
 */

/* Bit Mode Configuration */
#define LCD_EIGHT_BITS_MODE                 0    /* Use 8-bit mode for communication with the LCD */
#define LCD_FOUR_BITS_MODE                  1    /* Use 4-bit mode for communication with the LCD */
#define LCD_BIT_MODE_SELECT                 LCD_EIGHT_BITS_MODE  /* Select the desired bit mode */

/* Line Numbers Configuration */
#define LCD_SINGLE_LINE_DISPLAY             0    /* Use a single line for display on the LCD */
#define LCD_DOUBLE_LINE_DISPLAY             1    /* Use two lines for display on the LCD */
#define LCD_LINE_NUMBERS_N                  LCD_DOUBLE_LINE_DISPLAY  /* Select the number of lines to be displayed */

/* Character Font Configuration */
#define LCD_CHAR_FONT_5X7                   0    /* Use a 5x7 character font for display on the LCD */
#define LCD_CHAR_FONT_5X10                  1    /* Use a 5x10 character font for display on the LCD */
#define LCD_CHAR_FONT_F                     LCD_CHAR_FONT_5X7  /* Select the character font for display */

/* Display ON/OFF Control Configuration */
#define LCD_DISPLAY_OFF                     0    /* Turn off the display on the LCD */
#define LCD_DISPLAY_ON                      1    /* Turn on the display on the LCD */
#define LCD_DISPLAY_CONTROL_D               LCD_DISPLAY_ON  /* Select the display control setting */

/* Display Cursor Control Configuration */
#define LCD_DISPLAY_CURSOR_OFF              0    /* Turn off the cursor on the LCD */
#define LCD_DISPLAY_CURSOR_ON               1    /* Turn on the cursor on the LCD */
#define LCD_DISPLAY_CURSOR_C                LCD_DISPLAY_CURSOR_ON  /* Select the cursor control setting */

/* Cursor Blink Configuration */
#define LCD_CURSOR_BLINK_OFF                0    /* Disable cursor blinking on the LCD */
#define LCD_CURSOR_BLINK_ON                 1    /* Enable cursor blinking on the LCD */
#define LCD_CURSOR_BLINK_B                  LCD_CURSOR_BLINK_OFF  /* Select the cursor blink setting */

/* LCD Dimensions Configuration */
#define NUMBER_OF_LCD_LINES                 2    /* Specify the number of lines on the LCD (1 or 2) */
#define NUMBER_OF_LCD_COLOUMNS              16   /* Specify the number of columns on the LCD (typically 16) */
#define MAX_NUMBER_OF_LCD_CGRAM_BLOCKS      8    /* Specify the maximum number of CGRAM blocks for custom characters */
#define NUMBER_OF_LCD_PINS					11   /* Specify the maximum number of LCD Pins (typically 11) */
#define NUMBER_OF_REQ_SPECIAL_CHAR			1	 /* Specify the maximum number of required Special characters */



#endif /* LCD_CFG_H_ */
