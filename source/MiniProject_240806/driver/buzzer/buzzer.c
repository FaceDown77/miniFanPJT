#include "buzzer.h"

void Buzzer_init()
{
	// Timer/Counter 3 사용, Fast PWM mode, TOP ICR3, DutyCycle OCR3A, prescaler 1/64, Non-Inverting mode
	// Frequency : 1kHz, Duty Cycle : 50%
	
	TCCR3B |= ((0<<CS32) | (1<<CS31) | (1<<CS30));	// Prescaler 1/64
	TCCR3A |= (1<<WGM31) | (0<<WGM30); // Fast PWM - 14번 조합
	TCCR3B |= (1<<WGM33) | (1<<WGM32);
}

void Buzzer_soundOn()
{
	TCCR3A |= (1<<COM3A1) | (0<<COM3A0);	// COM Bit를 활성화, Non-Inverting mode
}

void Buzzer_soundOff()
{
	TCCR3A &= ~((1<<COM3A1) | (1<<COM3A0));	// COM Bit가 비활성화 되면 출력되던 PWM이 차단
}

// 가청 주파수 20 ~ 20kHz
void Buzzer_makeHertz(uint16_t hertz)
{
	if (hertz < 100) hertz = 100;
	else if (hertz > 5000) hertz = 5000;
	
	BUZZER_ICR = (250000 / hertz) - 1;
	BUZZER_OCR = BUZZER_ICR / 2;
	
	//BUZZER_ICR = 250000 / 1 - 1;			// Frequency : 1Hz -> 1s, TOP Value
	//BUZZER_ICR = 250000 / 10 - 1;			// Frequency : 10Hz -> 0.1s, TOP Value
	//BUZZER_ICR = 250000 / 100 - 1;		// Frequency : 100Hz -> 0.1s, TOP Value
	//BUZZER_ICR = 250000 / 500 - 1;		// Frequency : 500Hz -> 0.5ms, TOP Value
	//BUZZER_ICR = 250000 / 1000 - 1;		// Frequency : 1kHz -> 1ms, TOP Value
	//BUZZER_ICR = 250000 / 10000 - 1;		// Frequency : 10kHz -> 0.1ms, TOP Value
	//BUZZER_ICR = 25 - 1;					// Frequency : 10kHz -> 0.1ms, TOP Value
	
	//BUZZER_OCR = ICR3 / 2;	// Duty Cycle 50%, 기준값을 중간부로 설정
}

void Buzzer_buttonOn()
{
	Buzzer_makeHertz(1046);	// 6옥 도 - 1046
	_delay_ms(500);
	TCNT3 = 0;
	Buzzer_makeHertz(1318);	// 6옥 미 - 1318
	_delay_ms(500);
	TCNT3 = 0;
	Buzzer_makeHertz(1567);	// 6옥 솔 - 1567
	_delay_ms(500);
	TCNT3 = 0;
	Buzzer_makeHertz(2093);	// 7옥 도 - 2093
	_delay_ms(500);
	TCNT3 = 0;
}

void Buzzer_music1()
{
	Buzzer_makeHertz(700);
	_delay_ms(200);
	TCNT3 = 0;
	Buzzer_makeHertz(1500);
	_delay_ms(200);
	TCNT3 = 0;
}