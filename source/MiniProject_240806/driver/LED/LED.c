#include "LED.h"

// init Function
void LED_init(volatile uint8_t* DDR)
{
	Gpio_initPort(DDR, OUTPUT);
}

// LED all off
void LED_allOff(volatile uint8_t* PORT)
{
	Gpio_writePort(PORT, 0x00);
}

// LED all on
void LED_allOn(volatile uint8_t* PORT)
{
	Gpio_writePort(PORT, 0xff);
}

// data 전달 받아서 그 data 값으로 불을 켜는 것
void LED_dataOn(volatile uint8_t* PORT, uint8_t data)
{
	Gpio_writePort(PORT, data);
}