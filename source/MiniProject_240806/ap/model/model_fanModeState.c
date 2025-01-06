#include "model_fanModeState.h"

uint8_t fanModeStateData;

uint8_t Model_getFanModeStateData()
{
	return fanModeStateData;
}

void Model_setFanModeStateData(uint8_t state)
{
	fanModeStateData = state;
}