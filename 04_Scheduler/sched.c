/*
 * sched.c
 *
 *  Created on: 11 Mar 2024
 *      Author: Momen El Sayed
 */

#include "RCC.h"
#include "SYSTICK.h"
#include "sched.h"
#include "Runnables_List.h"

#define SCHED_TICK_TIME_MS 10


static volatile u32 pendingTicks = 0;

extern const runnable_t Runnables_List[_Runnables_Num];

static void Sched()
{
	u32 iterator = 0;
	static u32 timeStamp = 0;
	for(iterator = 0 ; iterator < _Runnables_Num;iterator++)
	{
		if((Runnables_List[iterator].callBackFn) && ((timeStamp % Runnables_List[iterator].periodicityMS) == 0))
		{
			Runnables_List[iterator].callBackFn();
		}
	}
	timeStamp+= SCHED_TICK_TIME_MS;
}

void Sched_TickCallBack(void)
{
	pendingTicks++;
}

void Sched_Init()
{
	SYSTICK_setTimeMS(SCHED_TICK_TIME_MS);
	SYSTICK_setCallBack(Sched_TickCallBack, 0);
}

void Sched_Start()
{
	SYSTICK_start(SYSTICK_CLK_AHB);
	while(1)
	{
		if(pendingTicks)
		{
			pendingTicks--;
			Sched();
		}
	}
}


