#include "model_timerSecNFlag.h"

uint8_t flagData;

uint8_t Model_getTimerFlagData()
{
	return flagData;
}

void Model_setTimerFlagData(uint8_t data)
{
	flagData = data;
}