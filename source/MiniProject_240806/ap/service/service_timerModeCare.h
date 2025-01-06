#ifndef SERVICE_TIMERMODECARE_H_
#define SERVICE_TIMERMODECARE_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#include "../model/model_fanModeState.h"
#include "../model/model_timerModeState.h"
#include "../model/model_timerSecNFlag.h"
#include "../presenter/presenter.h"

void service_milisecProcess();
void service_timerModeCare();

#endif /* SERVICE_TIMERMODECARE_H_ */