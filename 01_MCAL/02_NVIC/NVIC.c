/******************************************************************************
 *
 * Module: NVIC
 *
 * File Name: NVIC.c
 *
 * Description: Source file for the NVIC driver for STM32F401xC
 *
 * Author: Momen Elsayed Shaban
 *
 *******************************************************************************/
#include "NVIC.h"


#define NVIC_PRIO_BITS        	4U       /* STM32F4XC uses 4 Bits for the Priority Levels */
#define NVIC_BASE_ADDR		  	0xE000E100
#define SCB_BASE_ADDR		  	0xE000E008
#define SCB_AIRCR_VECTKEY_MASK	0xFFFF0000
#define SCB_AIRCR_VECTKEY_POS	16U
#define SCB_AIRCR_PRIGROUP_MASK	0x00000700
#define SCB_AIRCR_PRIGROUP_POS	8U


typedef struct
{
	volatile u32 ISER[8];
	u32 Reserved[24];
	volatile u32 ICER[8];
	u32 Reserved1[24];
	volatile u32 ISPR[8];
	u32 Reserved2[24];
	volatile u32 ICPR[8];
	u32 Reserved3[24];
	volatile u32 IABR[8];
	u32 Reserved4[56];
	volatile u8 IPR[240];		/*Interrupt Priority Register Mapped as 8 bits For Each Interrupt in the 240*/
	u32 Reserved5[644];
	volatile u32 STIR;
}NVIC_Registers_t;

typedef struct
{
    volatile u32 ACTLR;
    u32 Reserved1[829];
    volatile u32 CPUID;
    volatile u32 ICSR;
    volatile u32 VTOR;
    volatile u32 AIRCR;
    volatile u32 SCR;
    volatile u32 CCR;
    volatile u8 SHPR[12];
    volatile u32 SHCSR;
    volatile u32 CFSR;
    volatile u32 HFSR;
    volatile u32 Reserved2;
    volatile u32 MMAR;
    volatile u32 BFAR;
    volatile u32 AFSR;
}SCB_Registers_t;

static NVIC_Registers_t* const NVIC = (NVIC_Registers_t*)NVIC_BASE_ADDR;

static SCB_Registers_t* const SCB = (SCB_Registers_t*)SCB_BASE_ADDR;

NVIC_ErrorStatus_t NVIC_EnableIRQ(IRQn_Type IRQn)
{
	NVIC_ErrorStatus_t ErrorStatus = NVIC_OK;
	if(!(IRQn >= 0 && IRQn <= _NVIC_IRQn))
	{
		ErrorStatus = NVIC_InvalidIRQn;
	}
	else
	{
		/* Divide IRQn by 32 to get the suitable index of the array*/
		NVIC->ISER[IRQn >> 5] |= (1 << (IRQn % 32));
	}
	return ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_DisableIRQ(IRQn_Type IRQn)
{
	NVIC_ErrorStatus_t ErrorStatus = NVIC_OK;
	if(!(IRQn >= 0 && IRQn <= _NVIC_IRQn))
	{
		ErrorStatus = NVIC_InvalidIRQn;
	}
	else
	{
		/* Divide IRQn by 32 to get the suitable index of the array*/
		NVIC->ICER[IRQn >> 5] |= (1 << (IRQn % 32));
	}
	return ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
	NVIC_ErrorStatus_t ErrorStatus = NVIC_OK;
	if(!(IRQn >= 0 && IRQn <= _NVIC_IRQn))
	{
		ErrorStatus = NVIC_InvalidIRQn;
	}
	else
	{
		/* Divide IRQn by 32 to get the suitable index of the array*/
		NVIC->ISPR[IRQn >> 5] |= (1 << (IRQn % 32));
	}
	return ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
	NVIC_ErrorStatus_t ErrorStatus = NVIC_OK;
	if(!(IRQn >= 0 && IRQn <= _NVIC_IRQn))
	{
		ErrorStatus = NVIC_InvalidIRQn;
	}
	else
	{
		/* Divide IRQn by 32 to get the suitable index of the array*/
		NVIC->ICPR[IRQn >> 5] |= (1 << (IRQn % 32));
	}
	return ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_GetPendingIRQ(IRQn_Type IRQn, u32* pendingStatus)
{
	NVIC_ErrorStatus_t ErrorStatus = NVIC_OK;
	if(!(IRQn >= 0 && IRQn <= _NVIC_IRQn))
	{
		ErrorStatus = NVIC_InvalidIRQn;
	}
	else if (pendingStatus == NULL_PTR)
	{
		ErrorStatus = NVIC_NullPtr;
	}
	else
	{
		/* If the value is 0 not pending else is in pending state*/
		*pendingStatus = (NVIC->ICPR[IRQn >> 5] & (1 << (IRQn % 32)));
	}
	return ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_SetPriority(IRQn_Type IRQn, u32 priority)
{
	NVIC_ErrorStatus_t ErrorStatus = NVIC_OK;
	if(IRQn > _NVIC_IRQn)
	{
		ErrorStatus = NVIC_InvalidIRQn;
	}
	else if (priority >= 256)
	{
		ErrorStatus = NVIC_InvalidPriorityValue;
	}
	/*In Case of System Interrupts*/
	else if (IRQn < 0)
	{
		//SCB->SHPR[(u32)((IRQn - 8) >> 2)] = (priority << (8 - NVIC_PRIO_BITS));	/*Fix ME*/
	}
	else
	{
		NVIC->IPR[IRQn] = priority;
	}
	return ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_GetPriority(IRQn_Type IRQn, u32* priority)
{
	NVIC_ErrorStatus_t ErrorStatus = NVIC_OK;
	if(IRQn > _NVIC_IRQn)
	{
		ErrorStatus = NVIC_InvalidIRQn;
	}
	else if(priority == NULL_PTR)
	{
		ErrorStatus = NVIC_NullPtr;
	}
	/*In Case of System Interrupts*/
	else if (IRQn < 0)
	{
		//*priority = SCB->SHPR[(u32)((IRQn - 8) >> 2)] & (priority << (8 - NVIC_PRIO_BITS));	/*Fix ME*/
	}
	else
	{
		*priority = NVIC->IPR[IRQn] & (IRQn << (8 - NVIC_PRIO_BITS)); //FIX ME
	}
	return ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_SetPriorityGrouping(u32 PriorityGroup)
{
	NVIC_ErrorStatus_t ErrorStatus = NVIC_OK;
	u32 reg_value = 0;
	if(PriorityGroup > 7)
	{
		ErrorStatus = NVIC_InvalidPriorityGroup;
	}
	else
	{
		reg_value = SCB->AIRCR;
		reg_value &= ~(SCB_AIRCR_VECTKEY_MASK | SCB_AIRCR_PRIGROUP_MASK);
		reg_value |= ((u32)0x5FA << SCB_AIRCR_VECTKEY_POS) | ((PriorityGroup & 0x07) << SCB_AIRCR_PRIGROUP_POS);
		SCB->AIRCR = reg_value;
	}
	return ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_GetPriorityGrouping(u32* PriorityGroup)
{
	NVIC_ErrorStatus_t ErrorStatus = NVIC_OK;
	if(PriorityGroup == NULL_PTR)
	{
		ErrorStatus = NVIC_NullPtr;
	}
	else
	{
		*PriorityGroup = (SCB->AIRCR & SCB_AIRCR_PRIGROUP_MASK) >> SCB_AIRCR_PRIGROUP_POS;
	}
	return ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_EncodePriority(u32 PriorityGroup, u32 PreemptPriority, u32 SubPriority, u32* Priority)
{
	NVIC_ErrorStatus_t ErrorStatus = NVIC_OK;
	u32 SubPriorityBits = 0;
	u8 DontCareBits = (8 - NVIC_PRIO_BITS);
	if((PriorityGroup > 7) || ((7 - PriorityGroup) > NVIC_PRIO_BITS))
	{
		ErrorStatus = NVIC_InvalidPriorityGroup;
	}
	else if(Priority == NULL_PTR)
	{
		ErrorStatus = NVIC_NullPtr;
	}
	else
	{
		SubPriorityBits = (PriorityGroup + 1) - DontCareBits;
		*Priority = ((PreemptPriority << SubPriorityBits) | (SubPriority)) << NVIC_PRIO_BITS;
	}

	return ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_DecodePriority(u32 PriorityGroup, u32 Priority, u32* PreemptPriority, u32* SubPriority)
{
	NVIC_ErrorStatus_t ErrorStatus = NVIC_OK;
	u32 PreemptPriorityBits = 0;
	u32 SubPriorityBits = 0;
	u8 DontCareBits = (8 - NVIC_PRIO_BITS);
	if(PriorityGroup > _NVIC_IRQn)
	{
		ErrorStatus = NVIC_InvalidPriorityValue;
	}
	else if (PreemptPriority == NULL_PTR || SubPriority == NULL_PTR)
	{
		ErrorStatus = NVIC_NullPtr;
	}
	else
	{
		PreemptPriorityBits = 7 - PriorityGroup;
		SubPriorityBits = (PriorityGroup + 1) - DontCareBits;
		*PreemptPriority = (Priority >> (SubPriorityBits + DontCareBits)) & ((1 << PreemptPriorityBits)- 1);
		*SubPriority = (Priority >> DontCareBits)  & ((1 << SubPriorityBits)- 1);
	}
	return ErrorStatus;

}

NVIC_ErrorStatus_t NVIC_GetActive(IRQn_Type IRQn, u32* AciveIR)
{
	NVIC_ErrorStatus_t ErrorStatus = NVIC_OK;
	if(AciveIR == NULL_PTR)
	{
		ErrorStatus = NVIC_NullPtr;
	}
	else if(IRQn > _NVIC_IRQn)
	{
		ErrorStatus = NVIC_InvalidIRQn;
	}
	else
	{
		*AciveIR = NVIC->IABR[IRQn >> 5] & (1 << (IRQn % 32));
	}
	return ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_TriggerSWInterrupt(IRQn_Type IRQn)
{
	NVIC_ErrorStatus_t ErrorStatus = NVIC_OK;
	if(IRQn > _NVIC_IRQn)
	{
		ErrorStatus = NVIC_InvalidIRQn;
	}
	else
	{
		NVIC->STIR = IRQn;
	}
	return ErrorStatus;
}




