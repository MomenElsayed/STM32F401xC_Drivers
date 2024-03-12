/*
 * App2.c
 *
 *  Created on: 12 Mar 2024
 *      Author: Momen El Sayed
 */

#include "LED.h"
#include "SWITCH.h"

void Runnable_APP2(void)
{
	SWITCH_Init();
	LED_Init();
    u8 switchStatus = SWITCH_RELEASED;
    SWITCH_getState(SWITCH_Fire, &switchStatus);
    if (switchStatus == SWITCH_PRESSED)
    {
        LED_setState(LED_Alarm, LED_STATE_ON);
    }
    else
    {
        LED_setState(LED_Alarm, LED_STATE_OFF);
    }
}
