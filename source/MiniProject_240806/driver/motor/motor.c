#include "motor.h"


void Motor_init()
{
	// Timer/Counter 1 사용, Fast PWM mode, TOP ICR1, DutyCycle OCR1A, prescaler 1/64, Non-Inverting mode
	// Frequency : 1kHz, Duty Cycle : 50%
	
	TCCR1B |= ((0<<CS12) | (1<<CS11) | (1<<CS10));	// Prescaler 1/64
	TCCR1A |= (1<<WGM11) | (0<<WGM10); // Fast PWM - 14번 조합
	TCCR1B |= (1<<WGM13) | (1<<WGM12);
	
	DDRB |= (1<<5);	// 모터 부착 핀에 대한 Output mode
	
	Motor_setHertz(MOTOR_HERTZ);
	//Motor_setRotateMode(MOTOR3);
	Motor_rotateOff();
}

void Motor_rotateOn()
{
	TCCR1A |= (1<<COM1A1) | (0<<COM1A0);	// COM Bit를 활성화, Non-Inverting mode
}

void Motor_rotateOff()
{
	TCCR1A &= ~((1<<COM1A1) | (1<<COM1A0));	// COM Bit가 비활성화 되면 출력되던 PWM이 차단
}

// 권장 헤르츠 20kHz ~ 80kHz
void Motor_setHertz(uint32_t hertz)
{
	if (hertz < 20000) hertz = 20000;
	else if (hertz > 80000) hertz = 80000;
	
	MOTOR_ICR = (hertz / 4) - 1;
}

void Motor_setRotateMode(uint8_t modeData)
{
	switch (modeData)
	{
		case MOTOR1:
		MOTOR_OCR = (MOTOR_ICR / 10) * 4;
		break;
		
		case MOTOR2:
		MOTOR_OCR = (MOTOR_ICR / 10) * 7;
		break;
		
		case MOTOR3:
		MOTOR_OCR = (MOTOR_ICR / 10) * 10;
		break;
		
		case MOTOR4:
		MOTOR_OCR = (MOTOR_ICR / 10) * 2;
		break;
	}
}