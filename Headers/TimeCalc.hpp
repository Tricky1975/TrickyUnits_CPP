#pragma once
#include <string>

namespace TrickyUnits {
	
	typedef struct tqtime {
		unsigned char seconds;
		unsigned char minutes;
		unsigned char hours;
		unsigned int days;
	} tqtime;
	
	unsigned int toRawSecs(unsigned charhours,unsigned char minutes, unsigned char seconds);
	unsigned int toRawSecs(unsigned int days, unsigned char hours,unsigned char minutes, unsigned char seconds);
	
	void unRawSeconds(unsigned int raw,unsigned int *days,unsigned char *hours, unsigned char *minutes, unsigned char *seconds);
	void unRawSeconds(unsigned int raw,unsigned char *hours, unsigned char *minutes, unsigned char *seconds);
	tqtime unRawSeconds(unsigned int raw);
	
	std::string Digi(unsigned int raw);
	
	std::string Classic(unsigned int raw);
	std::string Classic(tqtime t);
}