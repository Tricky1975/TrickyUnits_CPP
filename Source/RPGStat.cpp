// Lic:
// Source/RPGStat.cpp
// RPGStat
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
#include "..\Headers\RPGStat.hpp"
#include "QuickString.hpp"

//#define Chat(a) cout << "\x1b[32mRPG-DEBUG> \x1b[0m"<<a<<endl
#define Chat(a)

#define PerformNULL(TheMap) \
		if (!TheMap.count(Tag)) return;\
		auto Old = TheMap[Tag];\
		TheMap.erase(Tag); \
		for (auto& chars : Map) if (chars.second.TheMap[Tag] == Old) return; \
		if (Old) delete Old;

#define PerformAllNULL(TheMap) \
		vector<string> Victims; \
		for (auto getvictim : TheMap) Victims.push_back(getvictim.first); \
		for (auto Tag : Victims) { PerformNULL(TheMap); }

#define Paniek(error) if (!Character::Panic) Character::Panic=DefaultPanic; Character::Panic(error); return

#define GetStuff(Class,Stuff,Tag)\
	if (!Stuff.count(Tag)) { if (safe) Stuff[Tag] = new Class(); else {Paniek("Call to non-existent stuff "+Tag) NULL; }} \
	return Stuff[Tag];

#define RPGDataGather(DataMap)\
		vector<string> ret;\
		for (auto& scan : DataMap) if (scan.second) ret.push_back(scan.first);\
		return ret;


namespace TrickyUnits {

	using namespace std;

	RPGPanic Character::Panic = NULL;
	map <string, Character> Character::Map;

	static void DefaultPanic(string errormessage) {
		cout << "\x7\x1b[31mERROR!!!\x1b[0m" << errormessage << "\n";
	}

	void Character::NULLStat(string Tag) {
		/* Model for Macro
		if (!MapStat.count(Tag)) return;
		auto Old = MapStat[Tag];
		MapStat.erase(Tag);
		// Clean Memory if applicable
		for (auto& chars : Map) if (chars.second.MapStat[Tag] == Old) return;
		delete Old;
		*/
		PerformNULL(MapStat);
	}
	void Character::NULLList(string Tag) {
		PerformNULL(MapList);
	}

	void Character::NULLData(string Tag) {
		PerformNULL(MapData);
	}
	void Character::NULLPoints(string Tag) {
		PerformNULL(MapPoints);
	}
	void Character::NULLAllStat() {
		PerformAllNULL(MapStat);
	}

	void Character::NULLAllList() {
		PerformAllNULL(MapList);
	}

	void Character::NULLAllData() {
		PerformAllNULL(MapData);
	}

	void Character::NULLAllPoints() {
		PerformAllNULL(MapPoints);
	}

	void Character::NULLEverything() {
		{PerformAllNULL(MapStat); }
		{PerformAllNULL(MapList); }
		{PerformAllNULL(MapData); }
		{PerformAllNULL(MapPoints); }
	}

	void Character::LinkStat(string Stat, string SourceChar) {
		if (!Map.count(SourceChar)) { Paniek("Tried to link with non-existent character"); }
		if (&Map[SourceChar] == this) { Paniek("Cannot link with oneself!"); }
		if (Stat == "*") {
			for (auto& k : Map[SourceChar]. Stats()) LinkStat(k, SourceChar);
			return;
		}
		if (!Map[SourceChar].HasStat(Stat)) { Paniek("Tried to link to non-existent stat (" + Stat + " from " + SourceChar + ")"); }
		NULLStat(Stat);
		MapStat[Stat] = Map[SourceChar].Map[SourceChar].GetStat(Stat, false);
	}

	void Character::LinkData(string Data, string SourceChar) {
		if (!Map.count(SourceChar)) { Paniek("Tried to link with non-existent character"); }
		if (&Map[SourceChar] == this) { Paniek("Cannot link with oneself!"); }
		if (Data == "*") {
			for (auto& k : Map[SourceChar].Datas()) LinkData(k, SourceChar);
			return;
		}
		if (!Map[SourceChar].HasData(Data)) { Paniek("Tried to link to non-existent Data (" + Data + " from " + SourceChar + ")"); }
		NULLData(Data);
		MapData[Data] = Map[SourceChar].Map[SourceChar].GetData(Data, false);
	}

	void Character::LinkList(string List, string SourceChar) {
		if (!Map.count(SourceChar)) { Paniek("Tried to link with non-existent character"); }
		if (&Map[SourceChar] == this) { Paniek("Cannot link with oneself!"); }
		if (List == "*") {
			for (auto& k : Map[SourceChar].Lists()) LinkList(k, SourceChar);
			return;
		}
		if (!Map[SourceChar].HasList(List)) { Paniek("Tried to link to non-existent List (" + List + " from " + SourceChar + ")"); }
		NULLList(List);
		MapList[List] = Map[SourceChar].GetList(List, false);
	}

	void Character::LinkPoints(string Pnts, string SourceChar) {
		if (!Map.count(SourceChar)) { Paniek("Tried to link with non-existent character"); }
		if (&Map[SourceChar] == this) { Paniek("Cannot link with oneself!"); }
		if (Pnts == "*") {
			for (auto& k : Map[SourceChar].Points()) LinkPoints(k, SourceChar);
			return;
		}
		if (!Map[SourceChar].HasPoints(Pnts)) { Paniek("Tried to link to non-existent Points (" + Pnts + " from " + SourceChar + ")"); }
		NULLPoints(Pnts);
		MapPoints[Pnts] = Map[SourceChar].GetPoints(Pnts, false);
	}

	bool Character::HasStat(string Stat) { return MapStat.count(Stat); }
	bool Character::HasData(string Data) { return MapData.count(Data); }
	bool Character::HasList(string List) { return MapList.count(List); }
	bool Character::HasPoints(string Pnts) { return MapPoints.count(Pnts) && MapPoints[Pnts]; }

	CharStat* Character::GetStat(string Stat, bool safe) { GetStuff(CharStat, MapStat, Stat); }
	CharData* Character::GetData(string Data, bool safe) { 
		//GetStuff(CharData, MapData, Data); 
		if (!MapData.count(Data)) {
			if (safe) {
				MapData[Data] = new CharData();
				cout << "Creating Character Data: " << Data << "!\n";
			} else { Paniek("Call to non-existent MapData " + Data) NULL; }
		}
		if (!MapData[Data]) cout << "WARNING! MapData on key [" << Data << "] appears to be NULL! This may never be possible!\n";
		return MapData[Data];
	}
	CharList* Character::GetList(string List, bool safe) { GetStuff(CharList, MapList, List); }
	CharPoints* Character::GetPoints(string Pnts, bool safe) {
		//GetStuff(CharPoints, MapPoints, Pnts); 
		if (!MapPoints.count(Pnts)) { if (safe) MapPoints[Pnts] = new CharPoints(); else { Paniek("Call to non-existent MapPoints " + Pnts) NULL; } } 
		auto mp = MapPoints[Pnts];
		if (!mp) { 
			for (auto& whatthefuck : MapPoints) cout << "WTF! " << whatthefuck.first << ":" << (int)whatthefuck.second << "\n"; // debug
			doRPGPanic("Internal error! NULL recevied for Character points " + CharTag + "." + Pnts); return nullptr; 
		}
		mp->MaxCopyUpdate(CharTag);
		return MapPoints[Pnts];

	}

	void Character::SetData(string Data,string value) {
		if (!MapData.count(Data)) MapData[Data] = new CharData();
		MapData[Data]->Value = value;
	}

	vector<string> Character::Stats() {
		RPGDataGather(MapStat);
	}

	vector<string> Character::Datas() {
		RPGDataGather(MapData);
	}

	vector<string> Character::Lists() {
		RPGDataGather(MapList);
	}

	vector<string> Character::Points() {
		RPGDataGather(MapPoints);
	}

	string Character::StatList() {
		string ret = "";
		for (auto s : MapStat) {
			if (ret != "") ret += "\n";
			ret += s.first + " = " + to_string(s.second->Value());
		}
		return ret;
	}

	static void ReportImpurities(vector<string> *k,string n){
		for(auto i:*k)
			cout << "IMPURITY " << n << " " << i << endl;
	}
	void Character::ScanImpurities(bool clean) {
		vector<string> Kill;
		// Points
		for (auto k : MapPoints) if (!k.second) Kill.push_back(k.first);
		ReportImpurities(&Kill, "Points");
		if (clean) for (auto Slachtoffer : Kill) MapPoints.erase(Slachtoffer);
		Kill.clear();
		// Stats
		for (auto k : MapStat) if (!k.second) Kill.push_back(k.first);
		ReportImpurities(&Kill, "Stat");
		if (clean) for (auto Slachtoffer : Kill) MapStat.erase(Slachtoffer);
		Kill.clear();
		// Data
		for (auto k : MapData) if (!k.second) Kill.push_back(k.first);
		ReportImpurities(&Kill, "Data");
		if (clean) for (auto Slachtoffer : Kill) MapData.erase(Slachtoffer);
		Kill.clear();
		// Lists
		for (auto k : MapList) if (!k.second) Kill.push_back(k.first);
		ReportImpurities(&Kill, "List");
		if (clean) for (auto Slachtoffer : Kill) MapList.erase(Slachtoffer);
		Kill.clear();

	}

	void Character::CreateChar(std::string Tag) {
		Map[Tag] = Character(Tag);
		cout << "Character '" << Tag << "' created!\n"; // debug
	}

	int Character::CountChars() {
		return Map.size();
	}

	Character::Character() {
		cout << "\x7WARNING! Character created without any tag!\n";
	}

	Character::Character(std::string Tag) { CharTag = Tag; }
	Character::~Character() {
		// I must make sure that the destruction of a character nullifies all memory!
		//cout << "Character destruction! '"<<CharTag<<"' N:'"<<Name<<"'\n";
		//NULLEverything();
	}




	void CharPoints::MaxCopyUpdate(string chartag) {
		// cout << maxcopy << " << MAXCOPY!\n";
		if (maxcopy == "") return;
		_maximum = Character::Map[chartag].GetStat(maxcopy)->Value();
		UnForce();
		// cout << "MAXCOPY:" << chartag << "." << maxcopy << " >> " << _maximum << "\n";
	}

	void CharPoints::Have(int v) { 
		//_have = max(min(v, _maximum), _minimum); 
		_have = v;
		UnForce();
	}

	void CharPoints::ForceHave(int v) {
		_have = v;
	}

	void CharPoints::Mini(int v) {
		if (v > _maximum) { Paniek("Setting minimum higher than maximum"); }
		_minimum = v;
	}

	void CharPoints::Maxi(int v, bool ignoremaxcopy) {
		if (v < _minimum && (!ignoremaxcopy)) { Paniek("Setting maximum lower than minimum"); }
		_maximum = v;
	}

	void CharPoints::UnForce() {
		// _have = max(min(_have, _maximum), _minimum);  // ? Ignored?
		//Paniek("UNFORCE!!!");; // Force an error to guarantee me this function is called at all!
		if (_minimum > _maximum) { Paniek("Points Unforce error! Maximum lower than minumum"); }
		if (_have > _maximum) { Chat("Have:" << _have << " greater than max:" << _maximum << "\tCorrecting!"); _have = _maximum; }
		if (_have < _minimum) { Chat("Have:" << _have << " lower   than min:" << _minimum << "\tCorrecting!"); _have = _minimum; }
	
	}


	int CharPoints::Have() { return _have; }
	int CharPoints::Mini() { return _minimum; }
	int CharPoints::Maxi() { return _maximum; }

	void CharPoints::MaxCopy(string mc) {
		maxcopy = mc;
	}

	string CharPoints::MaxCopy() {
		return maxcopy;
	}

	int CharStat::Value() {
		if (_script != "") {
			if (prefixed(_script, "SUM:")) {
				auto sp = Split(_script, ':');
				_value = 0;
				for (int i = 1; i < sp.size(); i++) {
					auto ss = Split(sp[i], '.');
					if (ss.size() < 2) { Paniek("Script error") 0; }
					for (int j = 1; j < ss.size(); j++) _value += Character::Map[ss[0]].GetStat(ss[j])->Value();
				}
			} else {
				Paniek("Scripting stats NOT yet supported!") 0;
			}
		}
		return _value;
	}

	void CharStat::Value(int v) {
		if (_script != "") { Paniek("Value fixed by script, and cannot be changed!\n"+_script); }
		_value = v;
	}

	void CharStat::Script(string s) { _script = s; }
	void CharStat::ScriptFile(string s) { _scriptfile = s; }
	void CharStat::ScriptFunction(string s) { _scriptfunction = s; }
	string CharStat::Script() { return _script; }

	string CharStat::ScriptFile() { return _scriptfile; }

	string CharStat::ScriptFunction() { return _scriptfunction; }

	int Party::_max = 0;
	vector<string> Party::_party;
	
	void Party::Member(int memnum, string setmem,bool dontcheckexistance) {
		if (memnum<1 || memnum>_max) { Paniek("Set Member Out Of Range ("+to_string(memnum)+":"+to_string(_max)+")"); }	
		if (setmem!="")
			if (!(Character::Map.count(setmem) || dontcheckexistance)) { Paniek("Member " + setmem + " doesn't exist and can therefore also not be put in the party!"); }
		_party[memnum - 1] = setmem;
	}

	string Party::Member(int memnum) {
		if (memnum<1 || memnum>_max) { Paniek("Get Member Out Of Range (" + to_string(memnum) + ":" + to_string(_max) + ")") ""; }
		return _party[memnum - 1];
	}

	void Party::Max(int maxnum) {
		_party.resize(maxnum);
		_max = maxnum;
	}

	int Party::Max() {
		return _max;
	}

	void Party::Remove(std::string Tag) {
		for (int i = 1; i <= _max; i++) {
			if (Tag == _party[i]) {
				Remove(i);
				return;
			}
		}
	}

	void Party::Remove(int memnum) {
		if (memnum<1 || memnum>_max) { Paniek("Remove Member Out Of Range"); }
		for (int i = memnum; i <= _max; i++) {
			_party[i] = _party[i + 1];
		}
		_party[memnum] = "";
	}

	void ResetRPG() {
		Party::Max(0);
		Character::Map.clear();
	}

	void doRPGPanic(string e) { Paniek(e); }

	void CharList::Add(string s) {
		List.push_back(s);
	}

	void CharList::Remove(string s) {
		for (size_t i = 0; i < List.size(); i++) {
			if (List[i] == s) {
				List.erase(List.begin() + i);
				return;
			}
		}
	}

}