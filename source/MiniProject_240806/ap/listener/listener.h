#ifndef LISTENER_H_
#define LISTENER_H_

#define F_CPU 16000000UL
#include <avr/io.h>

#include "../../periph/UART0/UART0_Queue.h"
#include "../../driver/button/Button.h"
#include "../model/model_fanModeState.h"
#include "../model/model_timerModeState.h"

#define BT_DDR		DDRA
#define BT_PIN		PINA
#define BT0_PINNUM	0
#define BT1_PINNUM	1
#define BT2_PINNUM	2
#define BT3_PINNUM	3
#define BT4_PINNUM	4

enum uartInput {FSTOP, FUP, FDOWN, FSP, FTM, FNONE};

void Listener_init();
void Listener_run();
void Listener_inputFanEventCheck();
void Listener_inputTmEventCheck();
void Listener_uartEventCheck();

#endif /* LISTENER_H_ */