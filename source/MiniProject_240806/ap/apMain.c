#include "apMain.h"


ISR (TIMER0_OVF_vect)
{
	uint8_t timerModeState;
	timerModeState = Model_getTimerModeStateData();
	if (timerModeState != TMOFF)
	{
		FND_ISR_Process();
	}
	else FND_dispNone();
	
	TCNT0 = 130;
}

ISR (TIMER2_COMP_vect)
{
	service_milisecProcess();
}

void apMain_init()
{
	Listener_init();
	Presenter_init();
	Timer0_init();
	Timer2_init();
	
	sei();
	
	Model_setFanModeStateData(MODE_OFF);
	Model_setTimerModeStateData(TMOFF);
	Model_setTimerFlagData(FLAG_OFF);
}

void apMain_run()
{
	Listener_run();
	
	Presenter_motorOperating();
	
	service_fanModeCare();
	service_timerModeCare();
}