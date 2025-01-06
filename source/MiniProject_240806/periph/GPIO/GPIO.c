#include "GPIO.h"

// GPIO 기능?
// DDR 레지스터, PORT 레지스터, PIN 레지스터 사용했던것들
// DDR 1. Port에 대한 설정 / 2. pin에 대한 설정

void Gpio_initPort(volatile uint8_t* DDR, uint8_t mode)	// 포트 전체에 DDR 초기화 케이스
{
	// DDR
	// 어떤 포트의 DDR인지, Input 모드인지 Output 모드인지 => 매개변수 2종
	if (mode == OUTPUTMODE)
	{
		*DDR = 0xff;	// Output Mode
	}
	else
	{
		*DDR = 0x00;	// Input Mode
	}
}

void Gpio_initPin(volatile uint8_t* DDR, uint8_t mode, uint8_t pinNum)	// 특정 핀에 DDR 초기화 케이스
{
	// DDR
	// DDRA &= ~(1<<0);	// Intput 모드일때, 0번 핀
	// DDRD |= (1<<0);	// Output 모드일때, 0번 핀	=> 매개변수 3종 필요
	if (mode == OUTPUTMODE)
	{
		*DDR |= (1<<pinNum);	// Output Mode
	}
	else
	{
		*DDR &= ~(1<<pinNum);	// Input Mode
	}
}

void Gpio_writePort(volatile uint8_t* PORT, uint8_t data)	// 포트 전체에 쓰는 케이스
{
	*PORT = data;
}

void Gpio_writePin(volatile uint8_t* PORT, uint8_t pinNum, uint8_t state)	// 특정 핀에 쓰는 케이스
{
	// PORT |= (1<<0);	// 0도 출력이다. == 0을 내보낼 거냐, 1을 내보낼 거냐
	if (state == GPIO_PIN_SET)
	{
		*PORT |= (1<<pinNum);
	}
	else
	{
		*PORT &= ~(1<<pinNum);
	}
}

uint8_t Gpio_readPort(volatile uint8_t* PIN)	// 포트 전체를 읽어오는 케이스
{
	return *PIN;
}

uint8_t Gpio_readPin(volatile uint8_t* PIN, uint8_t pinNum)	// 특정 핀만 읽어오는 케이스
{
	return ((*PIN & (1<<pinNum)) != 0);	
	// 누르면?  ((Pushed : 0) != 0) == 거짓(0)
	// 안누르면?((Released : 1) != 0) == 참(1)
}