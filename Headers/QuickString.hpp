// Lic:
// Headers/Quickstd::string.h
// Quick std::string
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
#include <string>


namespace TrickyUnits {
	std::string mid(std::string str, unsigned int start = 1, unsigned int length = 1);
	std::string mid(std::string str, unsigned int start, unsigned int length, std::string newstring);
	std::string left(std::string str, unsigned int length = 1);
	std::string right(std::string str, unsigned int length = 1);

	// inline std::string qsleft(std::string str,unsigned int length=1) { return left( str, length=1); } // No longer needed -- For some reason C++ didn't like the original definitions... :-/
	// inline std::string qsright(std::string str,unsigned int length=1) { return right(str, length=1); }

	bool prefixed(std::string str, std::string prefix);
	bool suffixed(std::string str, std::string suffix);


	std::string StripExt(std::string file);
	int findlast(std::string str, char ch);
	int findlast(std::string haystack, std::string needle);

	/// <summary>
	/// Looks up first occurance of a character in a std::string
	/// </summary>
	/// <param name="str">The haystack</param>
	/// <param name="ch">The needle</param>
	/// <returns>Position number (from 0) or -1 when non-existent</returns>
	int findfirst(std::string str, char ch);
	std::string TReplace(std::string mystr, char ori, char subst);
	std::vector<std::string> Split(std::string str, char spltchar);
	/// <summary>
	/// Splits a std::string into lines. WARNING! Please note this routine is only compatible with Unix LF and Windows CRLF. Systems using only CR will just lead to on big std::string with all their new lines removed.
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	std::vector<std::string> StringToLines(std::string str);

	/// <summary>
	/// Quick and dirty trimming function
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	std::string Trim(std::string str);

	void Trans2Upper(std::string &str);

	/// <summary>
	/// Gives uppercase version of a std::string. Please note "Trans2Upper" replaces the original std::string. If that is not what you want, this function copies the std::string and turns that to upper case in stead!
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	std::string Upper(std::string str);
}
#endif