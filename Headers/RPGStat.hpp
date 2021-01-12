// Lic:
// Headers/RPGStat.hpp
// RPG Statistics Database (header)
// version: 21.01.13
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
#pragma once
#include <string>
#include <map>
#include <vector>
#include <iostream>


namespace TrickyUnits {

	using namespace std; // Safe! This only affects my namespace scope!

	typedef void (*RPGPanic)(string errormessage);

	class CharPoints;
	class CharData;
	class CharList;
	class CharStat;
	class Character;

	class CharPoints {
	private:
		int _have=0;
		int _maximum=0;
		int _minimum=0;
		string maxcopy;
	public:
		void MaxCopyUpdate(string chartag);
		void Have(int v);
		void ForceHave(int v);
		void Mini(int v);
		void Maxi(int v,bool ignoremaxcopy=false);
		void UnForce();
		int Have();
		int Mini();
		int Maxi();
		void MaxCopy(std::string mc);
		std::string MaxCopy();
	};

	class CharList {
	public:
		vector<string> List;
		void Add(string s);
		void Remove(string s);

	};

	class CharStat {
	private:
		int _value;
		string _script;
		string _scriptfile;
		string _scriptfunction;
	public:
		bool Pure = false;
		int Modifier = 0;
		int Value();
		void Value(int v);
		void Script(string s);
		void ScriptFile(string s);
		void ScriptFunction(string s);
		string Script();
		string ScriptFile();
		string ScriptFunction();
	};

	class CharData {
	public:
		string Value;
	};

	class Character {
	private:
		map<string, CharPoints*> MapPoints;
		map<string, CharData*> MapData;
		map<string, CharList*> MapList;
		map<string, CharStat*> MapStat;
		std::string CharTag;
	public:
		void NULLStat(string Tag);
		void NULLList(string Tag);
		void NULLData(string Tag);
		void NULLPoints(string Tag);

		void NULLAllStat();
		void NULLAllList();
		void NULLAllData();
		void NULLAllPoints();

		void NULLEverything();

		void LinkStat(string Stat, string SourceChar);
		void LinkData(string Data, string SourceChar);
		void LinkList(string List, string SourceChar);
		void LinkPoints(string Pnts, string SourceChar);

		bool HasStat(string Stat);
		bool HasData(string Data);
		bool HasList(string List);
		bool HasPoints(string Pnts);

		CharStat* GetStat(string Stat, bool safe = true);
		CharData* GetData(string Data, bool safe = true);
		CharList* GetList(string Stat, bool safe = true);
		CharPoints* GetPoints(string Data, bool safe = true);

		void SetData(std::string Data,std::string value);

		vector<string> Stats();
		vector<string> Datas(); // I know this is odd English, but it will have to do! :-P
		vector<string> Lists();
		vector<string> Points();

		std::string StatList();

		string Name;
		static map <string, Character> Map;
		static RPGPanic Panic;
		static void CreateChar(std::string Tag);
		static int CountChars();

		Character();
		Character(std::string Tag);
		~Character();
	};

	class Party {
	private:
		static vector<string> _party;
		static int _max;
	public:
		static void Member(int memnum, string setmem, bool dontcheckexistance=false);
		static string Member(int memnum);
		static void Max(int maxnum);
		static int Max();
		static void Remove(std::string Tag);
		static void Remove(int memnum);

	};

	void ResetRPG();
	void doRPGPanic(string e);
}