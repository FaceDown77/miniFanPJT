#ifndef APMAIN_H_
#define APMAIN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "listener/listener.h"
#include "presenter/presenter.h"
#include "model/model_fanModeState.h"
#include "model/model_timerModeState.h"
#include "model/model_timerSecNFlag.h"
#include "service/service_fanModeCare.h"
#include "service/service_timerModeCare.h"
#include "../periph/timer/TIM.h"

void apMain_init();
void apMain_run();

#endif /* APMAIN_H_ */