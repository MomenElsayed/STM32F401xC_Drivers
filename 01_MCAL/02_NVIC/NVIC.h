/******************************************************************************
 *
 * Module: NVIC
 *
 * File Name: NVIC.h
 *
 * Description: Header file for the NVIC driver for STM32F401xC
 *
 * Author: Momen Elsayed Shaban
 *
 *******************************************************************************/
#ifndef NVIC_H_
#define NVIC_H_

#include "Interrupts.h"
#include "std_types.h"


/*******************************************************************************
 *                                Type Decelerations                           *
 *******************************************************************************/
typedef enum{
	NVIC_OK,
	NVIC_InvalidIRQn,
	NVIC_InvalidPriorityValue,
	NVIC_InvalidPriorityGroup,
	NVIC_NullPtr
}NVIC_ErrorStatus_t;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*****************************************************
 * Function: NVIC_EnableIRQ
 * Description: Enables the specified interrupt request (IRQ) in the Nested Vectored Interrupt Controller (NVIC).
 *
 * Parameters:
 *   - IRQn: The IRQ number to be enabled.
 *
 * Return:
 *   - NVIC_ErrorStatus_t: An error status indicating the success or failure of enabling the IRQ.
 *
 * Errors:
 *   - NVIC_InvalidIRQn: Returned if an invalid IRQ number is provided.
 *   - NVIC_OK: Returned if the IRQ enabling is successful.
 *
 * Usage: NVIC_ErrorStatus_t error = NVIC_EnableIRQ(USART1_IRQn);
 * Example: Enable the USART1 interrupt in the NVIC.
 *
 * Notes:
 *   - The IRQn parameter represents the specific interrupt number (e.g., USART1_IRQn).
 *****************************************************/
NVIC_ErrorStatus_t NVIC_EnableIRQ(IRQn_Type IRQn);

/*****************************************************
 * Function: NVIC_DisableIRQ
 * Description: Disables the specified interrupt request (IRQ) in the Nested Vectored Interrupt Controller (NVIC).
 *
 * Parameters:
 *   - IRQn: The IRQ number to be disabled.
 *
 * Return:
 *   - NVIC_ErrorStatus_t: An error status indicating the success or failure of disabling the IRQ.
 *
 * Errors:
 *   - NVIC_InvalidIRQn: Returned if an invalid IRQ number is provided.
 *   - NVIC_OK: Returned if the IRQ disabling is successful.
 *
 * Usage: NVIC_ErrorStatus_t error = NVIC_DisableIRQ(USART1_IRQn);
 * Example: Disable the USART1 interrupt in the NVIC.
 *
 * Notes:
 *   - The IRQn parameter represents the specific interrupt number (e.g., USART1_IRQn).
 *****************************************************/
NVIC_ErrorStatus_t NVIC_DisableIRQ(IRQn_Type IRQn);

/*****************************************************
 * Function: NVIC_SetPendingIRQ
 * Description: Sets the pending status of the specified interrupt request (IRQ) in the Nested Vectored Interrupt Controller (NVIC).
 *
 * Parameters:
 *   - IRQn: The IRQ number to set as pending.
 *
 * Return:
 *   - NVIC_ErrorStatus_t: An error status indicating the success or failure of setting the IRQ as pending.
 *
 * Errors:
 *   - NVIC_InvalidIRQn: Returned if an invalid IRQ number is provided.
 *   - NVIC_OK: Returned if setting the IRQ as pending is successful.
 *
 * Usage: NVIC_ErrorStatus_t error = NVIC_SetPendingIRQ(EXTI0_IRQn);
 * Example: Set the EXTI0 interrupt as pending in the NVIC.
 *
 * Notes:
 *   - The IRQn parameter represents the specific interrupt number (e.g., EXTI0_IRQn).
 *****************************************************/
NVIC_ErrorStatus_t NVIC_SetPendingIRQ(IRQn_Type IRQn);

/*****************************************************
 * Function: NVIC_ClearPendingIRQ
 * Description: Clears the pending status of the specified interrupt request (IRQ) in the Nested Vectored Interrupt Controller (NVIC).
 *
 * Parameters:
 *   - IRQn: The IRQ number to clear from pending status.
 *
 * Return:
 *   - NVIC_ErrorStatus_t: An error status indicating the success or failure of clearing the IRQ from pending status.
 *
 * Errors:
 *   - NVIC_InvalidIRQn: Returned if an invalid IRQ number is provided.
 *   - NVIC_OK: Returned if clearing the IRQ from pending status is successful.
 *
 * Usage: NVIC_ErrorStatus_t error = NVIC_ClearPendingIRQ(EXTI1_IRQn);
 * Example: Clear the pending status of the EXTI1 interrupt in the NVIC.
 *
 * Notes:
 *   - The IRQn parameter represents the specific interrupt number (e.g., EXTI1_IRQn).
 *****************************************************/
NVIC_ErrorStatus_t NVIC_ClearPendingIRQ(IRQn_Type IRQn);

/*****************************************************
 * Function: NVIC_GetPendingIRQ
 * Description: Gets the pending status of the specified interrupt request (IRQ) in the Nested Vectored Interrupt Controller (NVIC).
 *
 * Parameters:
 *   - IRQn: The IRQ number to check for pending status.
 *   - pendingStatus: Pointer to store the pending status (0 if not pending, non-zero if pending).
 *
 * Return:
 *   - NVIC_ErrorStatus_t: An error status indicating the success or failure of getting the pending status of the IRQ.
 *
 * Errors:
 *   - NVIC_InvalidIRQn: Returned if an invalid IRQ number is provided.
 *   - NVIC_NullPtr: Returned if the pendingStatus pointer is NULL.
 *   - NVIC_OK: Returned if getting the pending status of the IRQ is successful.
 *
 * Usage: NVIC_ErrorStatus_t error; u32 status; error = NVIC_GetPendingIRQ(USART1_IRQn, &status);
 * Example: Check the pending status of the USART1 interrupt and store it in the 'status' variable.
 *
 * Notes:
 *   - The IRQn parameter represents the specific interrupt number (e.g., USART1_IRQn).
 *****************************************************/
NVIC_ErrorStatus_t NVIC_GetPendingIRQ(IRQn_Type IRQn, u32* pendingStatus);

/*****************************************************
 * Function: NVIC_SetPriority
 * Description: Sets the priority of the specified interrupt request (IRQ) in the Nested Vectored Interrupt Controller (NVIC).
 *
 * Parameters:
 *   - IRQn: The IRQ number to set the priority for.
 *   - priority: The priority value to set for the IRQ (0 to 255).
 *
 * Return:
 *   - NVIC_ErrorStatus_t: An error status indicating the success or failure of setting the IRQ priority.
 *
 * Errors:
 *   - NVIC_InvalidIRQn: Returned if an invalid IRQ number is provided.
 *   - NVIC_InvalidPriorityValue: Returned if an invalid priority value is provided.
 *   - NVIC_OK: Returned if setting the IRQ priority is successful.
 *
 * Usage: NVIC_ErrorStatus_t error = NVIC_SetPriority(USART1_IRQn, 0x30);
 * Example: Set the priority of the USART1 interrupt to 0x30.
 *
 * Notes:
 * 	 - The MSB is the bits with the priority 0x30 shall be as the below
 * 	┌───────┬───────┬───────┬───────┬───────────────┐
 *	│ Bit 1 │ Bit 2 │ Bit 3 │ Bit 4 │ Hashed 4 Bits │
 *	 ─────── ─────── ─────── ─────── ───────────────
 *	┌───────┬───────┬───────┬───────┬───────────────┐
 *	│   0   │   0	│  	1	│   1   │ Hashed 4 Bits │
 *	 ─────── ─────── ─────── ─────── ───────────────
 *   - The IRQn parameter represents the specific interrupt number (e.g., USART1_IRQn).
 *****************************************************/
NVIC_ErrorStatus_t NVIC_SetPriority(IRQn_Type IRQn, u32 priority);

/*****************************************************
 * Function: NVIC_GetPriority
 * Description: Gets the priority of the specified interrupt request (IRQ) in the Nested Vectored Interrupt Controller (NVIC).
 *
 * Parameters:
 *   - IRQn: The IRQ number to get the priority for.
 *   - priority: Pointer to store the priority value of the IRQ.
 *
 * Return:
 *   - NVIC_ErrorStatus_t: An error status indicating the success or failure of getting the IRQ priority.
 *
 * Errors:
 *   - NVIC_InvalidIRQn: Returned if an invalid IRQ number is provided.
 *   - NVIC_NullPtr: Returned if the priority pointer is NULL.
 *   - NVIC_OK: Returned if getting the IRQ priority is successful.
 *
 * Usage: NVIC_ErrorStatus_t error; u32 prio; error = NVIC_GetPriority(USART1_IRQn, &prio);
 * Example: Get the priority of the USART1 interrupt and store it in the 'prio' variable.
 *
 * Notes:
 * 	  - The return value of the below block shall be 0x30 not 0x03 according to this API that respect the
 * 	  places of the priorities
 *	┌───────┬───────┬───────┬───────┬───────────────┐
 *	│   0   │   0	│  	1	│   1   │ Hashed 4 Bits │
 *   ─────── ─────── ─────── ─────── ───────────────
 *   - The IRQn parameter represents the specific interrupt number (e.g., USART1_IRQn).
 *****************************************************/
NVIC_ErrorStatus_t NVIC_GetPriority(IRQn_Type IRQn, u32* priority);

/*****************************************************
 * Function: NVIC_SetPriorityGrouping
 * Description: Sets the priority grouping of the Nested Vectored Interrupt Controller (NVIC).
 *
 * Parameters:
 *   - PriorityGroup: The priority grouping value (0 to 7).
 *
 * Return:
 *   - NVIC_ErrorStatus_t: An error status indicating the success or failure of setting the priority grouping.
 *
 * Errors:
 *   - NVIC_InvalidPriorityGroup: Returned if an invalid priority grouping value is provided.
 *   - NVIC_OK: Returned if setting the priority grouping is successful.
 *
 * Usage: NVIC_ErrorStatus_t error = NVIC_SetPriorityGrouping(4);
 * Example: Set the priority grouping of the NVIC to 4.
 *
 * Notes:
 *   - If we set the group by 4 then the first 1 will represent sub group and the second will represent
 *     the preemption group
 *     					  Group4
 *     						 |
 *   ┌───────┬───────┬───────┬───────┬───────────────┐
 *	 │   0   │   0	 │   1   │   1   │ Hashed 4 Bits │
 *    ─────── ─────── ───────|─────── ───────────────
 *    						 |
 *   - The PriorityGroup parameter is the number of priority bits that the NVIC uses for preemption and subpriority.
 *****************************************************/
NVIC_ErrorStatus_t NVIC_SetPriorityGrouping(u32 PriorityGroup);

/*****************************************************
 * Function: NVIC_GetPriorityGrouping
 * Description: Retrieves the current priority grouping setting from the NVIC.
 *
 * Parameters:
 *   - PriorityGroup: Pointer to a variable where the priority grouping value will be stored.
 *
 * Return:
 *   - NVIC_ErrorStatus_t: An error status indicating the success or failure of the operation.
 *     - NVIC_OK: Operation was successful.
 *     - NVIC_NullPtr: Returned if the PriorityGroup pointer is null.
 *
 * Usage: u32 priorityGroup; NVIC_ErrorStatus_t error = NVIC_GetPriorityGrouping(&priorityGroup);
 * Example: Retrieve the current NVIC priority grouping and store it in the priorityGroup variable.
 *
 * Notes:
 *   - Priority grouping determines the split between preempt priority levels and subpriority levels in the NVIC.
 *****************************************************/
NVIC_ErrorStatus_t NVIC_GetPriorityGrouping(u32* PriorityGroup);

/*****************************************************
 * Function: NVIC_EncodePriority
 * Description: Encodes the priority for an IRQ with the specified priority grouping.
 *
 * Parameters:
 *   - PriorityGroup: Priority grouping used.
 *   - PreemptPriority: Preemptive priority level of the interrupt.
 *   - SubPriority: Subpriority level of the interrupt within the preemptive priority.
 *   - Priority: Pointer to store the calculated NVIC priority value.
 *
 * Return:
 *   - NVIC_ErrorStatus_t: An error status indicating the success or failure of the operation.
 *     - NVIC_OK: Operation was successful.
 *     - NVIC_InvalidPriorityGroup: Returned if the priority group is not within the valid range.
 *     - NVIC_NullPtr: Returned if the Priority pointer is null.
 *
 * Usage: u32 encodedPriority; NVIC_ErrorStatus_t error = NVIC_EncodePriority(4 , 5 , 1, &encodedPriority);
 * - encodedPriority will be 176
 * Example: Calculate and encode the priority with specified priority grouping, preemptive priority, and subpriority levels.
 *
 * Notes:
 * 	 - the priority for the below shall be 176 (0xB0) According to this API
 * 	 					   Group4
 *     						 |
 *   ┌───────┬───────┬───────┬───────┬───────────────┐
 *	 │   1   │   0	 │   1   │   1   │ Hashed 4 Bits │
 *    ─────── ─────── ───────|─────── ───────────────
 *    						 |
 *   - This function calculates the NVIC priority based on the specified priority grouping and priority levels.
 *   - The calculation takes into account the priority grouping, which affects the number of bits used for preemptive and subpriority levels.
 *   - If you used another group than the default (3) you must use NVIC_SetPriorityGrouping(newGroupValue);
 *   - After You Get the priority you can use it directly in NVIC_SetPriority(IRQn,priority);
 *****************************************************/
NVIC_ErrorStatus_t NVIC_EncodePriority(u32 PriorityGroup, u32 PreemptPriority, u32 SubPriority, u32* Priority);

/*****************************************************
 * Function: NVIC_DecodePriority
 * Description: Decodes an NVIC priority value into its preemptive priority and subpriority components based on the specified priority grouping.
 *
 * Parameters:
 *   - PriorityGroup: Priority grouping that was used to encode the priority.
 *   - Priority: The encoded NVIC priority value to be decoded.
 *   - PreemptPriority: Pointer to store the decoded preemptive priority level.
 *   - SubPriority: Pointer to store the decoded subpriority level.
 *
 * Return:
 *   - NVIC_ErrorStatus_t: An error status indicating the success or failure of the operation.
 *     - NVIC_OK: Operation was successful.
 *     - NVIC_InvalidPriorityValue: Returned if the PriorityGroup is beyond acceptable range.
 *     - NVIC_NullPtr: Returned if any of the output pointers are null.
 *
 * Usage: NVIC_ErrorStatus_t error = NVIC_DecodePriority(4 , 176, &preemptPriority, &subPriority);
 * preemptPriority = 5; subPriority = 1;
 * Example: Decode the encoded priority value to understand its preemptive priority and subpriority components.
 *
 * Notes:
 *   - This function is the inverse of NVIC_EncodePriority, allowing for the extraction of preemptive and subpriority levels from a given NVIC priority value.
 *   - It is useful for understanding or displaying the priority levels of configured interrupts.
 *   - The PriorityGroup parameter is critical as it determines how many bits are used for preemptive and subpriority levels.
 *****************************************************/
NVIC_ErrorStatus_t NVIC_DecodePriority(u32 PriorityGroup, u32 Priority, u32* PreemptPriority, u32* SubPriority);

/*****************************************************
 * Function: NVIC_GetActive
 * Description: Checks if a specific IRQ number is currently active.
 *
 * Parameters:
 *   - IRQn: The IRQ number to check.
 *   - ActiveIR: Pointer to store the result (0 if not any other number if active).
 *
 * Return:
 *   - NVIC_ErrorStatus_t: Status of the operation.
 *     - NVIC_OK: Operation successful.
 *     - NVIC_NullPtr: Returned if the ActiveIR pointer is NULL.
 *     - NVIC_InvalidIRQn: Returned if the IRQn is beyond the supported range.
 *
 * Usage:
 *   u32 isActive;
 *   NVIC_ErrorStatus_t status = NVIC_GetActive(IRQn, &isActive);
 *   if(status == NVIC_OK && isActive) {
 *     // IRQn is active
 *   }
 *
 * Notes:
 *   - The function checks the active status of an IRQ by accessing the appropriate
 *     bit in the NVIC's Interrupt Active Bit Register (IABR).
 *   - ActiveIR will be set to non-zero if the IRQ is active, and 0 if it is not active.
 *****************************************************/
NVIC_ErrorStatus_t NVIC_GetActive (IRQn_Type IRQn, u32* AciveIR);

/*****************************************************
 * Function: NVIC_TriggerSWInterrupt
 * Description: Triggers a software interrupt for a specific IRQ number.
 *
 * Parameters:
 *   - IRQn: The IRQ number to trigger.
 *
 * Return:
 *   - NVIC_ErrorStatus_t: Status of the operation.
 *     - NVIC_OK: Operation successful.
 *     - NVIC_InvalidIRQn: Returned if the IRQn is beyond the supported range.
 *
 * Usage:
 *   NVIC_ErrorStatus_t status = NVIC_TriggerSWInterrupt(IRQn);
 *   if(status == NVIC_OK) {
 *     // Software interrupt triggered successfully
 *   }
 *
 * Notes:
 *   - This function allows software to trigger interrupts directly through the NVIC's
 *     Software Trigger Interrupt Register.
 *   - Useful for testing interrupt handlers or simulating interrupts in software.
 *****************************************************/
NVIC_ErrorStatus_t NVIC_TriggerSWInterrupt(IRQn_Type IRQn);


#endif /* NVIC_H_ */
