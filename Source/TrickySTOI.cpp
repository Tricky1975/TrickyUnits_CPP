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

