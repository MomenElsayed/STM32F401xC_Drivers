 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD_Cfg.c
 *
 * Description: Source file for the ATmega32 LCD driver Configurations
 *
 * Author: Momen Elsayed Shaban
 *
 *******************************************************************************/

#include "GPIO.h"
#include "LCD.h"
#include "LCD_Cfg.h"

/*
 * LCD Pin Configuration and Custom Character Definition
 * -----------------------------------------------------
 * Define the pin configuration for the LCD, specifying the port and pin for each data and control pin.
 * Also, define a custom character for use in the LCD.
 */

/* LCD Pin Configuration */
LCD_strPinCfg_t LCD_strCfg[NUMBER_OF_LCD_PINS] = {
    [DB0] = {.port = GPIO_PORT_A, .pin = GPIO_PIN_0},
    [DB1] = {.port = GPIO_PORT_A, .pin = GPIO_PIN_1},
    [DB2] = {.port = GPIO_PORT_A, .pin = GPIO_PIN_2},
    [DB3] = {.port = GPIO_PORT_A, .pin = GPIO_PIN_3},
    [DB4] = {.port = GPIO_PORT_A, .pin = GPIO_PIN_4},
    [DB5] = {.port = GPIO_PORT_A, .pin = GPIO_PIN_5},
    [DB6] = {.port = GPIO_PORT_A, .pin = GPIO_PIN_6},
    [DB7] = {.port = GPIO_PORT_A, .pin = GPIO_PIN_7},
    [RW]  = {.port = GPIO_PORT_A, .pin = GPIO_PIN_8},
    [RS]  = {.port = GPIO_PORT_A, .pin = GPIO_PIN_9},
    [E]   = {.port = GPIO_PORT_A, .pin = GPIO_PIN_10},
};

/* Custom Character Definition */
u8 customChar1[8] = {
    0b00000,
    0b00000,
    0b00000,
    0b11111,
    0b00101,
    0b00010,
    0b00000,
    0b00000
};
