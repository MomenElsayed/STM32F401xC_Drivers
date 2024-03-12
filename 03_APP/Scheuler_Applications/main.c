#include "RCC.h"
#include "NVIC.h"
#include "SYSTICK.h"
#include "LED.h"
#include "sched.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"


int main(int argc, char* argv[])
{
	RCC_Ctrl_AHB1_Clk(RCC_GPIOA_ENABLE_DISABLE,RCC_enuPeriphralEnable);
	SWITCH_Init();
	LED_Init();
	Sched_Init();
	Sched_Start();
}

#pragma GCC diagnostic pop


