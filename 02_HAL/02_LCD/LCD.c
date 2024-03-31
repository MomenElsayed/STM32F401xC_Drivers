 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD.c
 *
 * Description: Source file for the ATmega32 LCD driver
 *
 * Author: Momen Elsayed Shaban
 *
 *******************************************************************************/
#include "LCD.h"
#include "GPIO.h"


/*
 * Macros for Concatenating Binary Digits:
 * ---------------------------------------
 * Define a helper macro (CONCAT_HELPER) to concatenate binary literals for configuring LCD settings.
 * Define a macro (CONCAT) to concatenate eight binary digits using the helper macro.
 */
#define CONCAT_HELPER(pin7, pin6, pin5, pin4, pin3, pin2, pin1, pin0) (0b##pin7##pin6##pin5##pin4##pin3##pin2##pin1##pin0)
#define CONCAT(a, b, c, d, e, f, g, h) CONCAT_HELPER(a, b, c, d, e, f, g, h)

/*
 * LCD Configuration Based on Bit Mode:
 * -------------------------------------
 * Define the number of command or data pins and the data length based on the LCD bit mode.
 * Define specific configuration parameters for eight and four bits mode.
 */
#if LCD_BIT_MODE_SELECT == LCD_EIGHT_BITS_MODE

	#define NUMBER_OF_CD_PINS        8       /* Number of Command or Data Pins */
	#define LCD_DL                   1       /* LCD Data Length DL */
	#define LCD_FUNCTION_SET         CONCAT(0, 0, 1, LCD_DL, LCD_LINE_NUMBERS_N, LCD_CHAR_FONT_F, 0, 0)
	#define LCD_DISPLAY_CONTROL      CONCAT(0, 0, 0, 0, 1, LCD_DISPLAY_CONTROL_D, LCD_DISPLAY_CURSOR_C, LCD_CURSOR_BLINK_B)

#elif LCD_BIT_MODE_SELECT == LCD_FOUR_BITS_MODE

	#define NUMBER_OF_CD_PINS                  4
	#define LCD_DL                             0       /* LCD Data Length DL */
	#define LCD_PRE_FUNCTION_SET               0x20
	#define LCD_FUNCTION_SET                   CONCAT(0, 0, 1, LCD_DL, LCD_LINE_NUMBERS_N, LCD_CHAR_FONT_F, 0, 0)
	#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1 0x33
	#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2 0x32
	#define LCD_PRE_DISPLAY_CONTROL            0x00
	#define LCD_DISPLAY_CONTROL                CONCAT(0, 0, 0, 0, 1, LCD_DISPLAY_CONTROL_D, LCD_DISPLAY_CURSOR_C, LCD_CURSOR_BLINK_B)
	#define LCD_PRE_CLEAR_DISPLAY              0x00

#endif /* LCD_BIT_MODE_SELECT == LCD_EIGHT_BITS_MODE */



/*******************************************************************************
 *                              Static Functions	                           *
 *******************************************************************************/
static void LCD_InitStateMachine();
static void LCD_setTriggerEnable(u8 value);
static void LCD_writeCommandAsync(u8 Copy_u8command);
static void LCD_writeDataAsync(u8 Copy_u8data);
static void LCD_writeProc();
static void LCD_clearProc();

/*******************************************************************************
 *                        	  Types Declaration                                *
 *******************************************************************************/
#define LCD_TRIGGER_ENABLE_HIGH		1
#define LCD_TRIGGER_ENABLE_LOW		0

typedef enum
{
	LCD_PowerOn,
    LCD_FunctionSet1,
	LCD_FunctionSet2,
    LCD_DisplayControl,
    LCD_ClearDisplay,
    LCD_EndInit
} LCD_InitMode_t;

typedef enum
{
	Write_Start,
	Write_SetPostion,
    Write_Character,
    Write_Done
}LCD_writeState_t;

typedef enum
{
	Clear_Start,
	Clear_InProgress,
    Clear_Done
}LCD_clearState_t;

typedef enum
{
	LCD_initState,
	LCD_operationalState,
	LCD_off,
} LCD_State_t;

typedef enum{
    LCD_ReqIdle,
    LCD_ReqBusy
}LCD_ReqState_t;

typedef enum{
    LCD_ReqWtire,
    LCD_ReqClear,
    LCD_NoReq
}LCD_ReqType_t;

typedef struct{
	const char* data;
	u8 data_size;
	u8 x_pos;
	u8 y_pos;
	LCD_ReqState_t Req_state;
	LCD_ReqType_t Req_type;
}LCD_UserReq_t;

/*******************************************************************************
 *                              Global Variables	                           *
 *******************************************************************************/
u8 send_higher_nibble = 1;
u8 LCD_triggerEnableState = LCD_TRIGGER_ENABLE_LOW;
u8 remaining_chars = 0;

static LCD_UserReq_t LCD_UserReq;

LCD_InitMode_t LCD_initMode = LCD_PowerOn;
LCD_State_t	LCD_state = LCD_initState;
LCD_writeState_t LCD_writeState = Write_Start;
LCD_clearState_t LCD_clearState = Clear_Start;



/*******************************************************************************
 *                              	Functions   	                           *
 *******************************************************************************/

LCD_enumErrorState_t LCD_clearScreen()
{
	LCD_enumErrorState_t Error_status = LCD_enumOK;
	if(LCD_UserReq.Req_state == LCD_ReqIdle && LCD_state == LCD_operationalState)
	{
		LCD_UserReq.Req_state = LCD_ReqBusy;
		LCD_UserReq.Req_type = LCD_ReqClear;
		LCD_clearState = Clear_Start;
	}
	else
	{
		/*Do Nothing*/
	}
	return Error_status;
}

LCD_enumErrorState_t LCD_WriteStringAsync(const char* str,u8 size, u8 x_pos, u8 y_pos)
{
	LCD_enumErrorState_t Error_status = LCD_enumOK;
	if(str == NULL_PTR)
	{
		Error_status = LCD_enumNullPointer;
	}
	else if (x_pos > NUMBER_OF_LCD_LINES)
	{
		Error_status = LCD_enumInvalidLineNumber;
	}
	else if (y_pos > NUMBER_OF_LCD_COLOUMNS)
	{
		Error_status = LCD_enumInvalidColNumber;
	}
	else
	{
		if(LCD_UserReq.Req_state == LCD_ReqIdle && LCD_state == LCD_operationalState)
		{
			LCD_UserReq.data = str;
			LCD_UserReq.data_size = size;
			LCD_UserReq.x_pos = x_pos;
			LCD_UserReq.y_pos = y_pos;
			LCD_UserReq.Req_state = LCD_ReqBusy;
			LCD_UserReq.Req_type = LCD_ReqWtire;
			LCD_writeState = Write_Start;
			remaining_chars = LCD_UserReq.data_size;
		}
		else
		{
			/*Do Nothing*/
		}
	}
	return Error_status;
}



LCD_enumErrorState_t LCD_InitAsync()
{
    u8 loc_iterator_Pins = 0;
    LCD_enumErrorState_t loc_LCD_ErrorState = LCD_enumOK;
    GPIO_Pin_t loc_PORTstrConfig;

    /* Configure each LCD pin based on the selected bit mode */
#if LCD_BIT_MODE_SELECT == LCD_EIGHT_BITS_MODE
    for (loc_iterator_Pins = 0; loc_iterator_Pins < NUMBER_OF_LCD_PINS; loc_iterator_Pins++)
    {
        loc_PORTstrConfig.GPIO_Port = LCD_strCfg[loc_iterator_Pins].port;
        loc_PORTstrConfig.GPIO_Pin = LCD_strCfg[loc_iterator_Pins].pin;
        loc_PORTstrConfig.GPIO_Mode = GPIO_MODE_OUT_PP; /* Make All Data or command Pins as Output */
        loc_PORTstrConfig.GPIO_Speed = GPIO_SPEED_HIGH;
        GPIO_Init(&loc_PORTstrConfig);
    }

#elif LCD_BIT_MODE_SELECT == LCD_FOUR_BITS_MODE
    for (loc_iterator_Pins = NUMBER_OF_CD_PINS; loc_iterator_Pins < 11; loc_iterator_Pins++)
    {
        loc_PORTstrConfig.GPIO_Port = LCD_strCfg[loc_iterator_Pins].port;
        loc_PORTstrConfig.GPIO_Pin = LCD_strCfg[loc_iterator_Pins].pin;
        loc_PORTstrConfig.GPIO_Mode = GPIO_MODE_OUT_PP; /* Make All Data or command Pins as Output */
        loc_PORTstrConfig.GPIO_Speed = GPIO_SPEED_HIGH;
        PORT_setPinConfig(&loc_PORTstrConfig);
    }
#endif /* LCD_BIT_MODE_SELECT */
	LCD_initMode = LCD_initState;
	return loc_LCD_ErrorState;
}

void LCD_Runnable()
{
	switch (LCD_state)
	{
		case LCD_initState:
			LCD_InitStateMachine();
			break;
		case LCD_operationalState:
			if(LCD_UserReq.Req_state == LCD_ReqBusy)
			{
				switch(LCD_UserReq.Req_type)
				{
					case LCD_ReqWtire:
						LCD_writeProc();
						break;
					case LCD_ReqClear:
						LCD_clearProc();
						break;
					case LCD_NoReq:
						break;
				}
			}
			else
			{

			}
			break;
		case LCD_off:
			break;
	}
}

/*Every 2 ms*/
static void LCD_InitStateMachine()
{
	static u8 counts = 0;
	switch(LCD_initMode)
	{
		case LCD_PowerOn:
			counts++;
			if(counts == 15)	/*wait for 30 ms until the power ON*/
			{
				LCD_initMode = LCD_FunctionSet1;
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_LOW;
				LCD_setTriggerEnable(LCD_triggerEnableState);
			}
			break;
		case LCD_FunctionSet1:
#if LCD_BIT_MODE_SELECT == LCD_EIGHT_BITS_MODE
			if(LCD_triggerEnableState == LCD_TRIGGER_ENABLE_LOW)
			{
				LCD_writeCommandAsync(LCD_FUNCTION_SET);
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_HIGH;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_HIGH);
			}
			else
			{
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_LOW;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_LOW);
				LCD_initMode = LCD_DisplayControl;
			}
#elif LCD_BIT_MODE_SELECT == LCD_FOUR_BITS_MODE
			if(LCD_triggerEnableState == LCD_TRIGGER_ENABLE_LOW)
			{
				LCD_writeCommandAsync(LCD_FUNCTION_SET);
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_HIGH;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_HIGH);
			}
			else
			{
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_LOW;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_LOW);
				if(send_higher_nibble)
				{
					LCD_initMode = LCD_FunctionSet2;
				}
			}
#endif /* LCD_BIT_MODE_SELECT */
			break;
#if LCD_BIT_MODE_SELECT == LCD_FOUR_BITS_MODE
		case LCD_FunctionSet2:
			if(LCD_triggerEnableState == LCD_TRIGGER_ENABLE_LOW)
			{
				LCD_writeCommandAsync(LCD_FUNCTION_SET);
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_HIGH;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_HIGH);
			}
			else
			{
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_LOW;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_LOW);
				if(send_higher_nibble)
				{
					LCD_initMode = LCD_DisplayControl;
				}
			}
			break;
#endif
		case LCD_DisplayControl:
#if LCD_BIT_MODE_SELECT == LCD_EIGHT_BITS_MODE
			if(LCD_triggerEnableState == LCD_TRIGGER_ENABLE_LOW)
			{
				LCD_writeCommandAsync(LCD_DISPLAY_CONTROL);
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_HIGH;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_HIGH);
			}
			else
			{
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_LOW;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_LOW);
				LCD_initMode = LCD_ClearDisplay;
			}
#elif LCD_BIT_MODE_SELECT == LCD_FOUR_BITS_MODE
			if(LCD_triggerEnableState == LCD_TRIGGER_ENABLE_LOW)
			{
				LCD_writeCommandAsync(LCD_DISPLAY_CONTROL);
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_HIGH;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_HIGH);
			}
			else
			{
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_LOW;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_LOW);
				if(send_higher_nibble)
				{
					LCD_initMode = LCD_ClearDisplay;
				}
			}
#endif
			break;
		case LCD_ClearDisplay:
#if LCD_BIT_MODE_SELECT == LCD_EIGHT_BITS_MODE
			if(LCD_triggerEnableState == LCD_TRIGGER_ENABLE_LOW)
			{
				LCD_writeCommandAsync(LCD_CLEAR_DISPLAY);
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_HIGH;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_HIGH);
			}
			else
			{
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_LOW;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_LOW);
				LCD_initMode = LCD_EndInit;
			}
#elif LCD_BIT_MODE_SELECT == LCD_FOUR_BITS_MODE
			if(LCD_triggerEnableState == LCD_TRIGGER_ENABLE_LOW)
			{
				LCD_writeCommandAsync(LCD_CLEAR_DISPLAY);
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_HIGH;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_HIGH);
			}
			else
			{
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_LOW;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_LOW);
				if(send_higher_nibble)
				{
					LCD_initMode = LCD_EndInit;
				}
			}
#endif
			break;
		case LCD_EndInit:
			LCD_state = LCD_operationalState;
			break;
	}
}

static void LCD_writeProc()
{
	static u8 pos = 0;
	switch(LCD_writeState)
	{
		case Write_Start:
			LCD_writeState = Write_SetPostion;
			LCD_triggerEnableState = LCD_TRIGGER_ENABLE_LOW;
			LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_LOW);
			break;
		case Write_SetPostion:
			if(LCD_UserReq.x_pos == LCD_CURSOR_FIRST_LINE)
			{
				pos = LCD_UserReq.y_pos;
			}
		    else if (LCD_UserReq.x_pos == LCD_CURSOR_SECOND_LINE)
		    {
		    	pos = LCD_UserReq.y_pos + 0x40;
		    }
		    else if (LCD_UserReq.x_pos == LCD_CURSOR_THIRD_LINE)
		    {
		    	pos = LCD_UserReq.y_pos + 0x10;
		    }
		    else if (LCD_UserReq.x_pos == LCD_CURSOR_FOURTH_LINE)
		    {
		    	pos = LCD_UserReq.y_pos + 0x50;
		    }
		    else
		    {
		    	/*Do Nothing*/
		    }
			pos += LCD_SET_DDRAM_ADDRESS;
#if LCD_BIT_MODE_SELECT == LCD_EIGHT_BITS_MODE
			if(LCD_triggerEnableState == LCD_TRIGGER_ENABLE_LOW)
			{
				LCD_writeCommandAsync(pos);
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_HIGH;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_HIGH);
			}
			else
			{
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_LOW;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_LOW);
				LCD_writeState = Write_Character;
			}
#elif LCD_BIT_MODE_SELECT == LCD_FOUR_BITS_MODE
			if(LCD_triggerEnableState == LCD_TRIGGER_ENABLE_LOW)
			{
				LCD_writeCommandAsync(pos);
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_HIGH;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_HIGH);
			}
			else
			{
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_LOW;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_LOW);
				if(send_higher_nibble)
				{
					LCD_writeState = Write_Character;
				}
			}

#endif
			break;
		case Write_Character:
#if LCD_BIT_MODE_SELECT == LCD_EIGHT_BITS_MODE
			if(remaining_chars > 0)
			{
				if(LCD_triggerEnableState == LCD_TRIGGER_ENABLE_LOW)
				{
					LCD_writeDataAsync(LCD_UserReq.data[LCD_UserReq.data_size- remaining_chars]);
					LCD_triggerEnableState = LCD_TRIGGER_ENABLE_HIGH;
					LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_HIGH);
				}
				else
				{
					LCD_triggerEnableState = LCD_TRIGGER_ENABLE_LOW;
					LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_LOW);
					remaining_chars--;
				}
			}
			else
			{
				LCD_writeState = Write_Done;
			}
#elif LCD_BIT_MODE_SELECT == LCD_FOUR_BITS_MODE
			if(remaining_chars > 0)
			{
				if(LCD_triggerEnableState == LCD_TRIGGER_ENABLE_LOW)
				{
					LCD_writeDataAsync(LCD_UserReq.data[LCD_UserReq.data_size- remaining_chars]);
					LCD_triggerEnableState = LCD_TRIGGER_ENABLE_HIGH;
					LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_HIGH);
				}
				else
				{
					LCD_triggerEnableState = LCD_TRIGGER_ENABLE_LOW;
					LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_LOW);
					remaining_chars--;
				}
			}
			else
			{
				LCD_writeState = Write_Done;
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_LOW;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_LOW);
			}
#endif
			break;
		case Write_Done:
			LCD_UserReq.Req_state = LCD_ReqIdle;
			LCD_UserReq.Req_type = LCD_NoReq;
			break;
	}
}

static void LCD_clearProc()
{
	switch(LCD_clearState)
	{
		case Clear_Start:
			LCD_clearState = Clear_InProgress;
			LCD_triggerEnableState = LCD_TRIGGER_ENABLE_LOW;
			LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_LOW);
			break;
		case Clear_InProgress:
#if LCD_BIT_MODE_SELECT == LCD_EIGHT_BITS_MODE
			if(LCD_triggerEnableState == LCD_TRIGGER_ENABLE_LOW)
			{
				LCD_writeCommandAsync(LCD_CLEAR_DISPLAY);
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_HIGH;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_HIGH);
			}
			else
			{
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_LOW;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_LOW);
				LCD_clearState = Clear_Done;
			}
#elif LCD_BIT_MODE_SELECT == LCD_FOUR_BITS_MODE
			if(LCD_triggerEnableState == LCD_TRIGGER_ENABLE_LOW)
			{
				LCD_writeCommandAsync(LCD_CLEAR_DISPLAY);
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_HIGH;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_HIGH);
			}
			else
			{
				LCD_triggerEnableState = LCD_TRIGGER_ENABLE_LOW;
				LCD_setTriggerEnable(LCD_TRIGGER_ENABLE_LOW);
				if(send_higher_nibble)
				{
					LCD_clearState = Clear_Done;
				}
			}
#endif
			break;
		case Clear_Done:
			LCD_UserReq.Req_state = LCD_ReqIdle;
			LCD_UserReq.Req_type = LCD_NoReq;
			break;
	}

}

static void LCD_setTriggerEnable(u8 value)
{
	GPIO_setPinValue(LCD_strCfg[E].port, LCD_strCfg[E].pin, value);
}

static void LCD_writeCommandAsync(u8 Copy_u8command)
{
	/* Set the LCD in command mode (RS = 0, RW = 0) */
	GPIO_setPinValue(LCD_strCfg[RS].port, LCD_strCfg[RS].pin, LCD_enumLogicLow);
	GPIO_setPinValue(LCD_strCfg[RW].port, LCD_strCfg[RW].pin, LCD_enumLogicLow);
    /* Write the command to the data pins based on the selected bit mode */
#if LCD_BIT_MODE_SELECT == LCD_EIGHT_BITS_MODE
    /* Local variables */
    u8 loc_iterator = 0;
    for (loc_iterator = 0; loc_iterator < NUMBER_OF_CD_PINS; loc_iterator++)
    {
        if (((Copy_u8command >> loc_iterator) & 1) == 1)
        {
        	GPIO_setPinValue(LCD_strCfg[loc_iterator].port, LCD_strCfg[loc_iterator].pin, LCD_enumLogicHigh);
        }
        else
        {
        	GPIO_setPinValue(LCD_strCfg[loc_iterator].port, LCD_strCfg[loc_iterator].pin, LCD_enumLogicLow);
        }
    }

#elif LCD_BIT_MODE_SELECT == LCD_FOUR_BITS_MODE

    if(send_higher_nibble)
    {
    	/* Send the higher nibble of the command */
    	GPIO_setPinValue(LCD_strCfg[DB4].port, LCD_strCfg[DB4].pin, GET_BIT(Copy_u8command, 4));
    	GPIO_setPinValue(LCD_strCfg[DB5].port, LCD_strCfg[DB5].pin, GET_BIT(Copy_u8command, 5));
    	GPIO_setPinValue(LCD_strCfg[DB6].port, LCD_strCfg[DB6].pin, GET_BIT(Copy_u8command, 6));
    	GPIO_setPinValue(LCD_strCfg[DB7].port, LCD_strCfg[DB7].pin, GET_BIT(Copy_u8command, 7));
    }
    else
    {
    	/* Send the lower nibble of the command */
    	GPIO_setPinValue(LCD_strCfg[DB4].port, LCD_strCfg[DB4].pin, GET_BIT(Copy_u8command, 0));
    	GPIO_setPinValue(LCD_strCfg[DB5].port, LCD_strCfg[DB5].pin, GET_BIT(Copy_u8command, 1));
    	GPIO_setPinValue(LCD_strCfg[DB6].port, LCD_strCfg[DB6].pin, GET_BIT(Copy_u8command, 2));
    	GPIO_setPinValue(LCD_strCfg[DB7].port, LCD_strCfg[DB7].pin, GET_BIT(Copy_u8command, 3));
    }

    send_higher_nibble ^= 1;	/*Toggle higher nibble for continuous call*/


#endif /* LCD_BIT_MODE_SELECT */
}

static void LCD_writeDataAsync(u8 Copy_u8data)
{
	/* Set the LCD in command mode (RS = 0, RW = 0) */
	GPIO_setPinValue(LCD_strCfg[RS].port, LCD_strCfg[RS].pin, LCD_enumLogicHigh);
	GPIO_setPinValue(LCD_strCfg[RW].port, LCD_strCfg[RW].pin, LCD_enumLogicLow);
    /* Write the command to the data pins based on the selected bit mode */
#if LCD_BIT_MODE_SELECT == LCD_EIGHT_BITS_MODE
    /* Local variables */
    u8 loc_iterator = 0;
    for (loc_iterator = 0; loc_iterator < NUMBER_OF_CD_PINS; loc_iterator++)
    {
        if (((Copy_u8data >> loc_iterator) & 1) == 1)
        {
        	GPIO_setPinValue(LCD_strCfg[loc_iterator].port, LCD_strCfg[loc_iterator].pin, LCD_enumLogicHigh);
        }
        else
        {
        	GPIO_setPinValue(LCD_strCfg[loc_iterator].port, LCD_strCfg[loc_iterator].pin, LCD_enumLogicLow);
        }
    }

#elif LCD_BIT_MODE_SELECT == LCD_FOUR_BITS_MODE

    if(send_higher_nibble)
    {
    	/* Send the higher nibble of the command */
    	GPIO_setPinValue(LCD_strCfg[DB4].port, LCD_strCfg[DB4].pin, GET_BIT(Copy_u8data, 4));
    	GPIO_setPinValue(LCD_strCfg[DB5].port, LCD_strCfg[DB5].pin, GET_BIT(Copy_u8data, 5));
    	GPIO_setPinValue(LCD_strCfg[DB6].port, LCD_strCfg[DB6].pin, GET_BIT(Copy_u8data, 6));
    	GPIO_setPinValue(LCD_strCfg[DB7].port, LCD_strCfg[DB7].pin, GET_BIT(Copy_u8data, 7));
    }
    else
    {
    	/* Send the lower nibble of the command */
    	GPIO_setPinValue(LCD_strCfg[DB4].port, LCD_strCfg[DB4].pin, GET_BIT(Copy_u8data, 0));
    	GPIO_setPinValue(LCD_strCfg[DB5].port, LCD_strCfg[DB5].pin, GET_BIT(Copy_u8data, 1));
    	GPIO_setPinValue(LCD_strCfg[DB6].port, LCD_strCfg[DB6].pin, GET_BIT(Copy_u8data, 2));
    	GPIO_setPinValue(LCD_strCfg[DB7].port, LCD_strCfg[DB7].pin, GET_BIT(Copy_u8data, 3));
    }

    send_higher_nibble ^= 1;	/*Toggle higher nibble for continuous call*/


#endif /* LCD_BIT_MODE_SELECT */
}
