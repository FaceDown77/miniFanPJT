#include "FND.h"

uint16_t fndData = 0;
uint8_t fndColonFlag = 0;

void FND_init()
{
	FND_DIGIT_DDR |= ((1<<FND_DIGIT_1) | (1<<FND_DIGIT_2) | (1<<FND_DIGIT_3) | (1<<FND_DIGIT_4));
	FND_DATA_DDR = 0xff;
}

void FND_colonOn()
{
	fndColonFlag = 1;
}

void FND_colonOff()
{
	fndColonFlag = 0;
}

void FND_dispNone()
{
	PORTE |= (1<<FND_DIGIT_1) | (1<<FND_DIGIT_2) | (1<<FND_DIGIT_3) | (1<<FND_DIGIT_4);	// 포트 출력을 한번 끊어주는 역할
	PORTF = 0x40;
	PORTE &= ~(1<<FND_DIGIT_1);
	PORTE &= ~(1<<FND_DIGIT_2);
	PORTE &= ~(1<<FND_DIGIT_3);
	PORTE &= ~(1<<FND_DIGIT_4);
}

void FND_dispNum(uint16_t fndNum)
{
	uint8_t fndFont[11] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67, 0x80};
	
	static uint8_t fndDigitState = 0;
	
	fndDigitState = (fndDigitState + 1) % 5;
	
	switch (fndDigitState)
	{
		case 0:
		PORTE |= (1<<FND_DIGIT_1) | (1<<FND_DIGIT_2) | (1<<FND_DIGIT_3) | (1<<FND_DIGIT_4);	// 포트 출력을 한번 끊어주는 역할
		PORTF = fndFont[fndNum/1000%10];
		PORTE &= ~(1<<FND_DIGIT_1);
		//_delay_ms(1);
		break;
		case 1:
		PORTE |= (1<<FND_DIGIT_1) | (1<<FND_DIGIT_2) | (1<<FND_DIGIT_3) | (1<<FND_DIGIT_4);
		PORTF = fndFont[fndNum/100%10];
		PORTE &= ~(1<<FND_DIGIT_2);
		//_delay_ms(1);
		break;
		case 2:
		PORTE |= (1<<FND_DIGIT_1) | (1<<FND_DIGIT_2) | (1<<FND_DIGIT_3) | (1<<FND_DIGIT_4);
		PORTF = fndFont[fndNum/10%10];
		PORTE &= ~(1<<FND_DIGIT_3);
		//_delay_ms(1);
		break;
		case 3:
		PORTE |= (1<<FND_DIGIT_1) | (1<<FND_DIGIT_2) | (1<<FND_DIGIT_3) | (1<<FND_DIGIT_4);
		PORTF = fndFont[fndNum%10];
		PORTE &= ~(1<<FND_DIGIT_4);
		//_delay_ms(1);
		break;
		case 4:
		PORTE |= (1<<FND_DIGIT_1) | (1<<FND_DIGIT_2) | (1<<FND_DIGIT_3) | (1<<FND_DIGIT_4);
		if (fndColonFlag) PORTF = fndFont[10];
		else PORTF = 0x00;
		PORTE &= ~(1<<5);
		//_delay_ms(1);
		break;
	}
}

void FND_setFndData(uint16_t data)	// 전역변수인 fndData에다 매개변수로 전달받은 data를 집어넣는 용도
{
	fndData = data;
}

void FND_ISR_Process()
{
	FND_dispNum(fndData);
}