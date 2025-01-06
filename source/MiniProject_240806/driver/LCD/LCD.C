#include "LCD.h"


void LCD_gpioInit()
{
	Gpio_initPin(&LCD_CONTROL_DDR, OUTPUTMODE, LCD_RS);
	Gpio_initPin(&LCD_CONTROL_DDR, OUTPUTMODE, LCD_RW);
	Gpio_initPin(&LCD_CONTROL_DDR, OUTPUTMODE, LCD_EN);
	Gpio_initPort(&LCD_DATA_DDR, OUTPUTMODE);
}

void LCD_cmdMode()
{
	// RS Pin : bit를 0 set
	Gpio_writePin(&LCD_CONTROL_PORT, LCD_RS, GPIO_PIN_RESET);
}

void LCD_charMode()
{
	// RS Pin : bit를 1 set
	Gpio_writePin(&LCD_CONTROL_PORT, LCD_RS, GPIO_PIN_SET);
}

void LCD_writeMode()
{
	// RW Pin : bit를 0 Set
	Gpio_writePin(&LCD_CONTROL_PORT, LCD_RW, GPIO_PIN_RESET);
}

void LCD_enableHigh()
{
	// Enable Pin : bit를 1 Set
	Gpio_writePin(&LCD_CONTROL_PORT, LCD_EN, GPIO_PIN_SET);
	_delay_ms(1);
}

void LCD_enableLow()
{
	// Enable Pin : bit를 1 Set
	Gpio_writePin(&LCD_CONTROL_PORT, LCD_EN, GPIO_PIN_RESET);
	_delay_ms(1);
}

void LCD_writeByte(uint8_t data)
{
	// 8개의 비트를 PORT에 내보내기
	Gpio_writePort(&LCD_DATA_PORT, data);
}


// AVR -> LCD 명령어를 보낼경우 (Write Mode)
void LCD_writeCmdData(uint8_t data)
{
	// LCD로 명령어 전달
	// RS : 0 / RW : 0 / E : 0 -> 1 -> 0
	LCD_cmdMode();			// RS를 0으로 바꿔주는 역할 (Instruction 모드)
	LCD_writeMode();		// RW를 0으로 바꿔주는 역할
	LCD_enableHigh();		// enable을 High로 올려주고
	LCD_writeByte(data);	// data 얹어두고
	LCD_enableLow();		// enable을 Low로 내린다
}


// AVR -> LCD 데이터를 보낼경우 (Write Mode)
void LCD_writeCharData(uint8_t data)
{
	// LCD로 띄울 데이터 전달
	LCD_charMode();			// RS를 1로 바꿔주는 역할 (Data 모드)
	LCD_writeMode();		// RW를 0으로 바꿔주는 역할
	LCD_enableHigh();		// enable을 High로 올려주고
	LCD_writeByte(data);	// data 얹어두고
	LCD_enableLow();		// enable을 Low로 내린다
}

void LCD_init()
{
	LCD_gpioInit();
	
	_delay_ms(15);
	LCD_writeCmdData(LCD_8BIT_FUNCTION_SET);	// LCD_8bit_FUNCTION_SET	0x38
	
	_delay_ms(5);
	LCD_writeCmdData(LCD_8BIT_FUNCTION_SET);	// LCD_8bit_FUNCTION_SET	0x38
	
	_delay_ms(1);
	LCD_writeCmdData(LCD_8BIT_FUNCTION_SET);	// LCD_8bit_FUNCTION_SET	0x38
	
	LCD_writeCmdData(LCD_8BIT_FUNCTION_SET);	// LCD_8bit_FUNCTION_SET	0x38
	LCD_writeCmdData(LCD_DISPLAY_OFF);			// LCD_DISPLAY_OFF			0x08
	LCD_writeCmdData(LCD_DISPLAY_CLEAR);		// LCD_DISPLAY_Clear		0x01
	LCD_writeCmdData(LCD_ENTRY_MODE_SET);		// LCD_Entry_Mode_SET		0x06
	
	LCD_writeCmdData(LCD_DISPLAY_ON);			// LCD_DISPLAY_ON			0x0c
}

void LCD_writeString(char *str)
{
	for (int i = 0; str[i]; i++)	// 문자열의 NULL 문자를 만날때까지 FOR문 반복
	{
		LCD_writeCharData(str[i]);
	}
}

void LCD_gotoXY(uint8_t row, uint8_t col)	// 줄, 칸
{
	col %= 16;
	row %= 2;
	uint8_t lcdRegisterAddress = (0x40 * row) + col;
	uint8_t command = 0x80 + lcdRegisterAddress;
	LCD_writeCmdData(command);
}

void LCD_writeStringXY(uint8_t row, uint8_t col, char *str)
{
	LCD_gotoXY(row, col);
	LCD_writeString(str);
}

void LCD_clearDisplay()
{
	LCD_writeCmdData(LCD_DISPLAY_CLEAR);
}