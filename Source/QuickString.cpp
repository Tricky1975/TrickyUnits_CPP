// Lic:
// Source/QuickString.cpp
// Quick String
// version: 22.10.26
// Copyright (C) 2020, 2021, 2022 Jeroen P. Broks
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
#include <string>
#include <vector>
#include <algorithm>
#include <cstdarg>
#include <iostream>
// #include <iostream> 
#include "../Headers/QuickString.hpp"


// 3rd party
// #include "3rd_party/md5.hpp"

using namespace std;

namespace TrickyUnits {

	string mid(string str, unsigned int start, unsigned int length) {
		string ret = "";
		int istart = start - 1;
		if (start < 1) return ""; // NOT ALLOWED!!!
		for (int i = istart; i < istart + length && i < str.size(); i++) {
			ret += str[i];
		}
		return ret;
	}

	string mid(string str, unsigned int start, unsigned int length, string newstring) {
		string ret = str;
		int istart = start - 1;
		for (int i = 0; i < newstring.size(); i++) {
			if (i = ret.size())
				ret += newstring[i];
			else
				ret[i + istart] = newstring[i];
		}
		return ret;
	}

	string left(string str, unsigned int length) {
		return mid(str, 1, length);
	}

	string right(string str, unsigned int length) {
		if (length > str.size()) return str;
		return mid(str, (str.size() - length) + 1, length);
	}
	//string right(string str, size_t length) { return right(str, (unsigned int)length); }


	bool prefixed(string str, string prefix) {
		return left(str, prefix.size()) == prefix;
	}

	bool suffixed(string str, string suffix) {
		return right(str, suffix.size()) == suffix;
	}

	/// <summary>
	/// Find last occurance of a character in a string
	/// </summary>
	/// <param name="str"></param>
	/// <param name="ch"></param>
	/// <returns>The index number of the last occurance or -1 when the character has not been found at all</returns>
	int findlast(string str, char ch) {
		int i = str.size();
		do {
			i--;
		} while (i > 0 && str[i] != ch);
		return i;
	}

	int findlast(string haystack, string needle) {
		int i = haystack.size() - needle.size();
		if (i < 0) return -1;
		do {
			i--;
		} while (i > 0 && mid(haystack, i, needle.size()) != needle);
		return i;
	}

	int findfirst(string str, char ch) {
		for (int i = 0; i < str.size(); i++)
			if (str[i] == ch) return i;
		return -1;
	}

	string TReplace(string mystr, char ori, char subst) {
		for (unsigned int i = 0; i < mystr.size(); i++) {
			if (mystr[i] == ori) mystr[i] = subst;
		}
		return mystr;
	}

	std::string TReplace(std::string mystr, std::string ori, std::string subst) {
		/* bugged
		std::string ret ="";
		auto olen = mystr.size();
		auto slen = ori.size();
		unsigned p = 1;
		while (p + slen <= olen) {
			if (mid(mystr, p, slen) == ori) {
				ret += subst;
				p +=slen;
			} else {
				ret += mystr[p-1];
				p++;
			}
		}
		return ret;
		*/
		//* Fixed?
		std::string ret = "";
		auto olen = mystr.size();
		auto slen = ori.size();
		unsigned p = 1;
		while (p <= olen) {
			if ((p - 1) + slen <= olen && mid(mystr, p, slen) == ori) {
				//cout << p << "\t" << ori << "\t" << subst << "\t" << mystr << "\t" << ret << endl; // debug only
				ret += subst;
				p += slen;
				//cout << p << ":"<<olen<<endl;
			} else {
				ret += mystr[p - 1];
				p++;
			}
		}
		return ret;
		//*/
	}

	std::string TReplace(std::string mystr, char ori, string subst) {
		string ret;
		for (unsigned int i = 0; i < mystr.size(); i++) {
			if (mystr[i] == ori)
				ret += subst;
			else
				ret += mystr[i];
		}
		return ret;
	}



	std::string ExtractDir(std::string file) {
		file = TReplace(file, '\\', '/');
		int lastslash = findlast(file, '/');
		if (lastslash < -1) return "";
		return left(file, lastslash);
	}

	std::string StripDir(std::string file) {
		file = TReplace(file, '\\', '/');
		int lastslash = findlast(file, '/');
		if (lastslash < -1) return file;
		auto ret = right(file, file.size() - lastslash);
		while (ret.size() && ret[0] == '/') ret = right(ret, ret.size() - 1);
		return ret;
	}

	string StripExt(string file) {
		file = TReplace(file, '\\', '/');
		int lastdot = findlast(file, '.');
		int lastslash = findlast(file, '/');
		if (lastdot < 0 || lastdot < lastslash) return file;
		return left(file, lastdot);
	}

	std::string StripAll(std::string file) {
		return StripDir(StripExt(file));
	}

	vector<string> Split(string str, char spltchar) {
		vector<string> ret;
		unsigned int idx = 0;
		for (int i = 0; i < str.size(); i++) {
			if (idx >= ret.size()) ret.push_back("");
			if (str[i] == spltchar)
				idx++;
			else
				ret[idx] += str[i];
		}
		return ret;
	}

	vector<string> Split(string str, char spltchar, int max) {
		vector<string> ret;
		unsigned int idx = 0;
		for (int i = 0; i < str.size(); i++) {
			if (idx >= ret.size()) ret.push_back("");
			if (str[i] == spltchar && idx < max)
				idx++;
			else
				ret[idx] += str[i];
		}
		return ret;
	}


	vector<string> StringToLines(string str) {
		vector<string> ret;
		unsigned int idx = 0;
		for (int i = 0; i < str.size(); i++) {
			if (idx >= ret.size()) ret.push_back("");
			if (str[i] == '\n')
				idx++;
			else if (str[i] != '\r')
				ret[idx] += str[i];
		}
		return ret;
	}

	string Trim(string str) {
		string ret = "";
		bool begun = false;
		// before!
		for (int i = 0; i < str.size(); ++i) {
			begun = begun || (str[i] != ' ' && str[i] != '\t' && str[i] != '\r' && str[i] != '\n');
			if (begun)
				ret += str[i];
		}
		if (ret == "") return ""; // No need to go on if the string's empty now!
		/*
		for (int i = str.size() - 1; i >= 0; --i) {
			if (str[i] != ' ' && str[i] != '\t' && str[i] != '\r' && str[i] != '\n') return ret;
			ret[i] = '\0';
		}
		*/
		while (
			ret[ret.size() - 1] == ' ' ||
			ret[ret.size() - 1] == '\t' ||
			ret[ret.size() - 1] == '\n' ||
			ret[ret.size() - 1] == '\t'
			) {
			// cout << ret << " (" << ret.size() << ")\n";
			ret = left(ret, ret.size() - 1);
			if (ret == "") return "";
		}
		return ret; // Should never happen, but at least this prevents crashes, exceptions, whatever!
	}

	void Trans2Upper(string& str) {
		std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	}

	void Trans2Lower(string& str) {
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	}


	string Upper(string str) {
		string ret = str;
		Trans2Upper(ret);
		return ret;
	}

	std::string Lower(std::string str) {
		string ret = str;
		Trans2Lower(ret);
		return ret;
	}

	string bsdec(const char* str) {
		string ret = "";
		for (int i = 0; str[i]; i++) {
			auto c = str[i];
			if (c == ' ' || (c >= 'a' && c <= 'z') || (c >= '0' && c <= ':') || (c >= 'A' && c <= 'Z'))
				ret += c;
			else {
				char fme[10];
				sprintf_s(fme, 6, "\\%03d", c);
				ret += fme;
			}
		}
		return ret;
	}
	string bsdec(string str) { return bsdec(str.c_str()); }

	std::string hashmd5(std::string str) {
		/* original
			auto hash = ConstexprHashes::md5("jaklsdjlkad");
			cout << hex;
			for (auto i : hash) {
				cout << (static_cast<int>(i) & 0xff);
			}
			cout << endl;
		*/
		return "Not yet operational";
	}

	std::string Hex(int num) {
		char H[10];
		sprintf_s(H, "%08X", num);
		return std::string(H);
	}

	std::string StringJoin(std::string lnk, std::vector<std::string> strs) {
		string ret{ "" };
		for (auto s : strs) {
			if (ret.size()) ret += lnk;
			ret += s;
		}
		return ret;
	}

	long long FindString(std::string Needle, std::string HayStack) {
		auto NS = Needle.size();
		if (Needle.size() > HayStack.size()) return -1;
		if (Needle == HayStack) return 0;
		for (long long i = 0; i < HayStack.size() - Needle.size(); i++) {
			if (mid(HayStack, i, NS) == Needle) return i;
		}
		return -1;
	}


	string ExtractExt(std::string file) {
		file = TReplace(file, '\\', '/');
		int lastdot = findlast(file, '.');
		int lastslash = findlast(file, '/');
		if (lastdot < 0 || lastdot < lastslash) return "";
		return file.substr(lastdot + 1); //left(file, lastdot);
	}

	string Vec2Str(vector<char> input) {
		string s(input.begin(), input.end());
		return s;
	}


	static const char* scanformat(const char* strfrmt, char* form) {
		const char* L_FMTFLAGS{ "-+ #0" };
		const char* p = strfrmt;
		while (*p != '\0' && strchr(L_FMTFLAGS, *p) != NULL) p++;  /* skip flags */
		if ((size_t)(p - strfrmt) >= sizeof(L_FMTFLAGS) / sizeof(char)) {
			//000001193 | luaL_error(L, "invalid format (repeated flags)");
			std::cout << "Invalid format (repeated flags)\n";
			return NULL;
		}
		if (isdigit((unsigned char)(*p))) p++;  /* skip width */
		if (isdigit((unsigned char)(*p))) p++;  /* (2 digits at most) */
		if (*p == '.') {
			p++;
			if (isdigit((unsigned char)(*p))) p++;  /* skip precision */
			if (isdigit((unsigned char)(*p))) p++;  /* (2 digits at most) */
		}
		if (isdigit((unsigned char)(*p))) {
			//000001202 | luaL_error(L, "invalid format (width or precision too long)");
			cout << "invalid format (width or precision too long)";
			return NULL;
		}
		*(form++) = '%';
		memcpy(form, strfrmt, ((p - strfrmt) + 1) * sizeof(char));
		form += (p - strfrmt) + 1;
		*form = '\0';
		return p;
	}

	string TrSPrintF(const char* fmt, ...) {
		const char L_ESC{ '%' };
		const int MAX_FORMAT{ 32 };
		const int MAX_ITEM{ 120 };
		const int MAX_ITEMF{ 300 };
		va_list args;
		va_start(args, fmt);
		// Quick Alternate sprintf command (based on the Lua string.format() function)
		// int top = lua_gettop(L);
		string ret{ "" };
		//int arg = 1;
		size_t sfl{ strlen(fmt) };
		const char* strfrmt = fmt; // luaL_checklstring(L, arg, &sfl);
		const char* strfrmt_end = strfrmt + sfl;
		//luaL_Buffer b;
		//luaL_buffinit(L, &b);
		while (strfrmt < strfrmt_end) {
			if (*strfrmt != L_ESC)
				ret += (*strfrmt++); //luaL_addchar(&b, *strfrmt++);
			else if (*++strfrmt == L_ESC)
				ret += (*strfrmt++); //luaL_addchar(&b, *strfrmt++);  /* %% */
			else { /* format item */
				char form[MAX_FORMAT];  /* to store the format ('%...') */
				int maxitem = MAX_ITEM;
				char addret[MAX_ITEMF]{ "" };
				//char* buff = luaL_prepbuffsize(&b, maxitem);  /* to put formatted item */
				int nb = 0;  /* number of bytes in added item */
				//if (++arg > top)
				//	return luaL_argerror(L, arg, "no value");
				strfrmt = scanformat(strfrmt, form);
				if (!strfrmt) { va_end(args); return ""; }
				switch (*strfrmt++) {
				case 'c': {
					//nb = l_sprintf(buff, maxitem, form, (int)luaL_checkinteger(L, arg));
					//#define l_sprintf(s,sz,f,i)	((void)(sz), sprintf(s,f,i)) 
					//nb = ((void)(sz), sprintf_s(s, f, i));
					auto i{ va_arg(args, int) };
					sprintf_s(addret, form, i);
					break;
				}
				case 'd': case 'i':
				case 'o': case 'u': case 'x': case 'X': {
					//lua_Integer n = luaL_checkinteger(L, arg);
					//addlenmod(form, LUA_INTEGER_FRMLEN);
					//nb = l_sprintf(buff, maxitem, form, (LUAI_UACINT)n);
					auto i{ va_arg(args, int) };
					sprintf_s(addret, form, i);
					break;
				}
						/*
						case 'a': case 'A':
							addlenmod(form, LUA_NUMBER_FRMLEN);
							nb = lua_number2strx(L, buff, maxitem, form,
								luaL_checknumber(L, arg));
							break;
						//*/
				case 'f':
					maxitem = MAX_ITEMF;  /* extra space for '%f' */
					//buff = luaL_prepbuffsize(&b, maxitem);
					/* FALLTHROUGH */
				case 'e': case 'E': case 'g': case 'G': {
					//lua_Number n = luaL_checknumber(L, arg);
					//addlenmod(form, LUA_NUMBER_FRMLEN);
					//nb = l_sprintf(buff, maxitem, form, (LUAI_UACNUMBER)n);
					auto n{ va_arg(args,double) };
					sprintf_s(addret, form, n);
					break;
				}
						//case 'p': {
						//	const void* p = lua_topointer(L, arg);
						//	if (p == NULL) {  /* avoid calling 'printf' with argument NULL */
						//		p = "(null)";  /* result */
						//		form[strlen(form) - 1] = 's';  /* format it as a string */
						//	}
						//	nb = l_sprintf(buff, maxitem, form, p);
						//	break;
						//}
						//case 'q': {
						//	if (form[2] != '\0')  /* modifiers? */
						//		return luaL_error(L, "specifier '%%q' cannot have modifiers");
						//	addliteral(L, &b, arg);
						//	break;
						//}
				case 's': {
					const char* s{ va_arg(args,char*) }; //= luaL_tolstring(L, arg, &l);
					size_t l{ strlen(s) };					
					if (form[2] == '\0') { /* no modifiers? */
						//luaL_addvalue(&b);  /* keep entire string */
						std::string s2; s2 = string(s);
						strcpy_s(addret, s2.c_str());
						//strcpy_s(addret, s);
					}
					else {
						//luaL_argcheck(L, l == strlen(s), arg, "string contains zeros");
						if (l != strlen(s)) {
							cout << "string contains zeros\n"; va_end(args); return "";
						}
						if (!strchr(form, '.') && l >= 100) {
							/* no precision and string is too long to be formatted */
							strcpy_s(addret, s); //luaL_addvalue(&b);  /* keep entire string */
						} else {  /* format the string into 'buff' */
							//nb = l_sprintf(buff, maxitem, form, s);
							//lua_pop(L, 1);  /* remove result from 'luaL_tolstring' */
							sprintf_s(addret, form, s);
						}
					}
					break;
				}
				default: {  /* also treat cases 'pnLlh' */
					//return luaL_error(L, "invalid conversion '%s' to 'format'", form);
					printf("invalid conversion '%s' to 'format'", form);
					va_end(args);
					return "";
				}
				}
				//lua_assert(nb < maxitem);
				//luaL_addsize(&b, nb);
				ret += addret;
			}
		}
		//luaL_pushresult(&b);
		//return 1;
		return ret;
	}
}