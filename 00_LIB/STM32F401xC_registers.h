 /******************************************************************************
 *
 * File Name: STM32F401xC_registers.h
 *
 * Description: Header file for STM32F401xC registers Addresses
 *
 * Author: Momen Elsayed Shaban
 *
 *******************************************************************************/

#ifndef STM32F401xC_REGISTERS
#define STM32F401xC_REGISTERS

#include "std_types.h"


#define RCC_BASE_ADDR       0x40023800U /* RCC Base Address */

#define RCC_CR              (*(volatile u32*)(RCC_BASE_ADDR + 0x00)) /* Clock Control Register */
#define RCC_CR_HSION        0  /* Internal High-Speed Clock Enable */
#define RCC_CR_HSIRDY       1  /* Internal High-Speed Clock Ready */
#define RCC_CR_HSEON        16 /* HSE oscillator Enable */
#define RCC_CR_HSERDY       17 /* HSE oscillator Ready */
#define RCC_CR_HSEBYP		18 /* HSE clock bypass*/
#define RCC_CR_PLLON        24 /* Main PLL (PLL) Enable */
#define RCC_CR_PLLRDY       25 /* Main PLL (PLL) Ready */
#define RCC_CR_CSSON        28 /* Clock Security System Enable */
#define RCC_CR_PLLI2SON     26 /* PLLI2S Enable */
#define RCC_CR_PLLI2SRDY    27 /* PLLI2S Ready */
#define RCC_PLLCFGR         (*(volatile u32*)(RCC_BASE_ADDR + 0x04)) /* PLL Configuration Register */
#define RCC_PLLCFGR_PLLM    0   /* Position of PLLM bits in RCC_PLLCFGR register */
#define RCC_PLLCFGR_PLLN    6   /* Position of PLLN bits in RCC_PLLCFGR register */
#define RCC_PLLCFGR_PLLP    16  /* Position of PLLP bits in RCC_PLLCFGR register */
#define RCC_PLLCFGR_PLLSRC  22  /* Position of PLLSRC bit in RCC_PLLCFGR register */
#define RCC_PLLCFGR_PLLQ    24  /* Position of PLLQ bits in RCC_PLLCFGR register */
#define RCC_CFGR            (*(volatile u32*)(RCC_BASE_ADDR + 0x08)) /* Clock Configuration Register */
#define RCC_CFGR_HPRE    	4   /* Position of HPRE bits in RCC_CFGR register */
#define RCC_CFGR_PPRE1   	10  /* Position of PPRE1 bits in RCC_CFGR register */
#define RCC_CFGR_PPRE2   	13  /* Position of PPRE2 bits in RCC_CFGR register */
#define RCC_CIR             (*(volatile u32*)(RCC_BASE_ADDR + 0x0C)) /* Clock Interrupt Register */
#define RCC_AHB1RSTR        (*(volatile u32*)(RCC_BASE_ADDR + 0x10)) /* AHB1 Peripheral Reset Register */
#define RCC_AHB2RSTR        (*(volatile u32*)(RCC_BASE_ADDR + 0x14)) /* AHB2 Peripheral Reset Register */
#define RCC_AHB3RSTR        (*(volatile u32*)(RCC_BASE_ADDR + 0x18)) /* AHB3 Peripheral Reset Register */
#define RCC_APB1RSTR        (*(volatile u32*)(RCC_BASE_ADDR + 0x20)) /* APB1 Peripheral Reset Register */
#define RCC_APB2RSTR        (*(volatile u32*)(RCC_BASE_ADDR + 0x24)) /* APB2 Peripheral Reset Register */
#define RCC_AHB1ENR         (*(volatile u32*)(RCC_BASE_ADDR + 0x30)) /* AHB1 Peripheral Clock Enable Register */
#define RCC_AHB2ENR         (*(volatile u32*)(RCC_BASE_ADDR + 0x34)) /* AHB2 Peripheral Clock Enable Register */
#define RCC_AHB3ENR         (*(volatile u32*)(RCC_BASE_ADDR + 0x38)) /* AHB3 Peripheral Clock Enable Register */
#define RCC_APB1ENR         (*(volatile u32*)(RCC_BASE_ADDR + 0x40)) /* APB1 Peripheral Clock Enable Register */
#define RCC_APB2ENR         (*(volatile u32*)(RCC_BASE_ADDR + 0x44)) /* APB2 Peripheral Clock Enable Register */
#define RCC_AHB1LPENR       (*(volatile u32*)(RCC_BASE_ADDR + 0x50)) /* AHB1 Peripheral Clock Enable in Low Power mode Register */
#define RCC_AHB2LPENR       (*(volatile u32*)(RCC_BASE_ADDR + 0x54)) /* AHB2 Peripheral Clock Enable in Low Power mode Register */
#define RCC_AHB3LPENR       (*(volatile u32*)(RCC_BASE_ADDR + 0x58)) /* AHB3 Peripheral Clock Enable in Low Power mode Register */
#define RCC_APB1LPENR       (*(volatile u32*)(RCC_BASE_ADDR + 0x60)) /* APB1 Peripheral Clock Enable in Low Power mode Register */
#define RCC_APB2LPENR       (*(volatile u32*)(RCC_BASE_ADDR + 0x64)) /* APB2 Peripheral Clock Enable in Low Power mode Register */
#define RCC_BDCR            (*(volatile u32*)(RCC_BASE_ADDR + 0x70)) /* Backup Domain Control Register */
#define RCC_CSR             (*(volatile u32*)(RCC_BASE_ADDR + 0x74)) /* Control/Status Register */
#define RCC_SSCGR           (*(volatile u32*)(RCC_BASE_ADDR + 0x80)) /* Spread Spectrum Clock Generation Register */
#define RCC_PLLI2SCFGR      (*(volatile u32*)(RCC_BASE_ADDR + 0x84)) /* PLLI2S Configuration Register */
#define RCC_PLLSAICFGR      (*(volatile u32*)(RCC_BASE_ADDR + 0x88)) /* PLLSAI Configuration Register */
#define RCC_DCKCFGR         (*(volatile u32*)(RCC_BASE_ADDR + 0x8C)) /* Dedicated Clock Configuration Register */


#endif /*STM32F401xC_REGISTERS*/
