#ifndef I2C_H
	#define I2C_H

	#include <avr/io.h>

	void I2C_Init(void);
	void I2C_Start(void);
	void I2C_Stop(void);
	void I2C_Write(uint8_t);
	uint8_t I2C_Read(uint8_t);

#endif // I2C_H