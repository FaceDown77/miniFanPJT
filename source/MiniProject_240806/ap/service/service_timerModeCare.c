#include "service_timerModeCare.h"

uint16_t milisec, timerSec;


void service_milisecProcess()
{
	uint8_t timerState;
	timerState = Model_getTimerModeStateData();
	
	if (timerState == TMOFF) return;
	milisec = (milisec + 1) % 1000;
	
	if (milisec < 500) FND_colonOn();
	FND_colonOff();
	
	if (milisec) return;
	timerSec -= 1;
}

void service_timerModeCare()
{
	uint8_t timerState;
	uint8_t fanState;
	uint8_t tmFlag;
	timerState = Model_getTimerModeStateData();
	fanState = Model_getFanModeStateData();
	tmFlag = Model_getTimerFlagData();
	static uint8_t prevState = TM_NONE;
	
	switch (timerState)
	{
		case TMOFF:	//TIMER_OFF
		if (timerState != prevState)
		{
			prevState = timerState;
			timerSec = 0;
			
			if (tmFlag == FLAG_ON)
			{
				Model_setFanModeStateData(MODE_OFF);
				Model_setTimerFlagData(FLAG_OFF);
			}
		}
		break;
		
		case TM1:	//TIMER_1
		if (fanState == MODE_OFF)
		{
			Model_setTimerModeStateData(TMOFF);
			break;
		}
		if (timerState != prevState)
		{
			prevState = timerState;
			timerSec = 3;
		}
		break;
		
		case TM2:	//TIMER_2
		if (fanState == MODE_OFF)
		{
			Model_setTimerModeStateData(TMOFF);
			break;
		}
		if (timerState != prevState)
		{
			prevState = timerState;
			timerSec = 600;
		}
		break;
		
		case TM3:	//TIMER_3
		if (fanState == MODE_OFF)
		{
			Model_setTimerModeStateData(TMOFF);
			break;
		}
		if (timerState != prevState)
		{
			prevState = timerState;
			timerSec = 900;
		}
		break;
	}
	
	Presenter_dispEventProcess(timerSec);
}