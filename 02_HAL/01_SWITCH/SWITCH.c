/******************************************************************************
 *
 * Module: Switch
 *
 * File Name: SWITCH.c
 *
 * Description: Source file for the SWITCH driver for STM32F401xC
 *
 * Author: Momen Elsayed Shaban
 *
 *******************************************************************************/
#include "GPIO.h"
#include "SWITCH.h"


extern const SWITCH_Cfg_t Switches[_SWITCH_NUM];

SWITCH_ErrorStatus_t SWITCH_Init()
{
    SWITCH_ErrorStatus_t Error_Status = SWITCH_OK;
    GPIO_Pin_t Switch;
    u8 iterator;
    for(iterator = 0; iterator < _SWITCH_NUM; iterator++)
    {
        if(!(Switches[iterator].dir == SWITCH_PULL_UP || Switches[iterator].dir == SWITCH_PULL_DOWN))
        {
            Error_Status = SWITCH_InvalidDir;
        }
        else
        {
            Switch.GPIO_Pin = Switches[iterator].pin;
            Switch.GPIO_Port = Switches[iterator].port;
            Switch.GPIO_Mode = Switches[iterator].dir;
            GPIO_Init(&Switch);
        }
    }
    return Error_Status;
}

SWITCH_ErrorStatus_t SWITCH_getState(u32 Switch_Name,u8* Switch_state)
{
    SWITCH_ErrorStatus_t Error_Status = SWITCH_OK;
    u8 pin_state = 0;
    if(Switch_Name > _SWITCH_NUM)
    {
        Error_Status = SWITCH_InvalidName;
    }
    else if(Switch_state == NULL_PTR)
    {
        Error_Status = SWITCH_NullPtr;
    }
    else{
        GPIO_getPinValue(Switches[Switch_Name].port ,Switches[Switch_Name].pin ,&pin_state);
        /*Shifting by 3 because it is the position of pull-up and pull-down bits in the defined value*/
        *Switch_state = (pin_state ^ (Switches[Switch_Name].dir >> 3U));  
    }
    return Error_Status;
}
