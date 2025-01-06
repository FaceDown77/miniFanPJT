#include "service_fanModeCare.h"

void service_fanModeCare()
{
	uint8_t fanState;
	fanState = Model_getFanModeStateData();
	static uint8_t prevState = MODE_NONE;
	switch (fanState)
	{
		case MODE_OFF:
		if (fanState != prevState)
		{
			prevState = fanState;
			Model_setTimerModeStateData(TMOFF);
		}
		break;
		
		case MODE_1:
		if (fanState != prevState)
		{
			prevState = fanState;
		}
		break;
		
		case MODE_2:
		if (fanState != prevState)
		{
			prevState = fanState;
		}
		break;
		
		case MODE_3:
		if (fanState != prevState)
		{
			prevState = fanState;
		}
		break;
		
		case MODE_SP:
		if (fanState != prevState)
		{
			prevState = fanState;
		}
		break;
	}
}
