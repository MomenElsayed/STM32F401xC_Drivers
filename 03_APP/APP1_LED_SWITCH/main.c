#include "RCC.h"
#include "LED.h"
#include "SWITCH.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int main(int argc, char* argv[])
{
  RCC_setClkON(RCC_HSE_ON);
  RCC_cfgPLLClk(15,144,5,4);
  RCC_setPLLClkSrc(RCC_PLL_CLK_HSE);
  RCC_setClkON(RCC_HSE_ON);
  RCC_Set_AHB1_Prescaler(RCC_AHB_PRESCALER_2);	/*HClK = 30 MHz*/
  RCC_setSystemClk(RCC_SYSCLK_PLL);		/*SysClk = 60 MHz*/
  RCC_Ctrl_AHB1_Clk(RCC_GPIOA_ENABLE_DISABLE,RCC_enuPeriphralEnable);
  LED_Init();
  SWITCH_Init();
  u8 state = SWITCH_RELEASED;
  while (1)
    { 
      SWITCH_getState(SWITCH_Fire,&state);
      if(state == SWITCH_PRESSED)
      {
        LED_setState(LED_Alarm,LED_STATE_ON);
      }
      else
      {
        LED_setState(LED_Alarm,LED_STATE_OFF);
      }

    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
