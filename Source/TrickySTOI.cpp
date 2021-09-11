// Lic:
// Source/TrickySTOI.cpp
// Tricky's String To Int
// version: 21.09.11
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
#undef TrickySTOI_DEBUG
#ifdef TrickySTOI_DEBUG
#include <iostream>
#endif
#include <string>
#include "../Headers/QuickString.hpp"
#include <math.h>

namespace TrickyUnits {
int TrueToInt(std::string str,int scale) {
	if (!str.size()) return 0;
	if (scale>16 || scale<2) return 0; // Invalid scale	
	int l = str.size()-1;
	auto s = Upper(str);
	int ret{0};
	for (int p=0;p<=l;++p){
		int digi{0};
		auto ch=s[l-p];
		if (ch>='0' && ch<='9') digi=(int)ch-48;
		else if (ch>='A' && ch<='F') digi=(int)ch-55;
		if (digi>=scale) return 0;
		if (p==0)
			ret = digi;
		else
			ret += digi * (pow(scale,p));
	}
	return ret;
}

int ToInt(std::string s) {
	if (!s.size()) return 0;
	s = Trim(s);
	if (!s.size()) return 0;
	auto r = right(s,s.size()-1);
	switch (s[0]) {
		case '-':	return -TrueToInt(r,10);
		case '$':
		case 'x':	return TrueToInt(r,16);
		case '%':
		case 'b':	return TrueToInt(r,2);
		case 'o':	return TrueToInt(r,8);
		default:	return TrueToInt(s,10);
	}
}

unsigned int ToUInt(std::string s){
	if (!s.size()) return 0;
	s = Trim(s);
	if (!s.size()) return 0;
	auto r = right(s, s.size() - 1);
	switch (s[0]) {
	case '$':
	case 'x':	return (unsigned int)TrueToInt(r, 16);
	case '%':
	case 'b':	return (unsigned int)TrueToInt(r, 2);
	case 'o':	return (unsigned int)TrueToInt(r, 8);
	default:	return (unsigned int)TrueToInt(s, 10);
	}
}





}

#ifdef TrickySTOI_DEBUG
using namespace TrickyUnits;
int main(int an,char** A){
	std::cout << TrueToInt("123",10) <<"\n";
	std::cout << TrueToInt("3F",16)<<"\n";
	std::cout << ToInt("10") << "\t" << ToInt("$10") << "\t" << ToInt("o10") << "\t" << ToInt("b10") << "\t"<<ToInt("-10") << std::endl;
	std::cout << ToInt("b11111111")<<"\n";
}
#endif