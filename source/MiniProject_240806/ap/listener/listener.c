#include "listener.h"

// UART Interrupt Service Routine
ISR (USART0_RX_vect)
{
	UART0_ISR_Process();
}


/////////////////////// Button var ///////////////////////
button_t btn0_stop, btn1_dn, btn2_up, btn3_sp, btn4_tm;

/////////////////////// UART var ///////////////////////
extern volatile uint8_t rear;	// interrupt에서 queue에 data를 저장하는 위치값
extern volatile uint8_t front;	// while(1)에서 가져가는 위치값
extern volatile unsigned char rx_buff[QUEUE_SIZE][QUEUE_LENGTH];
FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);

static uint8_t uartInputData = FNONE;


void Listener_init()
{
	Button_init(&btn0_stop, &BT_DDR, &BT_PIN, BT0_PINNUM);
	Button_init(&btn1_dn, &BT_DDR, &BT_PIN, BT1_PINNUM);
	Button_init(&btn2_up, &BT_DDR, &BT_PIN, BT2_PINNUM);
	Button_init(&btn3_sp, &BT_DDR, &BT_PIN, BT3_PINNUM);
	Button_init(&btn4_tm, &BT_DDR, &BT_PIN, BT4_PINNUM);
	UART0_init();
	Queue_init();
	
	uartInputData = FNONE;
}

void Listener_run()
{
	Listener_inputFanEventCheck();
	Listener_inputTmEventCheck();
	Listener_uartEventCheck();
}

void Listener_inputFanEventCheck()
{
	uint8_t fanEventStateData;
	fanEventStateData = Model_getFanModeStateData();
	
	switch (fanEventStateData)
	{
		case MODE_OFF:
		if ((Button_getState(&btn0_stop) == ACT_PUSHED) || (uartInputData == FSTOP))
		{
			fanEventStateData = MODE_OFF;
			uartInputData = FNONE;
			Model_setFanModeStateData(fanEventStateData);
		}
		else if ((Button_getState(&btn1_dn) == ACT_PUSHED) || (uartInputData == FDOWN))
		{
			fanEventStateData = MODE_OFF;
			uartInputData = FNONE;
			Model_setFanModeStateData(fanEventStateData);
		}
		else if ((Button_getState(&btn2_up) == ACT_PUSHED) || (uartInputData == FUP))
		{
			fanEventStateData = MODE_1;
			uartInputData = FNONE;
			Model_setFanModeStateData(fanEventStateData);
		}
		else if ((Button_getState(&btn3_sp) == ACT_PUSHED) || (uartInputData == FSP))
		{
			fanEventStateData = MODE_SP;
			uartInputData = FNONE;
			Model_setFanModeStateData(fanEventStateData);
		}
		break;
		
		case MODE_1:
		if ((Button_getState(&btn0_stop) == ACT_PUSHED) || (uartInputData == FSTOP))
		{
			fanEventStateData = MODE_OFF;
			uartInputData = FNONE;
			Model_setFanModeStateData(fanEventStateData);
		}
		else if ((Button_getState(&btn1_dn) == ACT_PUSHED) || (uartInputData == FDOWN))
		{
			fanEventStateData = MODE_OFF;
			uartInputData = FNONE;
			Model_setFanModeStateData(fanEventStateData);
		}
		else if ((Button_getState(&btn2_up) == ACT_PUSHED) || (uartInputData == FUP))
		{
			fanEventStateData = MODE_2;
			uartInputData = FNONE;
			Model_setFanModeStateData(fanEventStateData);
		}
		else if ((Button_getState(&btn3_sp) == ACT_PUSHED) || (uartInputData == FSP))
		{
			fanEventStateData = MODE_SP;
			uartInputData = FNONE;
			Model_setFanModeStateData(fanEventStateData);
		}
		break;
		
		case MODE_2:
		if ((Button_getState(&btn0_stop) == ACT_PUSHED) || (uartInputData == FSTOP))
		{
			fanEventStateData = MODE_OFF;
			uartInputData = FNONE;
			Model_setFanModeStateData(fanEventStateData);
		}
		else if ((Button_getState(&btn1_dn) == ACT_PUSHED) || (uartInputData == FDOWN))
		{
			fanEventStateData = MODE_1;
			uartInputData = FNONE;
			Model_setFanModeStateData(fanEventStateData);
		}
		else if ((Button_getState(&btn2_up) == ACT_PUSHED) || (uartInputData == FUP))
		{
			fanEventStateData = MODE_3;
			uartInputData = FNONE;
			Model_setFanModeStateData(fanEventStateData);
		}
		else if ((Button_getState(&btn3_sp) == ACT_PUSHED) || (uartInputData == FSP))
		{
			fanEventStateData = MODE_SP;
			uartInputData = FNONE;
			Model_setFanModeStateData(fanEventStateData);
		}
		break;
		
		case MODE_3:
		if ((Button_getState(&btn0_stop) == ACT_PUSHED) || (uartInputData == FSTOP))
		{
			fanEventStateData = MODE_OFF;
			uartInputData = FNONE;
			Model_setFanModeStateData(fanEventStateData);
		}
		else if ((Button_getState(&btn1_dn) == ACT_PUSHED) || (uartInputData == FDOWN))
		{
			fanEventStateData = MODE_2;
			uartInputData = FNONE;
			Model_setFanModeStateData(fanEventStateData);
		}
		else if ((Button_getState(&btn2_up) == ACT_PUSHED) || (uartInputData == FUP))
		{
			fanEventStateData = MODE_OFF;
			uartInputData = FNONE;
			Model_setFanModeStateData(fanEventStateData);
		}
		else if ((Button_getState(&btn3_sp) == ACT_PUSHED) || (uartInputData == FSP))
		{
			fanEventStateData = MODE_SP;
			uartInputData = FNONE;
			Model_setFanModeStateData(fanEventStateData);
		}
		break;
		
		case MODE_SP:
		if ((Button_getState(&btn0_stop) == ACT_PUSHED) || (uartInputData == FSTOP))
		{
			fanEventStateData = MODE_OFF;
			uartInputData = FNONE;
			Model_setFanModeStateData(fanEventStateData);
		}
		else if ((Button_getState(&btn3_sp) == ACT_PUSHED) || (uartInputData == FSP))
		{
			fanEventStateData = MODE_SP;
			uartInputData = FNONE;
			Model_setFanModeStateData(fanEventStateData);
		}
		break;
	}
}

void Listener_inputTmEventCheck()
{
	uint8_t timerModeStateData;
	timerModeStateData = Model_getTimerModeStateData();
	
	switch (timerModeStateData)
	{
		case TMOFF:
		if ((Button_getState(&btn4_tm) == ACT_PUSHED) || (uartInputData == FTM))
		{
			timerModeStateData = TM1;
			uartInputData = TM_NONE;
			Model_setTimerModeStateData(timerModeStateData);
		}
		break;
		
		case TM1:
		if ((Button_getState(&btn4_tm) == ACT_PUSHED) || (uartInputData == FTM))
		{
			timerModeStateData = TM2;
			uartInputData = TM_NONE;
			Model_setTimerModeStateData(timerModeStateData);
		}
		break;
		
		case TM2:
		if ((Button_getState(&btn4_tm) == ACT_PUSHED) || (uartInputData == FTM))
		{
			timerModeStateData = TM3;
			uartInputData = TM_NONE;
			Model_setTimerModeStateData(timerModeStateData);
		}
		break;
		
		case TM3:
		if ((Button_getState(&btn4_tm) == ACT_PUSHED) || (uartInputData == FTM))
		{
			timerModeStateData = TMOFF;
			uartInputData = TM_NONE;
			Model_setTimerModeStateData(timerModeStateData);
		}
		break;
	}
}

void Listener_uartEventCheck()
{
	if (front != rear)	// data가 rx_buff에 존재
	{
		printf("%s", rx_buff[front]);
		if (!strcmp((char *) rx_buff[front], "FAN_STOP\n"))
		{
			uartInputData = FSTOP;
		}
		else if (!strcmp((char *) rx_buff[front], "FAN_DOWN\n"))
		{
			uartInputData = FDOWN;
		}
		else if (!strcmp((char *) rx_buff[front], "FAN_UP\n"))
		{
			uartInputData = FUP;
		}
		else if (!strcmp((char *) rx_buff[front], "FAN_SPECIAL\n"))
		{
			uartInputData = FSP;
		}
		else if (!strcmp((char *) rx_buff[front], "FAN_TIMER\n"))
		{
			uartInputData = FTM;
		}
		
		front++;
		front %= QUEUE_SIZE;
	}
}