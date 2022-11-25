// Lic:
// Source/ArgParse.cpp
// Argument Parser
// version: 22.10.26
// Copyright (C) 9, 2020, 2022 Jeroen P. Broks
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

// Standard libraries
#include <vector>
#include <string>
#include <map>

// Tricky's Units
#include "../Headers/QuickString.hpp"
#include "../Headers/TrickySTOI.hpp"
#include "../Headers/ArgParse.h"

using namespace std;

namespace TrickyUnits {

	static string _ParseArgReport = "";

	void AddFlag_Bool(FlagConfig &CFG, string name, bool defaultvalue ) {
		CFG.flagtype[name] = "BOOL";
		if (defaultvalue) CFG.defaultvalue[name] = "TRUE"; else CFG.defaultvalue[name] = "FALSE";
	}
	void AddFlag_String(FlagConfig& CFG, string name, string defaultvalue, bool req ) {
		CFG.flagtype[name] = "STRING";
		CFG.defaultvalue[name] = defaultvalue;
	}
	void AddFlag_Int(FlagConfig& CFG, string name, int defaultvalue, bool req ) {
		CFG.flagtype[name] = "INT";
		CFG.defaultvalue[name] = defaultvalue;
	}


	ParsedArg ParseArg(int l, char* args[], FlagConfig &CFG) {
		_ParseArgReport = "";
		ParsedArg ret;
		map<string, bool> reqflagset;
		string expectflag = "";
		for (int i = 0; i < l; i++) {
			string a = args[i];
			if (i == 0) {
				ret.myexe = args[i];
			}
			else if (expectflag != "") {
				// TODO: flag parse out complete
				//_ParseArgReport = "Flag parsing not yet supported";
				//ret.arguments.clear();
				//ret.bool_flags.clear();
				//ret.string_flags.clear();
				//ret.int_flags.clear();
				//return ret;
				if (CFG.flagtype[expectflag] == "STRING")
					ret.string_flags[expectflag] = args[i];
				else if (CFG.flagtype[expectflag]=="INT")
					ret.int_flags[expectflag] = ToInt(args[i]);
				else {
					_ParseArgReport = "Unknown flag: " + expectflag;
					return ret;
				}
				expectflag = "";
			}
			else if (prefixed(a, "-")) {
				string flag = right(a, a.size() - 1);
				if (CFG.flagtype[flag] == "BOOL") {
					ret.bool_flags[flag] = (CFG.defaultvalue[flag] == "FALSE");
				} else {
					// TODO: Proper flag parsing will be there later!
					//_ParseArgReport = "Flag parsing not yet supported";
					//ret.arguments.clear();
					//ret.bool_flags.clear();
					//ret.string_flags.clear();
					//ret.int_flags.clear();
					expectflag=flag;
					//return ret;
				}

			}
			else {
				ret.arguments.push_back(a);
			}
		}
		return ret;
	}

	/// <summary>
	/// Contains nothing at all when nothing went wrong. If something did go wrong, then this contains the error.
	/// </summary>
	/// <returns></returns>
	string ParseArgReport() { return _ParseArgReport; }


}