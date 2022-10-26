// Lic:
// Source/QuickInput.cpp
// Quick Input
// version: 22.10.26
// Copyright (C) 2022 Jeroen P. Broks
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
#include <iostream>
#include "../Headers/QuickInput.hpp"

using namespace std;

namespace TrickyUnits {
	string ReadLine(string Question) {
		string str;
		getline(cin, str);
		return str;
	}

	void CReadLine(char* ret, const char* Question) {
		if (!sizeof(ret)) return;
		auto _ret{ ReadLine(Question) };
		// strcpy_s(ret, _ret.c_str()); // Doesn't work for some odd reason. 
		int i = 0;
		do ret[i] = _ret[i]; while (_ret[++i] && i < sizeof(ret));
	}

}