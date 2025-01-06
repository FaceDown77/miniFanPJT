#ifndef MODEL_FANMODESTATE_H_
#define MODEL_FANMODESTATE_H_

#define F_CPU 16000000UL
#include <avr/io.h>

enum {MODE_OFF, MODE_1, MODE_2, MODE_3, MODE_SP, MODE_NONE = 9};

uint8_t Model_getFanModeStateData();
void Model_setFanModeStateData(uint8_t state);

#endif /* MODEL_FANMODESTATE_H_ */