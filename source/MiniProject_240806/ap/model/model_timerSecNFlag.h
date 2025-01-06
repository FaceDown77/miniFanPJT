#ifndef MODEL_TIMERSECNFLAG_H_
#define MODEL_TIMERSECNFLAG_H_

#define F_CPU 16000000UL
#include <avr/io.h>

enum flag {FLAG_OFF, FLAG_ON};

uint8_t Model_getTimerFlagData();
void Model_setTimerFlagData(uint8_t data);

#endif /* MODEL_TIMERSECNFLAG_H_ */