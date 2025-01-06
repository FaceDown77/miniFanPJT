#ifndef UART0_QUEUE_H_
#define UART0_QUEUE_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define QUEUE_SIZE 10
#define QUEUE_LENGTH 80

void UART0_init();
void Queue_init();
uint8_t Queue_empty();
uint8_t Queue_full();
void Queue_enQueue(uint8_t data, volatile uint8_t *index);
uint8_t Queue_deQueue();
void Queue_logic(uint8_t data, volatile uint8_t *index);
void UART0_ISR_Process();
void UART0_clearRxFlag();
void UART0_setRxFlag();
uint8_t UART0_getRxFlag();
uint8_t* UART0_readRxBuff();
void UART0_transmit(unsigned char data);
unsigned char UART0_receive(void);
void UART0_transmitString(char * str);
uint8_t UART0_Avail();

#endif /* UART0_QUEUE_H_ */