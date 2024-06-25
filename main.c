#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "serialPort.h"
#include "DHT11.h"
#include "RTC.h"
#include "TIMER1.h"

#define BR9600 (0x67)	// 0x67=103 configura BAUDRATE=9600@16MHz

//comunicación con la ISR
volatile char RX_Buffer=0;
volatile uint8_t stop = 1;

//RTC
uint8_t hours, minutes, seconds;
uint8_t day, month, year;

//DHT11
uint8_t humedad;
uint8_t temperatura;
uint8_t sensor_ok;

uint8_t mostrar=0;

char msg[100];

int main(void)
{
	SerialPort_Init(BR9600); 			// Inicializo formato 8N1 y BAUDRATE = 9600bps
	SerialPort_TX_Enable();				// Activo el Transmisor del Puerto Serie
	SerialPort_RX_Enable();				// Activo el Receptor del Puerto Serie
	SerialPort_RX_Interrupt_Enable();	// Activo Interrupción de recepcion.
	Timer1_Init();
	DHT11_init();
	RTC_Init();

	// Fecha y hora
	RTC_SetDate(24,6,24);	// FECHA= 24/06/24
	RTC_SetTime(14,30,12);	// HORA= 14:30:12
	
	sei();					// Activo la mascara global de interrupciones (Bit I del SREG en 1)
	
	while(1)
	{	
		//Encuesto sensor cada 2seg
		if (getFlag_2segundos()){
			sensor_ok = DHT11_read(&temperatura,&humedad);
			RTC_GetDate(&day,&month,&year);
			RTC_GetTime(&hours,&minutes,&seconds);
			setFlag_2segundos(0);
			mostrar=1;
		}
		if(stop && mostrar){
			if(sensor_ok == 1){		
				sprintf(msg, "TEMP:%2d°C HUM:%2d FECHA:%d/%d/%d HORA:%2d:%2d:%2d \r\n",temperatura,humedad,day,month,year,hours,minutes,seconds);
				SerialPort_Send_String(msg);
			}
			mostrar=0;
		}
	}
	return 0;
}

ISR(USART_RX_vect){
	RX_Buffer = UDR0;
	if((RX_Buffer == 's')||(RX_Buffer == 'S')){
		if(stop){
			SerialPort_Send_String("PAUSADO  \r\n");
			stop = 0;
		} else {
			stop = 1;
		}
	}
}


