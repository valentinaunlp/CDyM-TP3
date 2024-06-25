#include "DHT11.h"

void DHT11_init(){
	DDRC |= (1<<PIN);	//P0 COMO SALIDA
	DHT_PORT |= (1<<PIN);	//NIVEL ALTO
}

uint8_t DHT11_read(uint8_t *temperatura, uint8_t *humedad){
	uint8_t bits[5];
	uint8_t listo=0;
	
/*			  18ms	  40us	 80us	 80us
		---|_______|-------|_______|------|...datos...   
		
		___________|__________________________________
			MCU					DHT11					*/
	
	//Paso 1, enviar un pulso en bajo durante 18ms
	DHT_PORT &= ~(1<<PIN); //Nivel bajo
	_delay_ms(18);
	DHT_PORT |= (1<<PIN); //Nivel alto
	DHT_DDR &= ~(1<<PIN); //Pin como entrada
	
	while(DHT_PIN & (1<<PIN)); ////Paso 2, esperamos 20 a 40us hasta que el DHT11 envíe 0
	while(!(DHT_PIN & (1<<PIN))); //Paso 3, esperamos 80us hasta que el DHT11 envie 1
	while(DHT_PIN & (1<<PIN)); //Paso 4, esperamos 80us hasta que el DHT11 envie 0
	
	//Paso 5, leemos los 5 bytes
	for(int j=0; j<5; j++){
		uint8_t result=0;
		for(int i=0; i<8; i++){
			while(!(DHT_PIN & (1<<PIN)));
			_delay_us(35);
			if(DHT_PIN & (1<<PIN)){
				result |= (1<<(7-i));
			}
			while(DHT_PIN & (1<<PIN));
		}
		bits[j]=result;
	}
	
	DHT_DDR |= (1<<PIN); //Pin como salida
	DHT_PORT |= (1<<PIN); //Nivel alto
	
	listo = bits[0] + bits[1] + bits[2] + bits[3];
	
	if (listo == bits[4]){
		*temperatura = bits[2];
		*humedad = bits[0];
		return 1;
	}
	else{
		return 0;
	}
}