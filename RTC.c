#include "rtc.h"
#include "i2c.h"

void RTC_Init(void) {
	I2C_Init();
}

void RTC_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds){
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | 0); // Para escribir
	I2C_Write(0x00); // Empiezo en registro 0x00 (Segundos)
	I2C_Write(DEC_to_BCD(seconds));
	I2C_Write(DEC_to_BCD(minutes));
	I2C_Write(DEC_to_BCD(hours));
	I2C_Stop();
}

void RTC_GetTime(uint8_t* hours, uint8_t* minutes, uint8_t* seconds) {
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | 0); // Para escribir
	I2C_Write(0x00); // Empiezo en registro 0x00 (Segundos)
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | 1); // Para leer

	*seconds = BCD_to_DEC(I2C_Read(0));
	*minutes = BCD_to_DEC(I2C_Read(0));
	*hours = BCD_to_DEC(I2C_Read(1));

	I2C_Stop();
}

void RTC_SetDate(uint8_t day, uint8_t month, uint8_t year){
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | 0); // Para escribir
	I2C_Write(0x04); // Empiezo en registro 0x04 (Dia)
	I2C_Write(DEC_to_BCD(day));
	I2C_Write(DEC_to_BCD(month));
	I2C_Write(DEC_to_BCD(year));
	I2C_Stop();
}

void RTC_GetDate(uint8_t* day, uint8_t* month, uint8_t* year) {
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | 0); // Para escribir
	I2C_Write(0x04); // Empiezo en registro 0x04 (Dia)
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | 1); // Para leer

	*day = BCD_to_DEC(I2C_Read(0));
	*month = BCD_to_DEC(I2C_Read(0));
	*year = BCD_to_DEC(I2C_Read(1));

	I2C_Stop();
}

uint8_t BCD_to_DEC(uint8_t val) {
	return ((val / 16 * 10) + (val % 16));
}

uint8_t DEC_to_BCD(uint8_t val) {
	return ((val / 10 * 16) + (val % 10));
}