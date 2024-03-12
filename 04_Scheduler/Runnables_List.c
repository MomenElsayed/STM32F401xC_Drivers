/*
 * Runnables_List.c
 *
 *  Created on: 11 Mar 2024
 *      Author: Momen El Sayed
 */

#include "Runnables_List.h"
#include "sched.h"

extern void Runnable_APP1(void);
extern void Runnable_APP2(void);
extern void SW_Runnable(void);
extern void trafficLight(void);


const runnable_t Runnables_List[_Runnables_Num] =
{
        [APP1] = {
            .name = "Toggle Led For 1 Second",
            .periodicityMS = 1000,
            .callBackFn = &Runnable_APP1
        },
        [Switches_Run] = {
        	.name = "Get Switch Status",
        	.periodicityMS = 50,
			.callBackFn = &SW_Runnable
        },
        [APP2] = {
        	.name = "Control Led With Switch",
			.periodicityMS = 50,
			.callBackFn = &Runnable_APP2
        },
		[trafficLightAPP] = {
		    .name = "Traffic Light",
			.periodicityMS = 1000,
			.callBackFn = &trafficLight
		}
};

