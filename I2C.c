#include "i2c.h"
#include <util/twi.h>

void I2C_Init(void) {
	TWSR = 0x00;	// Prescaler en 0
	TWBR = 152;		// Frec SCL
	TWCR = 0x04;	// Enable TWI
}

void I2C_Start(void) {
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

void I2C_Stop(void) {
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

void I2C_Write(uint8_t data) {
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

uint8_t I2C_Read(uint8_t isLast) {
	if(isLast == 0)
		TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	else
		TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}