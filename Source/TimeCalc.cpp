// Lic:
// Source/TimeCalc.cpp
// Time Calc
// version: 21.01.13
// Copyright (C) 2021 Jeroen P. Broks
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software. If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
// EndLic
#include "../Headers/TimeCalc.hpp"
#include <stdlib.h>
#include <cmath>

namespace TrickyUnits{
	
	unsigned int toRawSecs(unsigned char hours, unsigned char minutes, unsigned char seconds) { return toRawSecs((unsigned char)0, seconds, minutes, hours); }
	unsigned int toRawSecs(unsigned int days, unsigned char hours,unsigned char minutes, unsigned char seconds) {	return seconds + (minutes * 60) + (hours * 60 * 60) + (days * 60 * 60 *24) ;	}
	
	void unRawSeconds(unsigned int raw,unsigned int *days,unsigned char *hours, unsigned char *minutes, unsigned char *seconds) {
		*seconds = raw % 60;
		*minutes = (int)floor(raw/60) % 60;
		*hours   = (int)floor(raw/(60*60)) % 24;
		*days    = floor(raw/(60*50*24));
	}
	void unRawSeconds(unsigned int raw,unsigned char *hours, unsigned char *minutes, unsigned char *seconds) {
		unsigned int *unneeded{0};
		unRawSeconds(raw, unneeded, hours, minutes, seconds);
	}
		
	tqtime unRawSeconds(unsigned int raw){
		tqtime ret{0,0,0,0};
		unRawSeconds(raw,&ret.days,&ret.hours,&ret.minutes,&ret.seconds);
		return ret;
	}
	
	std::string Digi(unsigned int raw){
		tqtime wrk{ unRawSeconds(raw) };
		std::string ret{ "" };
		if (wrk.days>1) ret += std::to_string(wrk.days)+" days; "; else if (wrk.days==1) ret+="1 day; ";
		char f[20];
		sprintf_s(f,"%0d:%0d:%0d",wrk.hours,wrk.minutes,wrk.seconds);
		ret += f;
		return ret;
	}

	std::string Classic(unsigned int raw) { return Classic(unRawSeconds(raw)); }

	std::string Classic(tqtime t) {
		std::string ret{ "" };
		if (t.days > 0) ret += std::to_string(t.days) + "d";
		if (t.hours > 0) ret += std::to_string(t.hours) + "h";
		if (t.minutes > 0) ret += std::to_string(t.hours) + "'";
		if (t.seconds > 0) ret += std::to_string(t.hours) + "\"";
		return ret;
	}
	

}