#include "TIM.h"

void Timer0_init()	// 1ms overflow interrupt , FND Display
{
	// 8bit 0번 인터럽트 발생용
	// 128분주기, interrupt per 1ms
	TCCR0 |= ((1<<CS02) | (0<<CS01) | (1<<CS00));	// 128 prescaler 설정
	TIMSK |= (1<<TOIE0);							// Timer/Counter0 overflow Mask 설정
	TCNT0 = 130;									// 이건 ISR에도 넣어주면 된다.
}

void Timer2_init()
{
	// Timer/Counter2 의 1/64(011) 1ms period interrupt , CTC mode
	
	// 1/64 prescaler
	TCCR2 |= ((0<<CS22) | (1<<CS21) | (1<<CS20));
	
	// Mask 설정
	TIMSK |= (1<<OCIE2);
	
	// CTC mode
	TCCR2 |= ((1<<WGM21) | (0<<WGM20));
	
	// OCR 설정
	OCR2 = 250-1;
}