#ifndef FND_H_
#define FND_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define FND_DIGIT_DDR	DDRE
#define FND_DATA_DDR	DDRF
#define FND_DIGIT_1		4		// 1000의 자리
#define FND_DIGIT_2		5		// 100의 자리
#define FND_DIGIT_3		6		// 10의 자리
#define FND_DIGIT_4		7		// 1의 자리

void FND_init();
void FND_colonOn();
void FND_colonOff();
void FND_dispNone();
void FND_dispNum(uint16_t fndNum);
void FND_setFndData(uint16_t data);
void FND_ISR_Process();

#endif /* FND_H_ */