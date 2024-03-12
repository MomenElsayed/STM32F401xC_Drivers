/*
 * TrafficLight.c
 *
 *  Created on: 12 Mar 2024
 *      Author: Momen El Sayed
 */
#include "LED.h"

#define PERIODICITY_SEC		1
u8 prev;
void greenOn (void)
{
	LED_setState(LED_Green, LED_STATE_ON);
	LED_setState(LED_Yellow, LED_STATE_OFF);
	LED_setState(LED_Red, LED_STATE_OFF);
}

void yellowOn (void)
{
	LED_setState(LED_Green, LED_STATE_OFF);
	LED_setState(LED_Yellow, LED_STATE_ON);
	LED_setState(LED_Red, LED_STATE_OFF);
}

void redOn (void)
{
	LED_setState(LED_Green, LED_STATE_OFF);
	LED_setState(LED_Yellow, LED_STATE_OFF);
	LED_setState(LED_Red, LED_STATE_ON);
}

enum{
	green,
	yellow,
	red
}light;

/*every 1 Second*/
/*Green 5 seconds, yellow 2 second, red 3 seconds*/
void trafficLight (void)
{
	static u32 seconds = 0;
	seconds += PERIODICITY_SEC;
	switch(light)
	{
	case green:
		greenOn();
		if(seconds == 5)
		{
			seconds = 0;
			light = yellow;
			prev = green;
		}
		break;
	case yellow:
		yellowOn();
		if((seconds == 2) && (prev == green))
		{
			seconds = 0;
			light = red;
			prev = yellow;
		}
		else if((seconds == 2) && (prev == red))
		{
			seconds = 0;
			light = green;
			prev = yellow;
		}
		break;
	case red:
		redOn();
		if(seconds == 3)
		{
			seconds = 0;
			light = yellow;
			prev = red;
		}
		break;
	}

}
