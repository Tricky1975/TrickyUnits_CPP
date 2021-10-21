#include "..\Headers\TrickyTime.hpp"
#include <iostream>

using namespace std;

namespace TrickyUnits {
	union tc {
		char str[256];
		time_t raw;
	};

	/*
	std::string TrickyUnits::GetTimeBuff() {
		tc t;
		time(&t.raw);
		return t.str;
	}
	*/

	// Avoid Microsoft's "unsafe" whinings.
	 
	tm _localtime(time_t* fuck) {
		tm r;
		//cout << fuck << "\n";
		localtime_s(&r, fuck)			;
		//cout << "well?\n";
		//localtime(fuck);
		return r;
	}

	tm LocalTime() {
		time_t t;
		time(&t);
		return _localtime(&t);		
	}

	string CurrentDate() {
		time_t t;
		char buff[256];		
		time(&t);		
		strftime(buff, 256, "%d %b %Y", &_localtime(&t));
		//cout << "Out date\n";
		return buff;
	}

	string CurrentTime() {
		time_t t;
		char buff[256];
		time(&t);
		strftime(buff, 256, "%H:%M:%S", &_localtime(&t));
		//cout << "Out Time\n";
		return buff;
	}
	std::string QTimeF(const char* f) {
		time_t t;
		char buff[256];
		time(&t);
		strftime(buff, 256, f, &_localtime(&t));
		return buff;		
	}


}