 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD.h
 *
 * Description: Header file for the ATmega32 LCD driver
 *
 * Author: Momen Elsayed Shaban
 *
 *******************************************************************************/


#ifndef LCD_H_
#define LCD_H_

#include "LCD_Cfg.h"
#include "std_types.h"

/*******************************************************************************
 *                      Display Control Instructions                           *
 *******************************************************************************/
#define LCD_CLEAR_DISPLAY		0x01
#define LCD_RETURN_HOME			0x02
#define LCD_SET_CGRAM_ADDRESS	0x40		/*64  in Decimal*/
#define LCD_SET_DDRAM_ADDRESS	0x80		/*128 in Decimal*/
#define LCD_SHIFT_CURSOR_LEFT	0x10
#define LCD_SHIFT_CURSOR_RIGHT	0x14
#define LCD_SHIFT_DISPLAY_LEFT	0x18
#define LCD_SHIFT_DISPLAY_RIGHT	0x1C

/*******************************************************************************
 *                                Type Decelerations                           *
 *******************************************************************************/
#define LCD_CURSOR_FIRST_LINE		0
#define LCD_CURSOR_SECOND_LINE		1
#define LCD_CURSOR_THIRD_LINE		2
#define LCD_CURSOR_FOURTH_LINE		3

typedef enum {
	LCD_enumLogicLow,
	LCD_enumLogicHigh
} LCD_enumPinState_t;

enum{
	DB0,			/*in 8-bit mode used as		*/
	DB1,			/*low order bi-directional  */
	DB2,			/*data bus and in 4-bit mode*/
	DB3,			/*open these terminals		*/
	
	DB4,			/*in 8-bit mode used as		*/
	DB5,			/*high order bi-directional */
	DB6,			/*data bus and in 4-bit mode*/
	DB7,			/*used as both high and low	*/
					/*order data bus			*/
	
	RW,				/*Read Write Selection*/
	RS,				/*Register Selection*/
	E				/*Enable Signal*/
};

typedef struct{
	void* port;
	u32  pin;
}LCD_strPinCfg_t;

typedef enum{
	LCD_enumOK,
	LCD_enumInvalidCommand,
	LCD_enumInvalidLineNumber,
	LCD_enumNullPointer,
	LCD_enumInvalidNumberOfLCDPins,
	LCD_enumInvalidColNumber,
	LCD_enumInvalidCGRAMBlockNumber
}LCD_enumErrorState_t;

/*******************************************************************************
 *                              extern Variables	                           *
 *******************************************************************************/
extern LCD_strPinCfg_t LCD_strCfg[NUMBER_OF_LCD_PINS];
/*
 * Custom Characters for LCD
 * -------------------------
 * Define custom characters for the LCD based on the specified number of required special characters.
 */

#if NUMBER_OF_REQ_SPECIAL_CHAR == 1
    extern u8 customChar1[8];
#elif NUMBER_OF_REQ_SPECIAL_CHAR == 2
    extern u8 customChar1[8];
    extern u8 customChar2[8];
#elif NUMBER_OF_REQ_SPECIAL_CHAR == 3
    extern u8 customChar1[8];
    extern u8 customChar2[8];
    extern u8 customChar3[8];
#elif NUMBER_OF_REQ_SPECIAL_CHAR == 4
    extern u8 customChar1[8];
    extern u8 customChar2[8];
    extern u8 customChar3[8];
    extern u8 customChar4[8];
#elif NUMBER_OF_REQ_SPECIAL_CHAR == 5
    extern u8 customChar1[8];
    extern u8 customChar2[8];
    extern u8 customChar3[8];
    extern u8 customChar4[8];
    extern u8 customChar5[8];
#elif NUMBER_OF_REQ_SPECIAL_CHAR == 6
    extern u8 customChar1[8];
    extern u8 customChar2[8];
    extern u8 customChar3[8];
    extern u8 customChar4[8];
    extern u8 customChar5[8];
    extern u8 customChar6[8];
#elif NUMBER_OF_REQ_SPECIAL_CHAR == 7
    extern u8 customChar1[8];
    extern u8 customChar2[8];
    extern u8 customChar3[8];
    extern u8 customChar4[8];
    extern u8 customChar5[8];
    extern u8 customChar6[8];
    extern u8 customChar7[8];
#elif NUMBER_OF_REQ_SPECIAL_CHAR == 8
    extern u8 customChar1[8];
    extern u8 customChar2[8];
    extern u8 customChar3[8];
    extern u8 customChar4[8];
    extern u8 customChar5[8];
    extern u8 customChar6[8];
    extern u8 customChar7[8];
    extern u8 customChar8[8];
#endif	/*NUMBER_OF_REQ_SPECIAL_CHAR*/


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
LCD_enumErrorState_t LCD_InitAsync();

LCD_enumErrorState_t LCD_clearScreen();

LCD_enumErrorState_t LCD_WriteStringAsync(const char* str,u8 size, u8 x_pos, u8 y_pos);


#endif /* LCD_H_ */
