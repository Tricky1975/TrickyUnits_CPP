// Lic:
// Headers/QuickString.h
// Quick String
// version: 20.08.20
// Copyright (C) 2020 Jeroen P. Broks
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
#ifndef TRICKYINIT_INCLUDED_QUICKSTRING


#define TRICKYINIT_INCLUDED_QUICKSTRING


#include <vector>

using namespace std;

namespace TrickyUnits {
	string mid(string str, unsigned int start = 1, unsigned int length = 1);
	string mid(string str, unsigned int start, unsigned int length, string newstring);
	string left(string str, unsigned int length = 1);
	string right(string str, unsigned int length = 1);

	// inline string qsleft(string str,unsigned int length=1) { return left( str, length=1); } // No longer needed -- For some reason C++ didn't like the original definitions... :-/
	// inline string qsright(string str,unsigned int length=1) { return right(str, length=1); }

	bool prefixed(string str, string prefix);
	bool suffixed(string str, string suffix);


	string StripExt(string file);
	int findlast(string str, char ch);
	int findlast(string haystack, string needle);
	string TReplace(string mystr, char ori, char subst);
	vector<string> Split(string str, char spltchar);
	/// <summary>
	/// Splits a string into lines. WARNING! Please note this routine is only compatible with Unix LF and Windows CRLF. Systems using only CR will just lead to on big string with all their new lines removed.
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	vector<string> StringToLines(string str);
}
#endif