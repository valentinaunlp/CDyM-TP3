#include "TIMER1.h"

static uint8_t FLAG_2segundos = 0;

void setFlag_2segundos(uint8_t Flag_2segundos){
	FLAG_2segundos = Flag_2segundos;
}

uint8_t getFlag_2segundos(){
	return FLAG_2segundos;
}

void Timer1_Init(void) {
	TCCR1B |= (1 << WGM12);
	OCR1A = 249;
	TIMSK1 |= (1 << OCIE1A);
	TCCR1B |= (1 << CS11) | (1 << CS10);
}

ISR(TIMER1_COMPA_vect) {
	static uint16_t contador_2segundos = 0;
	if (++contador_2segundos == 2000) {
		FLAG_2segundos = 1;
		contador_2segundos = 0;
	}
}