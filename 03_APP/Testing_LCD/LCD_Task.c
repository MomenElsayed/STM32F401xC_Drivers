#include "LCD.h"



// every 10 ms
void LCD_writeName()
{
	//LCD_clearScreen();
	LCD_WriteStringAsync("Momen",5,0,0);
}

