/******************************************************************************
 *
 * Module: LED
 *
 * File Name: LED_Cfg.c
 *
 * Description: Source file for the LED driver for STM32F401xC Configurations
 *
 * Author: Momen Elsayed Shaban
 *
 *******************************************************************************/
#include "GPIO.h"
#include "LED.h"

const LED_Cfg_t LEDS[_LEDS_NUM] = 
{
    [LED_Alarm] = {
        .port = GPIO_PORT_A,
        .pin = GPIO_PIN_0,
        .dir = LED_DIR_FORWARD
    }
};
