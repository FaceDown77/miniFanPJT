#ifndef SERVICE_FANMODECARE_H_
#define SERVICE_FANMODECARE_H_

#define F_CPU 16000000UL
#include <avr/io.h>

#include "../model/model_fanModeState.h"
#include "../model/model_timerModeState.h"

void service_fanModeCare();

#endif /* SERVICE_FANMODECARE_H_ */