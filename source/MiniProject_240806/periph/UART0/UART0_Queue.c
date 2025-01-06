#include "UART0_Queue.h"

uint8_t uart0RxBuff[100];
uint8_t uart0RxFlag;

volatile uint8_t rear;	// interrupt에서 queue에 data를 저장하는 위치값
volatile uint8_t front;	// while(1)에서 가져가는 위치값
volatile unsigned char rx_buff[QUEUE_SIZE][QUEUE_LENGTH];


void UART0_init()
{
	// UART0, TxD, RxD, x2 mode, 9600 Baud Rate
	// 8bit Data bit, 1bit Stop bit, 'None' Parity bit -> Default Value
	
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);	// Receiver & Transmitter 를 Enable
	UCSR0A |= (1<<U2X0);	// x2 mode 를 ON
	UBRR0L = 207;	// 2배 모드의 9600 Baud Rate
	// 그 외 다른건 Default 사용
	UCSR0B |= (1<<RXCIE0);	// 1 byte Received Interrupt Enable
	
	uart0RxFlag = 0;
}

void Queue_init()
{
	rear = 0;
	front = 0;
}

uint8_t Queue_empty()
{
	if (rear == front) return 1;
	else return 0;
}

uint8_t Queue_full()
{
	if ((rear + 1) % QUEUE_SIZE == front) return 1;
	else return 0;
}

void Queue_enQueue(uint8_t data, volatile uint8_t *index)
{
	if (Queue_full())
	{
		printf("큐가 가득 찼습니다\n");
		return;
	}
	else
	{
		rx_buff[rear][*index] = data;
	}
}

uint8_t Queue_deQueue()
{
	if (Queue_empty())
	{
		return -1;
	}
	else
	{
		front = (front + 1) % QUEUE_SIZE;
		return rx_buff[front][0];
	}
}

void Queue_logic(uint8_t data, volatile uint8_t *index)
{
	if (data == '\n')
	{
		Queue_enQueue('\n', index);		// 개행문자 Newline을 만나면 NULL로 바꿔줌
		*index = 0;
		rear++;
		rear %= QUEUE_SIZE;				// if rear >= QUEUE_SIZE rear = 0;
	}
	else // \n 이 아닌 일반 문자일때
	{
		Queue_enQueue(data, index);
		*index = *index + 1;
	}
}

// LED1_TOGGLE\n
// LED2_TOGGLE\n
// LED3_TOGGLE\n
void UART0_ISR_Process()
{
	// circular queue
	volatile static	uint8_t i = 0;		// message length index
	uint8_t rx0Data = UDR0;		// UDR0 레지스터의 값을 복사해오면, UDR0 내의 값은 사라짐
	
	Queue_logic(rx0Data, &i);
}

void UART0_clearRxFlag()
{
	uart0RxFlag = 0;
}

void UART0_setRxFlag()
{
	uart0RxFlag = 1;
}

uint8_t UART0_getRxFlag()
{
	return uart0RxFlag;
}

uint8_t* UART0_readRxBuff()
{
	return uart0RxBuff;
}

// UART 송신용 함수
void UART0_transmit(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );	// xx1x xxxx or xx0x xxxx
	
	/* Put data into buffer, sends the data */
	UDR0 = data;
	
	// UDR이 비어있어야 while 문 탈출하여 UDR에 송신용 데이터를 얹음
}

// UART 수신용 함수
unsigned char UART0_receive(void)
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
	
	// 수신 완료시에 RXC가 ON 되고, while 탈출하여 UDR 값 리턴해줌
}

void UART0_transmitString(char * str)
{
	for (int i = 0; str[i]; i++)
	{
		UART0_transmit(str[i]);
	}
}

uint8_t UART0_Avail()
{
	if ( !(UCSR0A & (1<<RXC0)) )
	{
		return 0;	// RX 데이터가 없으면 0
	}
	return 1;	// RX 데이터가 있으면 1
}