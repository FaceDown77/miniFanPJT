#ifndef PRESENTER_H_
#define PRESENTER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "../../driver/FND/FND.h"
#include "../../driver/LCD/LCD.h"
#include "../../driver/motor/motor.h"
#include "../../driver/buzzer/buzzer.h"
#include "../../periph/timer/TIM.h"
#include "../model/model_fanModeState.h"
#include "../model/model_timerModeState.h"
#include "../model/model_timerSecNFlag.h"

void Presenter_init();
void Presenter_dispEventProcess(uint16_t timerSec);
void Presenter_motorOperating();

#endif /* PRESENTER_H_ */