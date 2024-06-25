#ifndef TIMER1_H

	#define TIMER1_H

	#include <avr/io.h>
	#include <avr/interrupt.h>


	#define F_CPU 16000000UL
	#define PRESCALER 64

	void Timer1_Init(void);
	void setFlag_2segundos(uint8_t Flag_2segundos);
	uint8_t getFlag_2segundos();

#endif