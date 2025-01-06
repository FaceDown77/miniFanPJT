#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "../../periph/GPIO/GPIO.h"

#define LCD_CONTROL_DDR		DDRG
#define LCD_CONTROL_PORT	PORTG
#define LCD_DATA_DDR		DDRC
#define LCD_DATA_PORT		PORTC
#define LCD_RS				2
#define LCD_RW				3
#define LCD_EN				4

#define LCD_8BIT_FUNCTION_SET	0x38	//0b 0011 1000
#define LCD_DISPLAY_OFF			0x08	//0b 0000 1000
#define LCD_DISPLAY_CLEAR		0x01	//0b 0000 0001
#define LCD_ENTRY_MODE_SET		0x06	//0b 0000 0110
#define LCD_DISPLAY_ON			0x0c	//0b 0000 1100


void LCD_gpioInit();
void LCD_cmdMode();
void LCD_charMode();
void LCD_writeMode();
void LCD_enableHigh();
void LCD_enableLow();
void LCD_writeByte(uint8_t data);
void LCD_writeCmdData(uint8_t data);
void LCD_writeCharData(uint8_t data);
void LCD_init();
void LCD_writeString(char *str);
void LCD_gotoXY(uint8_t row, uint8_t col);
void LCD_writeStringXY(uint8_t row, uint8_t col, char *str);
void LCD_clearDisplay();

#endif /* LCD_H_ */