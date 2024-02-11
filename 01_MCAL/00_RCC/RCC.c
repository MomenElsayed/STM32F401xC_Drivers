/******************************************************************************
 *
 * Module: RCC
 *
 * File Name: RCC.c
 *
 * Description: Source file for the RCC driver Configurations for STM32F401xC
 *
 * Author: Momen Elsayed Shaban
 *
 *******************************************************************************/
#include "RCC.h"
#include "bitmath.h"
#include "STM32F401xC_registers.h"

/*****************************************************
 * Function: RCC_setClk
 * Description: Sets the system clock source based on
 * the provided RCC_enuClk_t parameter.
 *
 * Parameters:
 *   - RCC_clk: An enumeration representing the desired
 *   clock source (e.g., HSI, HSE, PLL, etc.).
 *
 * Return:
 *   - RCC_enuErrorState_t: An error state indicating the
 *   success or failure of the clock setting.
 *
 * Errors:
 *   - RCC_enuInvalidClk: Returned if an invalid clock option is provided.
 *   - RCC_enuOK: Returned if the clock setting is successful.
 *
 * Usage: RCC_enuErrorState_t error = RCC_setClk(RCC_enuHSE_bypass);
 * Example: Set the system clock source to HSE with bypass
 *
 * Notes:
 *   - The function supports various clock sources such
 *   as HSI, HSE (crystal and bypass), PLL, and PLLI2S.
 *****************************************************/
RCC_enuErrorState_t RCC_setClk(RCC_enuClk_t RCC_clk)
{
	RCC_enuErrorState_t RCC_ErrorState = RCC_enuOK;
	if (RCC_clk > RCC_enuPLL)
	{
		RCC_ErrorState = RCC_enuInvalidClk;
	}
	else
	{
		/*Do Nothing*/
	}
	if (RCC_ErrorState == RCC_enuOK)
	{
		switch(RCC_clk)
		{
			case RCC_enuHSI:
				SET_BIT(RCC_CR,RCC_CR_HSION);
				break;
			case RCC_enuHSE_crystal:
				SET_BIT(RCC_CR,RCC_CR_HSEON);		/*It enable HSE in Crystal mode only*/
				break;
			case RCC_enuHSE_bypass:
				SET_BIT(RCC_CR,RCC_CR_HSEON);
				SET_BIT(RCC_CR,RCC_CR_HSEBYP);
				break;
			case RCC_enuPLL:
				SET_BIT(RCC_CR,RCC_CR_PLLON);
				break;
			case RCC_enuPLLI2S:
				SET_BIT(RCC_CR,RCC_CR_PLLI2SON);
				break;
			default:
				/*Do Nothing*/
				break;
		}
	}
	return RCC_ErrorState;
}

/*****************************************************
 * Function: RCC_setPLLClkCfg
 * Description: Configures the PLL (Phase-Locked Loop) settings
 * based on the provided clock source and frequency.
 *
 * Parameters:
 *   - RCC_clkSrc: An enumeration representing the clock source
 *    for PLL configuration (e.g., HSI, HSE).
 *   - RCC_clkFreq: An enumeration representing the supported
 *    frequencies for PLL configuration.
 *
 * Return:
 *   - RCC_enuErrorState_t: An error state indicating the success
 *    or failure of the PLL configuration.
 *
 * Errors:
 *   - RCC_enuInvalidClkSrcForPLL: Returned if an invalid clock
 *    source is provided for PLL configuration.
 *   - RCC_enuNotSupportedFreq: Returned if the specified frequency
 *    is not supported for PLL configuration.
 *   - RCC_enuPLLisONwhileCfg: Returned if the PLL is already enabled
 *    while configuring its settings.
 *   - RCC_enuOK: Returned if the PLL configuration is successful.
 *
 * Supported Frequencies:
 *   - RCC_enu48Mhz: 48 MHz
 *   - RCC_enu54Mhz: 54 MHz
 *   - RCC_enu64Mhz: 64 MHz
 *   - RCC_enu84Mhz: 84 MHz
 *
 * Usage: RCC_enuErrorState_t error = RCC_setPLLClkCfg(RCC_enuHSE, RCC_enu64Mhz);
 *  Example: Configure PLL with HSE and 64 MHz frequency
 *
 * Notes:
 *   - The function supports PLL configuration with HSI, HSE as the clock source.
 *   - The PLL settings are based on predefined values for M, N, P, and Q for different frequencies.
 *****************************************************/
RCC_enuErrorState_t RCC_setPLLClkCfg(RCC_enuClk_t RCC_clkSrc,RCC_enuFreqSupported_t RCC_clkFreq)
{
	RCC_enuErrorState_t RCC_ErrorState = RCC_enuOK;
	u16 loc_temp_RCC_PLLCFGR = 0;
	u8 PLL_HSI_M[NUMBER_OF_SUPPORTED_FREQS] = {9 ,8 ,8 ,10};
	u16 PLL_HSI_N[NUMBER_OF_SUPPORTED_FREQS] = {216 ,216 , 192, 210};
	u8 PLL_HSI_P[NUMBER_OF_SUPPORTED_FREQS] = {8 ,8 , 6, 4};
	u8 PLL_HSI_Q[NUMBER_OF_SUPPORTED_FREQS] = {8 ,9 , 8, 7};
	u8 PLL_HSE_M = 25;
	u16 PLL_HSE_N[NUMBER_OF_SUPPORTED_FREQS]={192 ,432 , 384, 336};
	u8 PLL_HSE_P[NUMBER_OF_SUPPORTED_FREQS]={4 ,8 ,6 , 4};
	u8 PLL_HSE_Q[NUMBER_OF_SUPPORTED_FREQS]={4 ,9 , 8, 7};
	if(RCC_clkSrc > RCC_enuHSE_crystal)
	{
		RCC_ErrorState = RCC_enuInvalidClkSrcForPLL;
	}
	else if (RCC_clkFreq > RCC_enu84Mhz)
	{
		RCC_ErrorState = RCC_enuNotSupportedFreq;
	}
	else if (BIT_IS_SET(RCC_CR,RCC_CR_PLLON))				/*Check if PLL is on or not*/
	{
		RCC_ErrorState = RCC_enuPLLisONwhileCfg;
	}
	else
	{
		/*Do Nothing*/
	}
	if(RCC_ErrorState == RCC_enuOK)
	{
		loc_temp_RCC_PLLCFGR = RCC_PLLCFGR;		/*Save the Value of the register in case of any interrupt during this function*/
		loc_temp_RCC_PLLCFGR = 0;				/*Reset all the values of the register*/
		if(RCC_clkSrc == RCC_enuHSI)
		{
			CLEAR_BIT(RCC_PLLCFGR,RCC_PLLCFGR_PLLSRC);
			loc_temp_RCC_PLLCFGR |= (PLL_HSI_M[RCC_clkFreq] << RCC_PLLCFGR_PLLM);
			loc_temp_RCC_PLLCFGR |= (PLL_HSI_N[RCC_clkFreq] << RCC_PLLCFGR_PLLN);
			loc_temp_RCC_PLLCFGR |= (PLL_HSI_P[RCC_clkFreq] << RCC_PLLCFGR_PLLP);
			loc_temp_RCC_PLLCFGR |= (PLL_HSI_Q[RCC_clkFreq] << RCC_PLLCFGR_PLLQ);
		}
		else if((RCC_clkSrc == RCC_enuHSE_bypass) || (RCC_clkSrc == RCC_enuHSE_crystal))
		{
			SET_BIT(RCC_PLLCFGR,RCC_PLLCFGR_PLLSRC);
			loc_temp_RCC_PLLCFGR |= (PLL_HSE_M << RCC_PLLCFGR_PLLM);
			loc_temp_RCC_PLLCFGR |= (PLL_HSE_N[RCC_clkFreq] << RCC_PLLCFGR_PLLN);
			loc_temp_RCC_PLLCFGR |= (PLL_HSE_P[RCC_clkFreq] << RCC_PLLCFGR_PLLP);
			loc_temp_RCC_PLLCFGR |= (PLL_HSE_Q[RCC_clkFreq] << RCC_PLLCFGR_PLLQ);
		}
		RCC_PLLCFGR = loc_temp_RCC_PLLCFGR;
	}
	return RCC_ErrorState;
}

/*****************************************************
 * Function: RCC_setSystemClk
 * Description: Sets the system clock source based on the
 * provided RCC_enuSysClk_t parameter.
 *
 * Parameters:
 *   - RCC_SysclkSrc: An enumeration representing the
 *   desired system clock source (e.g., HSI, HSE, PLL).
 *
 * Return:
 *   - RCC_enuErrorState_t: An error state indicating the success
 *    or failure of the system clock setting.
 *
 * Errors:
 *   - RCC_enuInvalidSysClk: Returned if an invalid system clock
 *   source is provided.
 *   - RCC_enuOK: Returned if the system clock setting is successful.
 *
 * Usage: RCC_enuErrorState_t error = RCC_setSystemClk(RCC_enuSysPLL);
 * Example: Set the system clock source to PLL
 *
 * Notes:
 *   - The function supports various system clock sources such as HSI, HSE, and PLL.
 *   - The RCC_CFGR register is updated to reflect the selected system clock source.
 *****************************************************/
RCC_enuErrorState_t RCC_setSystemClk(RCC_enuSysClk_t RCC_SysclkSrc)
{
	RCC_enuErrorState_t RCC_ErrorState = RCC_enuOK;
	switch(RCC_SysclkSrc)
	{
	case RCC_enuSysHSI:
		RCC_CFGR |= RCC_enuSysHSI;
		break;
	case RCC_enuSysHSE:
		RCC_CFGR |= RCC_enuSysHSE;
		break;
	case RCC_enuSysPLL:
		RCC_CFGR |= RCC_enuSysPLL;
		break;
	default:
		RCC_ErrorState = RCC_enuInvalidSysClk;
		break;
	}
	return RCC_ErrorState;
}

/*****************************************************
 * Function: RCC_Set_AHB1_Prescaler
 * Description: Sets the AHB1 (Advanced High-Performance Bus 1)
 * prescaler based on the provided value.
 *
 * Parameters:
 *   - Copy_AHB1_Prescaler: An 8-bit value representing the AHB1
 *    prescaler configuration.
 *
 * Return:
 *   - RCC_enuErrorState_t: An error state indicating the success or
 *   failure of the AHB1 prescaler setting.
 *
 * Errors:
 *   - RCC_enuInvalidPrescaler: Returned if an invalid AHB1 prescaler value is provided.
 *   - RCC_enuOK: Returned if the AHB1 prescaler setting is successful.
 *
 * Prescaler Values:
 *   - RCC_AHB_PRESCALER_NONE: No prescaling (1:1)
 *   - RCC_AHB_PRESCALER_2: Prescale by 2 (2:1)
 *   - RCC_AHB_PRESCALER_4: Prescale by 4 (4:1)
 *   - RCC_AHB_PRESCALER_8: Prescale by 8 (8:1)
 *   - RCC_AHB_PRESCALER_16: Prescale by 16 (16:1)
 *   - RCC_AHB_PRESCALER_64: Prescale by 64 (64:1)
 *   - RCC_AHB_PRESCALER_128: Prescale by 128 (128:1)
 *   - RCC_AHB_PRESCALER_256: Prescale by 256 (256:1)
 *   - RCC_AHB_PRESCALER_512: Prescale by 512 (512:1)
 *
 * Usage: RCC_enuErrorState_t error = RCC_Set_AHB1_Prescaler(RCC_AHB_PRESCALER_4);
 * Example: Set AHB1 prescaler to 4
 *
 * Notes:
 *   - The function sets the AHB1 prescaler value in the RCC_CFGR register.
 *****************************************************/
RCC_enuErrorState_t RCC_Set_AHB1_Prescaler(u8 Copy_AHB1_Prescaler)
{
	RCC_enuErrorState_t RCC_ErrorState = RCC_enuOK;
	if(Copy_AHB1_Prescaler > RCC_AHB_PRESCALER_512)	/*Condition Is not totally right because some numbers in the middle falls*/
	{
		RCC_ErrorState = RCC_enuInvalidPrescaler;
	}
	else
	{
		/*Do Nothing*/
	}
	if(RCC_ErrorState == RCC_enuOK)
	{
		RCC_CFGR |= (Copy_AHB1_Prescaler << RCC_CFGR_HPRE);
	}
	else
	{
		/*Do Nothing*/
	}
	return RCC_ErrorState;
}

/*****************************************************
 * Function: RCC_Ctrl_AHB1_Clk
 * Description: Controls the clock for AHB1 peripherals based
 *  on the provided peripheral and mode.
 *
 * Parameters:
 *   - Copy_u32Periphral: A 32-bit value representing the AHB1
 *   peripheral(s) to be enabled or disabled.
 *   - RCC_enuPeriphralMode: An enumeration representing the desired
 *    mode (enable or disable) for the specified peripheral(s).
 *
 * Return:
 *   - RCC_enuErrorState_t: An error state indicating the success
 *    or failure of the AHB1 peripheral control operation.
 *
 * Errors:
 *   - RCC_enuInvalidPeriphralMode: Returned if an invalid peripheral mode is provided.
 *   - RCC_enuOK: Returned if the AHB1 peripheral control operation is successful.
 *
 * AHB1 Peripheral Definitions:
 *   - RCC_GPIOA_ENABLE_DISABLE: GPIOA Peripheral Enable/Disable
 *   - RCC_GPIOB_ENABLE_DISABLE: GPIOB Peripheral Enable/Disable
 *   - RCC_GPIOC_ENABLE_DISABLE: GPIOC Peripheral Enable/Disable
 *   - RCC_GPIOD_ENABLE_DISABLE: GPIOD Peripheral Enable/Disable
 *   - RCC_GPIOE_ENABLE_DISABLE: GPIOE Peripheral Enable/Disable
 *   - RCC_GPIOH_ENABLE_DISABLE: GPIOH Peripheral Enable/Disable
 *   - RCC_CRCRST_ENABLE_DISABLE: CRC Peripheral Enable/Disable
 *   - RCC_DMA1_ENABLE_DISABLE: DMA1 Peripheral Enable/Disable
 *   - RCC_DMA2_ENABLE_DISABLE: DMA2 Peripheral Enable/Disable
 *
 * Peripheral Mode:
 *   - RCC_enuPeriphralEnable: Enable the specified AHB1 peripheral(s).
 *   - RCC_enuPeriphralDisable: Disable the specified AHB1 peripheral(s).
 *
 * Usage: RCC_enuErrorState_t error = RCC_Ctrl_AHB1_Clk(RCC_GPIOA_ENABLE_DISABLE, RCC_enuPeriphralEnable);
 *
 * Notes:
 *   - The function sets or clears bits in the RCC_AHB1RSTR register based on the specified mode and peripheral.
 *****************************************************/
RCC_enuErrorState_t RCC_Ctrl_AHB1_Clk(u32 Copy_u32Periphral, RCC_enuPeriphralMode_t RCC_enuPeriphralMode)
{
	RCC_enuErrorState_t RCC_ErrorState = RCC_enuOK;
	if (RCC_enuPeriphralMode == RCC_enuPeriphralEnable)
	{
		RCC_AHB1RSTR |= Copy_u32Periphral;
	}
	else if (RCC_enuPeriphralMode == RCC_enuPeriphralDisable)
	{
		RCC_AHB1RSTR &= ~Copy_u32Periphral;
	}
	else
	{
		RCC_ErrorState = RCC_enuInvalidPeriphralMode;
	}
	return RCC_ErrorState;
}

/*****************************************************
 * Function: RCC_Ctrl_AHB2_Clk
 * Description: Controls the clock for AHB2 peripherals based
 *  on the provided peripheral and mode.
 *
 * Parameters:
 *   - Copy_u32Periphral: A 32-bit value representing the AHB2
 *   peripheral(s) to be enabled or disabled.
 *   - RCC_enuPeriphralMode: An enumeration representing the
 *   desired mode (enable or disable) for the specified peripheral(s).
 *
 * Return:
 *   - RCC_enuErrorState_t: An error state indicating the success
 *   or failure of the AHB2 peripheral control operation.
 *
 * Errors:
 *   - RCC_enuInvalidPeriphralMode: Returned if an invalid peripheral mode is provided.
 *   - RCC_enuOK: Returned if the AHB2 peripheral control operation is successful.
 *
 * AHB2 Peripheral Definitions:
 *   - RCC_OTGFS_ENABLE_DISABLE: OTG FS (On-The-Go Full Speed) Peripheral Enable/Disable
 *
 * Peripheral Mode:
 *   - RCC_enuPeriphralEnable: Enable the specified AHB2 peripheral(s).
 *   - RCC_enuPeriphralDisable: Disable the specified AHB2 peripheral(s).
 *
 * Usage: RCC_enuErrorState_t error = RCC_Ctrl_AHB2_Clk(RCC_OTGFS_ENABLE_DISABLE, RCC_enuPeriphralEnable);
 *
 * Notes:
 *   - Ensure that the RCC_AHB2RSTR register is properly defined in the codebase.
 *   - The function sets or clears bits in the RCC_AHB2RSTR register based on the specified mode and peripheral.
 *****************************************************/
RCC_enuErrorState_t RCC_Ctrl_AHB2_Clk(u32 Copy_u32Periphral, RCC_enuPeriphralMode_t RCC_enuPeriphralMode)
{
	RCC_enuErrorState_t RCC_ErrorState = RCC_enuOK;
	if (RCC_enuPeriphralMode == RCC_enuPeriphralEnable)
	{
		RCC_AHB2RSTR |= Copy_u32Periphral;
	}
	else if (RCC_enuPeriphralMode == RCC_enuPeriphralDisable)
	{
		RCC_AHB2RSTR &= ~Copy_u32Periphral;
	}
	else
	{
		RCC_ErrorState = RCC_enuInvalidPeriphralMode;
	}
	return RCC_ErrorState;
}

/*****************************************************
 * Function: RCC_Set_APB1_Prescaler
 * Description: Sets the APB1 (Advanced Peripheral Bus 1)
 * prescaler based on the provided value.
 *
 * Parameters:
 *   - Copy_APB1_Prescaler: An 8-bit value representing the
 *   APB1 prescaler configuration.
 *
 * Return:
 *   - RCC_enuErrorState_t: An error state indicating the success
 *   or failure of the APB1 prescaler setting.
 *
 * Errors:
 *   - RCC_enuInvalidPrescaler: Returned if an invalid APB1 prescaler value is provided.
 *   - RCC_enuOK: Returned if the APB1 prescaler setting is successful.
 *
 * APB1 Prescaler Values:
 *   - RCC_APB1_PRESCALER_NONE: No prescaling (1:1)
 *   - RCC_APB1_PRESCALER_2: Prescale by 2 (2:1)
 *   - RCC_APB1_PRESCALER_4: Prescale by 4 (4:1)
 *   - RCC_APB1_PRESCALER_8: Prescale by 8 (8:1)
 *   - RCC_APB1_PRESCALER_16: Prescale by 16 (16:1)
 *
 * Usage: RCC_enuErrorState_t error = RCC_Set_APB1_Prescaler(RCC_APB1_PRESCALER_4);
 * Example: Set APB1 prescaler to 4
 *
 * Notes:
 *   - The function sets the APB1 prescaler value in the RCC_CFGR register.
 *****************************************************/
RCC_enuErrorState_t RCC_Set_APB1_Prescaler(u8 Copy_APB1_Prescaler)
{
	RCC_enuErrorState_t RCC_ErrorState = RCC_enuOK;
	if(Copy_APB1_Prescaler > RCC_APB1_PRESCALER_16)	/*Condition Is not totally right because some numbers in the middle falls*/
	{
		RCC_ErrorState = RCC_enuInvalidPrescaler;
	}
	else
	{
		/*Do Nothing*/
	}
	if(RCC_ErrorState == RCC_enuOK)
	{
		RCC_CFGR |= (Copy_APB1_Prescaler << RCC_CFGR_PPRE1);
	}
	else
	{
		/*Do Nothing*/
	}
	return RCC_ErrorState;
}

/*****************************************************
 * Function: RCC_Ctrl_APB1_Clk
 * Description: Controls the clock for APB1 (Advanced Peripheral Bus 1)
 * peripherals based on the provided peripheral and mode.
 *
 * Parameters:
 *   - Copy_u32Periphral: A 32-bit value representing the APB1 peripheral(s)
 *    to be enabled or disabled.
 *   - RCC_enuPeriphralMode: An enumeration representing the desired mode
 *   (enable or disable) for the specified peripheral(s).
 *
 * Return:
 *   - RCC_enuErrorState_t: An error state indicating the success or failure
 *    of the APB1 peripheral control operation.
 *
 * Errors:
 *   - RCC_enuInvalidPeriphralMode: Returned if an invalid peripheral mode is provided.
 *   - RCC_enuOK: Returned if the APB1 peripheral control operation is successful.
 *
 * APB1 Peripheral Definitions:
 *   - RCC_TIM2_ENABLE_DISABLE: TIM2 Peripheral Enable/Disable
 *   - RCC_TIM3_ENABLE_DISABLE: TIM3 Peripheral Enable/Disable
 *   - RCC_TIM4_ENABLE_DISABLE: TIM4 Peripheral Enable/Disable
 *   - RCC_TIM5_ENABLE_DISABLE: TIM5 Peripheral Enable/Disable
 *   - RCC_WWDG_ENABLE_DISABLE: WWDG Peripheral Enable/Disable
 *   - RCC_SPI2_ENABLE_DISABLE: SPI2 Peripheral Enable/Disable
 *   - RCC_SPI3_ENABLE_DISABLE: SPI3 Peripheral Enable/Disable
 *   - RCC_USART2_ENABLE_DISABLE: USART2 Peripheral Enable/Disable
 *   - RCC_I2C1_ENABLE_DISABLE: I2C1 Peripheral Enable/Disable
 *   - RCC_I2C2_ENABLE_DISABLE: I2C2 Peripheral Enable/Disable
 *   - RCC_I2C3_ENABLE_DISABLE: I2C3 Peripheral Enable/Disable
 *   - RCC_PWR_ENABLE_DISABLE: Power Control Peripheral Enable/Disable
 *
 * Peripheral Mode:
 *   - RCC_enuPeriphralEnable: Enable the specified APB1 peripheral(s).
 *   - RCC_enuPeriphralDisable: Disable the specified APB1 peripheral(s).
 *
 * Usage: RCC_enuErrorState_t error = RCC_Ctrl_APB1_Clk(RCC_TIM2_ENABLE_DISABLE, RCC_enuPeriphralEnable);
 *
 * Notes:
 *   - The function sets or clears bits in the RCC_APB1RSTR register based on the specified mode and peripheral.
 *****************************************************/
RCC_enuErrorState_t RCC_Ctrl_APB1_Clk(u32 Copy_u32Periphral, RCC_enuPeriphralMode_t RCC_enuPeriphralMode)
{
	RCC_enuErrorState_t RCC_ErrorState = RCC_enuOK;
	if (RCC_enuPeriphralMode == RCC_enuPeriphralEnable)
	{
		RCC_APB1RSTR |= Copy_u32Periphral;
	}
	else if (RCC_enuPeriphralMode == RCC_enuPeriphralDisable)
	{
		RCC_APB1RSTR &= ~Copy_u32Periphral;
	}
	else
	{
		RCC_ErrorState = RCC_enuInvalidPeriphralMode;
	}
	return RCC_ErrorState;
}

/*****************************************************
 * Function: RCC_Set_APB2_Prescaler
 * Description: Sets the APB2 (Advanced Peripheral Bus 2) prescaler
 *  based on the provided value.
 *
 * Parameters:
 *   - Copy_APB2_Prescaler: An 8-bit value representing the APB2
 *   prescaler configuration.
 *
 * Return:
 *   - RCC_enuErrorState_t: An error state indicating the success
 *   or failure of the APB2 prescaler setting.
 *
 * Errors:
 *   - RCC_enuInvalidPrescaler: Returned if an invalid APB2 prescaler
 *   value is provided.
 *   - RCC_enuOK: Returned if the APB2 prescaler setting is successful.
 *
 * APB2 Prescaler Values:
 *   - RCC_APB2_PRESCALER_NONE: No prescaling (1:1)
 *   - RCC_APB2_PRESCALER_2: Prescale by 2 (2:1)
 *   - RCC_APB2_PRESCALER_4: Prescale by 4 (4:1)
 *   - RCC_APB2_PRESCALER_8: Prescale by 8 (8:1)
 *   - RCC_APB2_PRESCALER_16: Prescale by 16 (16:1)
 *
 * Usage: RCC_enuErrorState_t error = RCC_Set_APB2_Prescaler(RCC_APB2_PRESCALER_4);
 * Example: Set APB2 prescaler to 4
 *
 * Notes:
 *   - The function sets the APB2 prescaler value in the RCC_CFGR register.
 *****************************************************/
RCC_enuErrorState_t RCC_Set_APB2_Prescaler(u8 Copy_APB2_Prescaler)
{
	RCC_enuErrorState_t RCC_ErrorState = RCC_enuOK;
	if(Copy_APB2_Prescaler > RCC_APB2_PRESCALER_16)	/*Condition Is not totally right because some numbers in the middle falls*/
	{
		RCC_ErrorState = RCC_enuInvalidPrescaler;
	}
	else
	{
		/*Do Nothing*/
	}
	if(RCC_ErrorState == RCC_enuOK)
	{
		RCC_CFGR |= (Copy_APB2_Prescaler << RCC_CFGR_PPRE2);
	}
	else
	{
		/*Do Nothing*/
	}
	return RCC_ErrorState;
}

/*****************************************************
 * Function: RCC_Ctrl_APB2_Clk
 * Description: Controls the clock for APB2 (Advanced Peripheral Bus 2)
 * peripherals based on the provided peripheral and mode.
 *
 * Parameters:
 *   - Copy_u32Periphral: A 32-bit value representing the APB2 peripheral(s)
 *   to be enabled or disabled.
 *   - RCC_enuPeriphralMode: An enumeration representing the desired mode
 *   (enable or disable) for the specified peripheral(s).
 *
 * Return:
 *   - RCC_enuErrorState_t: An error state indicating the success or failure
 *   of the APB2 peripheral control operation.
 *
 * Errors:
 *   - RCC_enuInvalidPeriphralMode: Returned if an invalid peripheral mode is provided.
 *   - RCC_enuOK: Returned if the APB2 peripheral control operation is successful.
 *
 * APB2 Peripheral Definitions:
 *   - RCC_TIM1_ENABLE_DISABLE: TIM1 Peripheral Enable/Disable
 *   - RCC_USART1_ENABLE_DISABLE: USART1 Peripheral Enable/Disable
 *   - RCC_USART6_ENABLE_DISABLE: USART6 Peripheral Enable/Disable
 *   - RCC_ADC1_ENABLE_DISABLE: ADC1 Peripheral Enable/Disable
 *   - RCC_SDIO_ENABLE_DISABLE: SDIO Peripheral Enable/Disable
 *   - RCC_SPI1_ENABLE_DISABLE: SPI1 Peripheral Enable/Disable
 *   - RCC_SPI4_ENABLE_DISABLE: SPI4 Peripheral Enable/Disable
 *   - RCC_SYSCFG_ENABLE_DISABLE: System Configuration Controller Peripheral Enable/Disable
 *   - RCC_TIM9_ENABLE_DISABLE: TIM9 Peripheral Enable/Disable
 *   - RCC_TIM10_ENABLE_DISABLE: TIM10 Peripheral Enable/Disable
 *   - RCC_TIM11_ENABLE_DISABLE: TIM11 Peripheral Enable/Disable
 *
 * Peripheral Mode:
 *   - RCC_enuPeriphralEnable: Enable the specified APB2 peripheral(s).
 *   - RCC_enuPeriphralDisable: Disable the specified APB2 peripheral(s).
 *
 * Usage: RCC_enuErrorState_t error = RCC_Ctrl_APB2_Clk(RCC_TIM1_ENABLE_DISABLE, RCC_enuPeriphralEnable);
 *
 * Notes:
 *   - The function sets or clears bits in the RCC_APB2RSTR register based on the specified mode and peripheral.
 *****************************************************/
RCC_enuErrorState_t RCC_Ctrl_APB2_Clk(u32 Copy_u32Periphral, RCC_enuPeriphralMode_t RCC_enuPeriphralMode)
{
	RCC_enuErrorState_t RCC_ErrorState = RCC_enuOK;
	if (RCC_enuPeriphralMode == RCC_enuPeriphralEnable)
	{
		RCC_APB2RSTR |= Copy_u32Periphral;
	}
	else if (RCC_enuPeriphralMode == RCC_enuPeriphralDisable)
	{
		RCC_APB2RSTR &= ~Copy_u32Periphral;
	}
	else
	{
		RCC_ErrorState = RCC_enuInvalidPeriphralMode;
	}
	return RCC_ErrorState;
}
