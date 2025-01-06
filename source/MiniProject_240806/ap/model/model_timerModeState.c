#include "model_timerModeState.h"

uint8_t timerModeStateData;

uint8_t Model_getTimerModeStateData()
{
	return timerModeStateData;
}

void Model_setTimerModeStateData(uint8_t state)
{
	timerModeStateData = state;
}