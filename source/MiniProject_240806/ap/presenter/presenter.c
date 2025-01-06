#include "presenter.h"

uint8_t fanModeState;

char lcdArray1[5][4] = {"OFF", "01 ", "02 ", "03 ", "SP "};
char lcdArray2[5][4] = {"OFF", "-1-", "-2-", "-3-"};


void Presenter_init()
{
	FND_init();
	LCD_init();
	Buzzer_init();
	Motor_init();
}

void Presenter_dispEventProcess(uint16_t timerSec)
{
	static uint8_t prevState;
	uint8_t timerModeState, flagData;
	uint16_t timerData;
	
	prevState = TM_NONE;
	timerModeState = Model_getTimerModeStateData();
	fanModeState = Model_getFanModeStateData();
	flagData = Model_getTimerFlagData();
	
	//LCD Display Part
	char buff[30];
	sprintf(buff, "[Table Mini Fan]");
	LCD_writeStringXY(0, 0, buff);
	sprintf(buff, "FAN %s,Timer%s", lcdArray1[fanModeState], lcdArray2[timerModeState-10]);
	LCD_writeStringXY(1, 0, buff);
	
	
	//FND Display Part
	switch (timerModeState)
	{
		case TMOFF:
		if (timerModeState != prevState)
		{
			prevState = timerModeState;
		}
		break;
		
		case TM1:
		if (timerModeState != prevState)
		{
			prevState = timerModeState;
		}
		timerData = ((timerSec / 60) * 100) + (timerSec % 60);
		FND_setFndData(timerData);
		
		if (timerSec <= 0)
		{
			timerModeState = TMOFF;
			Model_setTimerModeStateData(timerModeState);
			flagData = FLAG_ON;
			Model_setTimerFlagData(flagData);
		}
		break;
		
		case TM2:
		if (timerModeState != prevState)
		{
			prevState = timerModeState;
		}
		timerData = ((timerSec / 60) * 100) + (timerSec % 60);
		FND_setFndData(timerData);
		
		if (timerSec <= 0)
		{
			timerModeState = TMOFF;
			Model_setTimerModeStateData(timerModeState);
			flagData = FLAG_ON;
			Model_setTimerFlagData(flagData);
		}
		break;
		
		case TM3:
		if (timerModeState != prevState)
		{
			prevState = timerModeState;
		}
		timerData = ((timerSec / 60) * 100) + (timerSec % 60);
		FND_setFndData(timerData);
		
		if (timerSec <= 0)
		{
			timerModeState = TMOFF;
			Model_setTimerModeStateData(timerModeState);
			flagData = FLAG_ON;
			Model_setTimerFlagData(flagData);
		}
		break;
	}
}

void Presenter_motorOperating()
{
	switch (fanModeState)
	{
		case 0:	//MODE_OFF , 정지
		Motor_rotateOff();
		break;
		
		case 1:	//MODE_1 , 약풍
		Motor_rotateOn();
		Motor_setRotateMode(MOTOR1);
		break;
		
		case 2:	//MODE_2 , 미풍
		Motor_rotateOn();
		Motor_setRotateMode(MOTOR2);
		break;
		
		case 3:	//MODE_3 , 강풍
		Motor_rotateOn();
		Motor_setRotateMode(MOTOR3);
		break;
		
		case 4:	//MODE_SP , 수면풍
		Motor_rotateOn();
		Motor_setRotateMode(MOTOR4);
		break;
	}
}
