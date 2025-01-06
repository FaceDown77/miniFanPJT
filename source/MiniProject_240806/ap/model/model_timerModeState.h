#ifndef MODEL_TIMERMODESTATE_H_
#define MODEL_TIMERMODESTATE_H_

#define F_CPU 16000000UL
#include <avr/io.h>

enum {TMOFF = 10, TM1 = 11, TM2 = 12, TM3 = 13, TM_NONE = 19};

uint8_t Model_getTimerModeStateData();
void Model_setTimerModeStateData(uint8_t state);

#endif /* MODEL_TIMERMODESTATE_H_ */