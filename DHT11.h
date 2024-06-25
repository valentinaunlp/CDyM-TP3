#ifndef DHT11_H_
	#define DHT11_H_

	#define F_CPU 16000000UL
	#include <stdlib.h>
	#include <stdio.h>
	#include <util/delay.h>
	#include <avr/io.h>
	#include <avr/interrupt.h>

	#define DHT_DDR DDRC
	#define DHT_PORT PORTC
	#define DHT_PIN PINC
	#define PIN PINC0

	void DHT11_init();
	uint8_t DHT11_read(uint8_t *temperatura, uint8_t *humedad);

#endif /* DHT11_H_ */