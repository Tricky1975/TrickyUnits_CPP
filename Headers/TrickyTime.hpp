#pragma once

#include <time.h>
#include <string>

namespace TrickyUnits {
	//std::string GetTimeBuff();
	std::string CurrentDate();
	std::string CurrentTime();
	std::string QTimeF(const char* f);
	tm _localtime(time_t* fuck);
	tm LocalTime();
}
