#ifndef MOTOR_H_
#define MOTOR_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define MOTOR_ICR	ICR1
#define MOTOR_OCR	OCR1A
#define MOTOR_HERTZ	50000

enum dutyCycleSet {MOTOR1, MOTOR2, MOTOR3, MOTOR4};

void Motor_init();
void Motor_rotateOn();
void Motor_rotateOff();
void Motor_setHertz(uint32_t hertz);
void Motor_setRotateMode(uint8_t modeData);

#endif /* MOTOR_H_ */