#include "RCC.h"
#include "NVIC.h"
#include "SYSTICK.h"
#include "LCD.h"
#include "sched.h"


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"


int main(int argc, char* argv[])
{
	RCC_Ctrl_AHB1_Clk(RCC_GPIOA_ENABLE_DISABLE,RCC_enuPeriphralEnable);
	LCD_InitAsync();
	Sched_Init();
	Sched_Start();
}

#pragma GCC diagnostic pop


