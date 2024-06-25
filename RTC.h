#ifndef RTC_H
	#define RTC_H

	#include <stdint.h>

	#define DS3231_ADDRESS 0x68

	void RTC_Init(void);
	void RTC_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds);
	void RTC_GetTime(uint8_t* hours, uint8_t* minutes, uint8_t* seconds);
	void RTC_SetDate(uint8_t day, uint8_t month, uint8_t year);
	void RTC_GetDate(uint8_t* day, uint8_t* month, uint8_t* year);
	uint8_t BCD_to_DEC(uint8_t val);
	uint8_t DEC_to_BCD(uint8_t val);

#endif // RTC_H