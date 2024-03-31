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


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*****************************************************
 * Function: LCD_InitAsync
 * Description: Initializes the LCD pins asynchronously based on the selected bit mode.
 *
 * Parameters: None
 *
 * Return:
 *   - LCD_enumErrorState_t: Error state indicating the success or failure of the initialization.
 *     - LCD_enumOK: Initialization successful.
 *
 * Usage:
 *   LCD_enumErrorState_t status = LCD_InitAsync();
 *   if(status == LCD_enumOK) {
 *     // LCD initialization process initiated successfully
 *   } else {
 *     // Handle error
 *   }
 *
 * Notes:
 *   - This function initializes the LCD pins asynchronously based on the selected bit mode.
 *   - Each LCD pin is configured as an output with a specified speed.
 *   - Configuration is based on the bit mode selected (eight bits or four bits).
 *   - The actual initialization process may be handled asynchronously by the GPIO module.
 *****************************************************/
LCD_enumErrorState_t LCD_InitAsync();

/*****************************************************
 * Function: LCD_clearScreen
 * Description: Initiates the process to clear the LCD screen.
 *
 * Parameters: None
 *
 * Return:
 *   - LCD_enumErrorState_t: Error state indicating the success or failure of the operation.
 *     - LCD_enumOK: Operation successful.
 *
 * Usage:
 *   LCD_enumErrorState_t status = LCD_clearScreen();
 *   if(status == LCD_enumOK) {
 *     // LCD screen clearing process initiated successfully
 *   } else {
 *     // Handle error
 *   }
 *
 * Notes:
 *   - This function sets the LCD user request state to busy and initializes the LCD
 *     clear request type. It also sets the clear state to start the clearing process.
 *   - The LCD screen clearing process will be handled asynchronously.
 *   - The LCD module must be in an operational state (LCD_operationalState) and not
 *     handling any other user requests (LCD_ReqIdle) for the clearing process to begin.
 *****************************************************/
LCD_enumErrorState_t LCD_clearScreen();

/*****************************************************
 * Function: LCD_WriteStringAsync
 * Description: Initiates asynchronous writing of a string to the LCD screen.
 *
 * Parameters:
 *   - str: Pointer to the string to be written.
 *   - size: Size of the string to be written.
 *   - x_pos: X-coordinate position on the LCD screen.
 *   - y_pos: Y-coordinate position on the LCD screen.
 *
 * Return:
 *   - LCD_enumErrorState_t: Error state indicating the success or failure of the operation.
 *     - LCD_enumOK: Operation successful.
 *     - LCD_enumNullPointer: Null pointer provided for the string.
 *     - LCD_enumInvalidLineNumber: Invalid line number provided.
 *     - LCD_enumInvalidColNumber: Invalid column number provided.
 *
 * Usage:
 *   LCD_enumErrorState_t status = LCD_WriteStringAsync("Hello", 5, 0, 0);
 *   if(status == LCD_enumOK) {
 *     // Asynchronous writing process initiated successfully
 *   } else {
 *     // Handle error
 *   }
 *
 * Notes:
 *   - This function initiates the asynchronous writing of a string to the LCD screen.
 *   - The string, its size, and the position on the screen are provided as parameters.
 *   - If the LCD module is idle and in operational state, the provided string, size,
 *     and position are assigned to the LCD user request structure to begin the writing process.
 *   - The actual writing process may be handled asynchronously by the LCD module.
 *****************************************************/
LCD_enumErrorState_t LCD_WriteStringAsync(const char* str,u8 size, u8 x_pos, u8 y_pos);


#endif /* LCD_H_ */
