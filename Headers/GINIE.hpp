// Lic:
// Headers/GINIE.hpp
// GINIE is not INI either
// version: 21.01.13
// Copyright (C) 2020, 2021 Jeroen P. Broks
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
#ifndef TRICKY_UNIT_GINIE_INCLUDED
#define TRICKY_UNIT_GINIE_INCLUDED

#include <vector>
#include <string>
#include <map>
#include <iostream>



namespace TrickyUnits {

	typedef struct {
		std::map<std::string, std::string> Values;
		std::map<std::string, std::vector<std::string>> Lists;
	} VGINIE;

	class GINIE {
	private:
		std::map <std::string, VGINIE> Data;
		std::string LastError="";
		void JamError(std::string Err);
		void PerformAutoSave();

	public:
		/// <summary>
		/// Set to false if you don't want errors to show! Set to true if you want.
		/// </summary>
		bool ShowError=true;

		/// <summary>
		/// When set, GINIE will save automatically every time a modification took place.
		/// </summary>
		std::string AutoSave = "";

		GINIE();
		void Clear();
		std::string GetError();
		void Parse(std::vector<std::string> source, bool merge = false);

		/// <summary>
		/// Parse a string into GINIE data
		/// </summary>
		/// <param name="source"></param>
		/// <param name="merge"></param>
		void Parse(std::string source, bool merge = false);
		// Creates a new value, but only if it didn't already exist. If it does exist this instruction will simply be ignored. Handy for setting default values.
		void NewValue(std::string group, std::string varname, std::string value);
		void Value(std::string group, std::string varname, std::string value);
		std::string Value(std::string group, std::string varname);
		std::string UnParse();
		void CreateList(std::string group, std::string List);
		void Add(std::string group, std::string list, std::string value);
		unsigned int ListCount(std::string group, std::string list);
		std::vector<std::string> List(std::string group, std::string list);
		std::vector<std::string> EachList(std::string sect);
		std::vector<std::string> EachValue(std::string sect);
		std::vector<std::string> EachGroup();
		void FromFile(std::string file, bool allownonexistent=false, bool merge=false);
		void ToFile(std::string file);
		std::vector<char> ByteUnParse();
		void ByteParse(std::vector<char>* b,bool merge=false);
		void ByteParse(std::vector<char> b, bool merge = false);
		void ByteParse(char* b,bool merge=false);
		void AutoParse(std::vector<char> b, bool merge = false);
		void AutoParse(char* b, bool merge = false);
	};

}
#endif // !TRICKY_UNIT_GINIE_INCLUDED