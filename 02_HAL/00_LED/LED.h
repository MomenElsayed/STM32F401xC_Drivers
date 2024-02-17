/******************************************************************************
 *
 * Module: LED
 *
 * File Name: LED.h
 *
 * Description: Header file for the LED driver for STM32F401xC
 *
 * Author: Momen Elsayed Shaban
 *
 *******************************************************************************/
#ifndef LED_H_
#define LED_H_

#include "LED_Cfg.h"
#include "std_types.h"

/*******************************************************************************
 *                                Type Decelerations                           *
 *******************************************************************************/
#define LED_DIR_FORWARD     0
#define LED_DIR_REVERSE     1
#define LED_STATE_ON        1
#define LED_STATE_OFF       0

typedef struct{
    void* port;
    u32 pin;
    u8 dir;
}LED_Cfg_t;


typedef enum{
    LED_OK,
    LED_InvalidDir,
    LED_InvalidLedName,
    LED_InvalidState
}LED_ErrorStatus_t;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*****************************************************
 * Function: LED_Init
 * Description: Initializes the specified LEDs based on the provided configuration.
 *
 * Return:
 *   - LED_ErrorStatus_t: An error status indicating the success or failure of the LED initialization.
 *
 * Errors:
 *   - LED_InvalidDir: Returned if an invalid LED direction is provided.
 *   - LED_OK: Returned if the LED initialization is successful.
 *
 * Usage: LED_ErrorStatus_t error = LED_Init();
 * Example: Initialize LEDs according to the predefined configuration.
 *
 * Notes:
 *   - The LED_Init function initializes LEDs based on the LED_Cfg_t configuration.
 *****************************************************/
LED_ErrorStatus_t LED_Init();

/*****************************************************
 * Function: LED_setState
 * Description: Sets the state of the specified LED.
 *
 * Parameters:
 *   - LedName: The Name of the LED in the configuration enum "LED_Cfg.h".
 *   - Led_state: The desired state for the LED (LED_STATE_ON or LED_STATE_OFF).
 *
 * Return:
 *   - LED_ErrorStatus_t: An error status indicating the success or failure of the LED state change.
 *
 * Errors:
 *   - LED_InvalidLedName: Returned if an invalid LED index is provided.
 *   - LED_InvalidState: Returned if an invalid LED state is provided.
 *   - LED_OK: Returned if the LED state change is successful.
 *
 * Usage: LED_ErrorStatus_t error = LED_setState(0, LED_STATE_ON);
 * Example: Set the state of the first LED to ON.
 *
 * Notes:
 *   - The LED_setState function sets the state of the LED based on the LED_Cfg_t configuration.
 *****************************************************/
LED_ErrorStatus_t LED_setState(u32 Led, u8 Led_state);

#endif /*LED_H_*/