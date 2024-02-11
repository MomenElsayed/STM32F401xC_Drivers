/******************************************************************************
 *
 * Module: RCC
 *
 * File Name: RCC.h
 *
 * Description: Header file for the RCC driver Configurations for STM32F401xC
 *
 * Author: Momen Elsayed Shaban
 *
 *******************************************************************************/

#ifndef RCC_H_
#define RCC_H_

#include "std_types.h"


/*******************************************************************************
 *                                Type Decelerations                           *
 *******************************************************************************/
/************RCC AHB1 peripherals******************/
#define RCC_GPIOA_ENABLE_DISABLE		0x00000001
#define RCC_GPIOB_ENABLE_DISABLE		0x00000002
#define RCC_GPIOC_ENABLE_DISABLE		0x00000004
#define RCC_GPIOD_ENABLE_DISABLE		0x00000008
#define RCC_GPIOE_ENABLE_DISABLE		0x00000010
#define RCC_GPIOH_ENABLE_DISABLE		0x00000080
#define RCC_CRCRST_ENABLE_DISABLE		0x00001000
#define RCC_DMA1_ENABLE_DISABLE			0x00200000
#define RCC_DMA2_ENABLE_DISABLE			0x00400000

/************RCC AHB2 peripherals******************/
#define RCC_OTGFS_ENABLE_DISABLE		0x00000080

/************RCC APB1 peripherals******************/
#define RCC_TIM2_ENABLE_DISABLE			0x00000001
#define RCC_TIM3_ENABLE_DISABLE			0x00000002
#define RCC_TIM4_ENABLE_DISABLE			0x00000004
#define RCC_TIM5_ENABLE_DISABLE			0x00000008
#define RCC_WWDG_ENABLE_DISABLE			0x00000800
#define RCC_SPI2_ENABLE_DISABLE			0x00004000
#define RCC_SPI3_ENABLE_DISABLE			0x00008000
#define RCC_USART2_ENABLE_DISABLE		0x00020000
#define RCC_I2C1_ENABLE_DISABLE			0x00200000
#define RCC_I2C2_ENABLE_DISABLE			0x00400000
#define RCC_I2C3_ENABLE_DISABLE			0x00800000
#define RCC_PWR_ENABLE_DISABLE			0x10000000

/************RCC APB2 peripherals******************/
#define RCC_TIM1_ENABLE_DISABLE       	0x00000001
#define RCC_USART1_ENABLE_DISABLE     	0x00000010
#define RCC_USART6_ENABLE_DISABLE     	0x00000020
#define RCC_ADC1_ENABLE_DISABLE       	0x00000100
#define RCC_SDIO_ENABLE_DISABLE       	0x00000800
#define RCC_SPI1_ENABLE_DISABLE       	0x00001000
#define RCC_SPI4_ENABLE_DISABLE       	0x00002000
#define RCC_SYSCFG_ENABLE_DISABLE     	0x00004000
#define RCC_TIM9_ENABLE_DISABLE       	0x00010000
#define RCC_TIM10_ENABLE_DISABLE      	0x00020000
#define RCC_TIM11_ENABLE_DISABLE      	0x00040000

/************RCC AHB prescalers******************/
#define RCC_AHB_PRESCALER_NONE				0x0
#define RCC_AHB_PRESCALER_2					0x8
#define RCC_AHB_PRESCALER_4					0x9
#define RCC_AHB_PRESCALER_8					0xA
#define RCC_AHB_PRESCALER_16				0xB
#define RCC_AHB_PRESCALER_64				0xC
#define RCC_AHB_PRESCALER_128				0xD
#define RCC_AHB_PRESCALER_256				0xE
#define RCC_AHB_PRESCALER_512				0xF

/************RCC APB1 prescalers******************/
#define RCC_APB1_PRESCALER_NONE				0x0
#define RCC_APB1_PRESCALER_2				0x4
#define RCC_APB1_PRESCALER_4				0x5
#define RCC_APB1_PRESCALER_8				0x6
#define RCC_APB1_PRESCALER_16				0x7

/************RCC APB2 prescalers******************/
#define RCC_APB2_PRESCALER_NONE				0x0
#define RCC_APB2_PRESCALER_2				0x4
#define RCC_APB2_PRESCALER_4				0x5
#define RCC_APB2_PRESCALER_8				0x6
#define RCC_APB2_PRESCALER_16				0x7


#define NUMBER_OF_SUPPORTED_FREQS		4

typedef enum {
    RCC_enuPeriphralEnable,    /* Enable the specified peripheral(s) */
    RCC_enuPeriphralDisable    /* Disable the specified peripheral(s) */
} RCC_enuPeriphralMode_t;


typedef enum{
	RCC_enuHSI,			/*The high speed Internal clock signal*/
	RCC_enuHSE_bypass,	/*The high speed external clock signal bypass*/
	RCC_enuHSE_crystal,	/*The high speed external clock signal crystal*/
	RCC_enuPLL,			/*Main Phase-locked loop*/
	RCC_enuPLLI2S		/*A dedicated PLL (PLLI2S) used to generate an accurate clock to achieve high-quality
						 *audio performance on the I2S interface*/
}RCC_enuClk_t;

typedef enum{
	RCC_enuSysHSI,			/*The high speed Internal clock signal*/
	RCC_enuSysHSE,			/*The high speed external clock signal bypass*/
	RCC_enuSysPLL			/*Main Phase-locked loop*/
}RCC_enuSysClk_t;

typedef enum {
    RCC_enu48Mhz,    /* Supported frequency option for 48 MHz */
    RCC_enu54Mhz,    /* Supported frequency option for 54 MHz */
    RCC_enu64Mhz,    /* Supported frequency option for 64 MHz */
    RCC_enu84Mhz     /* Supported frequency option for 84 MHz */
} RCC_enuFreqSupported_t;

typedef enum {
    RCC_enuOK,                      /* Operation completed successfully */
    RCC_enuInvalidClk,              /* Invalid clock option provided */
    RCC_enuInvalidClkSrcForPLL,     /* Invalid clock source provided for PLL configuration */
    RCC_enuNotSupportedFreq,        /* Unsupported frequency option provided */
    RCC_enuPLLisONwhileCfg,         /* Attempted PLL configuration while PLL is already enabled */
    RCC_enuInvalidSysClk,           /* Invalid system clock option provided */
    RCC_enuInvalidPeriphralMode,    /* Invalid peripheral mode provided for control */
    RCC_enuInvalidPrescaler         /* Invalid prescaler value provided */
} RCC_enuErrorState_t;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
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
RCC_enuErrorState_t RCC_setClk(RCC_enuClk_t RCC_clk);

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
RCC_enuErrorState_t RCC_setPLLClkCfg(RCC_enuClk_t RCC_clkSrc,RCC_enuFreqSupported_t RCC_clkFreq);

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
RCC_enuErrorState_t RCC_setSystemClk(RCC_enuSysClk_t RCC_SysclkSrc);

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
RCC_enuErrorState_t RCC_Set_AHB1_Prescaler(u8 Copy_AHB1_Prescaler);

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
RCC_enuErrorState_t RCC_Ctrl_AHB1_Clk(u32 Copy_u32Periphral, RCC_enuPeriphralMode_t RCC_enuPeriphralMode);

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
RCC_enuErrorState_t RCC_Ctrl_AHB2_Clk(u32 Copy_u32Periphral, RCC_enuPeriphralMode_t RCC_enuPeriphralMode);

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
RCC_enuErrorState_t RCC_Set_APB1_Prescaler(u8 Copy_APB1_Prescaler);

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
RCC_enuErrorState_t RCC_Ctrl_APB1_Clk(u32 Copy_u32Periphral, RCC_enuPeriphralMode_t RCC_enuPeriphralMode);

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
RCC_enuErrorState_t RCC_Set_APB2_Prescaler(u8 Copy_APB2_Prescaler);

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
RCC_enuErrorState_t RCC_Ctrl_APB2_Clk(u32 Copy_u32Periphral, RCC_enuPeriphralMode_t RCC_enuPeriphralMode);



#endif /* RCC_H_ */
