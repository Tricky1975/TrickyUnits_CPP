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