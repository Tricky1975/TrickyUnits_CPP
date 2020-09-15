#include "..\Headers\RPGStat.hpp"
#include "QuickString.hpp"


#define PerformNULL(TheMap) \
		if (!TheMap.count(Tag)) return;\
		auto Old = TheMap[Tag];\
		TheMap.erase(Tag); \
		for (auto& chars : Map) if (chars.second.TheMap[Tag] == Old) return; \
		delete Old;

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
		for (auto& scan : DataMap) ret.push_back(scan.first);\
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
		if (&Map[SourceChar] == this) { Paniek("Cannot link with oneself!"); }
		if (!Map[SourceChar].HasStat(Stat)) { Paniek("Tried to link to non-existent stat (" + Stat + " from " + SourceChar + ")"); }
		NULLStat(Stat);
		MapStat[Stat] = Map[SourceChar].GetStat(Stat, false);
	}

	void Character::LinkData(string Data, string SourceChar) {
		if (&Map[SourceChar] == this) { Paniek("Cannot link with oneself!"); }
		if (!Map[SourceChar].HasData(Data)) { Paniek("Tried to link to non-existent Data (" + Data + " from " + SourceChar + ")"); }
		NULLData(Data);
		MapData[Data] = Map[SourceChar].GetData(Data, false);
	}

	void Character::LinkList(string List, string SourceChar) {
		if (&Map[SourceChar] == this) { Paniek("Cannot link with oneself!"); }
		if (!Map[SourceChar].HasList(List)) { Paniek("Tried to link to non-existent List (" + List + " from " + SourceChar + ")"); }
		NULLList(List);
		MapList[List] = Map[SourceChar].GetList(List, false);
	}

	void Character::LinkPoints(string Pnts, string SourceChar) {
		if (&Map[SourceChar] == this) { Paniek("Cannot link with oneself!"); }
		if (!Map[SourceChar].HasList(Pnts)) { Paniek("Tried to link to non-existent Points (" + Pnts + " from " + SourceChar + ")"); }
		NULLPoints(Pnts);
		MapPoints[Pnts] = Map[SourceChar].GetPoints(Pnts, false);
	}

	bool Character::HasStat(string Stat) { return MapStat.count(Stat); }
	bool Character::HasData(string Data) { return MapData.count(Data); }
	bool Character::HasList(string List) { return MapList.count(List); }
	bool Character::HasPoints(string Pnts) { return MapData.count(Pnts); }

	CharStat* Character::GetStat(string Stat, bool safe) { GetStuff(CharStat, MapStat, Stat); }
	CharData* Character::GetData(string Data, bool safe) { GetStuff(CharData, MapData, Data); }
	CharList* Character::GetList(string List, bool safe) { GetStuff(CharList, MapList, List); }
	CharPoints* Character::GetPoints(string Pnts, bool safe) { GetStuff(CharPoints, MapPoints, Pnts); }

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

	Character::~Character() {
		// I must make sure that the destruction of a character nullifies all memory!
		NULLEverything();
	}




	void CharPoints::MaxCopyUpdate(string chartag) {
		if (maxcopy == "") return;
		Character::Map[chartag].GetStat(maxcopy)->Value();
	}

	void CharPoints::Have(int v) { _have = max(min(v, _maximum), _minimum); }

	void CharPoints::Mini(int v) {
		if (v > _maximum) { Paniek("Setting minimum higher than maximum"); }
		_minimum = v;
	}

	void CharPoints::Maxi(int v, bool ignoremaxcopy) {
		if (v < _minimum && (!ignoremaxcopy)) { Paniek("Setting maximum lower than minimum"); }
		_maximum = v;
	}


	int CharPoints::Have() { return _have; }
	int CharPoints::Mini() { return _minimum; }
	int CharPoints::Maxi() { MaxCopyUpdate(maxcopy); return _maximum; }

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
					for (int j = 1; j < ss.size(); j++) _value += Character::Map[ss[0]].GetStat(ss[1])->Value();
				}
			} else {
				Paniek("Scripting stats NOT yet supported!") 0;
			}
		}
		return _value;
	}

	void CharStat::Value(int v) {
		if (_script != "") { Paniek("Value fixed by script, and cannot be changed!"); }
	}

	void CharStat::Script(string s) { _script = s; }
	void CharStat::ScriptFile(string s) { _scriptfile = s; }
	void CharStat::ScriptFunction(string s) { _scriptfunction = s; }
	string CharStat::Script() { return _script; }

	string CharStat::ScriptFile() { return _scriptfile; }

	string CharStat::ScriptFunction() { return _scriptfunction; }

	int Party::_max = 0;
	vector<string> Party::_party;
	
	void Party::Member(int memnum, string setmem) {
		if (memnum<1 || memnum>_max) { Paniek("Set Member Out Of Range"); }
		if (!Character::Map.count(setmem)) { Paniek("Member " + setmem + " doesn't exist and can therefore also not be put in the party!"); }
		_party[memnum - 1] = memnum;
	}

	string Party::Member(int memnum) {
		if (memnum<1 || memnum>_max) { Paniek("Get Member Out Of Range") ""; }
		return _party[memnum-1];
	}

	void Party::Max(int maxnum) {
		_party.resize(maxnum);
		_max = maxnum;
	}

	int Party::Max() {
		return _max;
	}

	void ResetRPG() {
		Party::Max(0);
		Character::Map.clear();
	}

	void doRPGPanic(string e) { Paniek(e); }

	void CharList::Add(string s) {
		List.push_back(s);
	}

}
