/******************************************************************************
 *
 * Module: LED
 *
 * File Name: LED.c
 *
 * Description: Source file for the LED driver for STM32F401xC
 *
 * Author: Momen Elsayed Shaban
 *
 *******************************************************************************/
#include "GPIO.h"
#include "LED.h"

extern const LED_Cfg_t LEDS[_LEDS_NUM];


LED_ErrorStatus_t LED_Init()
{
    LED_ErrorStatus_t Error_Status = LED_OK;
    u8 iterator = 0;
    GPIO_Pin_t Led;
    Led.GPIO_Mode = GPIO_MODE_OUT_PP;
    Led.GPIO_Speed = GPIO_SPEED_MED;
    for(iterator = 0 ; iterator < _LEDS_NUM ; iterator++)
    {
        if(LEDS[iterator].dir > LED_DIR_REVERSE)        /*Pin and Port Will be Checked in GPIO Driver*/
        {
            Error_Status = LED_InvalidDir;
        }
        else{
            Led.GPIO_Pin = LEDS[iterator].pin;
            Led.GPIO_Port = LEDS[iterator].port;
            GPIO_Init(&Led);
        }      
    }
    return Error_Status;    
}

LED_ErrorStatus_t LED_setState(u32 LedName, u8 Led_state)
{
    LED_ErrorStatus_t Error_Status = LED_OK;
    if(LedName > _LEDS_NUM)
    {
        Error_Status = LED_InvalidLedName;
    }
    else if (Led_state > LED_STATE_ON)
    {
        Error_Status = LED_InvalidState;
    }
    else
    {
         /*Using Xor will give the corresponding value based on the dir*/ 
        GPIO_setPinValue(LEDS[LedName].port,LEDS[LedName].pin, (LEDS[LedName].dir ^ Led_state));   
    }
    return Error_Status;
}

LED_ErrorStatus_t LED_toggle(u32 LedName)
{
	LED_ErrorStatus_t Error_Status = LED_OK;
	u8 led_state = 0;
	if(LedName > _LEDS_NUM)
	{
	    Error_Status = LED_InvalidLedName;
	}
	else
	{
		GPIO_getPinValue(LEDS[LedName].port, LEDS[LedName].pin, &led_state);
		GPIO_setPinValue(LEDS[LedName].port, LEDS[LedName].pin, led_state ^ 1);
	}
    return Error_Status;

}
