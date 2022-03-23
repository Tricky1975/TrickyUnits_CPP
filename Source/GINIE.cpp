// Lic:
// Source/GINIE.cpp
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
#include <GINIE.hpp>
#include <QuickString.hpp>
#include <QuickStream.hpp>

#undef GINIE_DEBUG


namespace TrickyUnits {

	// Class GENIE

	static void GCHAT(string msg) {
#ifdef GINIE_DEBUG
		cout << "DEBUG:> " << msg << "\n";
#endif
	}

	void GINIE::JamError(string Err) {
		if (ShowError) cout << "GENIE ERROR!\t" << Err << "\n";
		LastError = Err;
	}


	// Empty Constructor
	GINIE::GINIE() {}

	void GINIE::PerformAutoSave() {
		if (AutoSave == "") return;
		GCHAT("Auto-Saving GINIE: " + AutoSave);
		SaveString(AutoSave, UnParse());
	}

	void GINIE::Clear() {
		Data.clear();
	}

	string GINIE::GetError() {
		return LastError;
	}

	std::vector<std::string> GINIE::EachList(std::string sect) {
		vector<std::string> ret{};
		for (auto& it : Data[Upper(sect)].Lists) ret.push_back(it.first);
		return ret;
	}

	std::vector<std::string> GINIE::EachValue(std::string sect) {
		vector<std::string> ret{};
		for (auto& it : Data[Upper(sect)].Values) ret.push_back(it.first);
		return ret;
	}

	std::vector<std::string> GINIE::EachGroup() {
		vector<std::string> ret{};
		for (auto& it : Data) ret.push_back(it.first);
		return ret;
	}


	string EIL(string msg, int l) {
		return msg + " in line " + to_string(l + 1);
	}

	void GINIE::Parse(vector<string> source, bool merge) {
		LastError = "";
		if (!merge) this->Clear();
		string currenttag = "";
		string inlist = "";
		GCHAT("Parsing " + to_string(source.size()) + " line(s)");
		for (int ln = 0; ln < source.size(); ln++) {
			string line = Trim(source[ln]);
			GCHAT(source[ln] + " >> " + line);
			GCHAT("TAG [" + to_string(prefixed(line, "[")) + " ]" + to_string(suffixed(line, "]")));
			if (line == "" || prefixed(line, "#")) {
				// DO NOTHING!
			}
			else if (inlist != "") {
				if (Upper(line) == "*END")
					inlist = "";
				else
					//cout << "Added " << line << " to list [" << currenttag << "," << line << endl;
					Data[currenttag].Lists[inlist].push_back(line);
			}
			else if (prefixed(line, "[") && suffixed(line, "]")) {
				currenttag = Upper(mid(line, 2, line.size() - 2));
				GCHAT("Tag:" + currenttag);
			}
			else if (prefixed(Upper(line), "*LIST:")) {
				if (currenttag == "")
					JamError(EIL("List without group", ln));
				else
					inlist = Upper(line.substr(6));
			}
			else if (currenttag != "" && (inlist=="")) {
				int pos = findfirst(line, '=');
				if (pos < 0) { JamError(EIL("Missing = in definition", ln)); }
				else {
					string Variable = Upper(line.substr(0, pos));
					string Value = line.substr(pos + 1);
					Data[currenttag].Values[Variable] = Value;
				}
			}
			else {
				JamError(EIL("Instruction " + line + " not understood", ln));
			}
		}
	}

	void GINIE::Parse(string source, bool merge) {
		GCHAT("String received to parse");
		this->Parse(Split(source, '\n'), merge);
	}

	void GINIE::Value(string group, string varname, string value) {
		Data[Upper(group)].Values[Upper(varname)] = value;
		PerformAutoSave();
	}

	void GINIE::NewValue(string group, string varname, string value) {
		if (Data[Upper(group)].Values.count(Upper(varname))) return;
		Data[Upper(group)].Values[Upper(varname)] = value;
		PerformAutoSave();
	}

	string GINIE::Value(string group, string varname)
	{
		string g = Upper(group);
		string v = Upper(varname);
		if (Data.count(g) == 0) return "";
		if (Data[g].Values.count(v) == 0) return "";
		return Data[g].Values[v];
	}

	string GINIE::UnParse() {
		string ret = "# Automatically Generated by GINIE!\n\n";
		for (std::map<string, VGINIE>::iterator it = Data.begin(); it != Data.end(); ++it) {
			ret += "\n[" + it->first + "]\n";
			for (std::map<string, string>::iterator itv = Data[it->first].Values.begin(); itv != Data[it->first].Values.end(); ++itv) {
				ret += itv->first + "=" + itv->second + "\n";
			}
			for (std::map<string, vector<string>>::iterator itv = Data[it->first].Lists.begin(); itv != Data[it->first].Lists.end(); ++itv) {
				ret += "*LIST:"+itv->first + "\n";
				for (int i = 0; i < itv->second.size(); i++) {
					ret += "\t" + itv->second[i] + "\n";
				}
				ret += "*END\n";
			}
		}
		return ret;
	}

	void GINIE::CreateList(string group, string List) {
		auto g = Trim(Upper(group));
		auto l = Trim(Upper(List));
		if (Data.count(g) == 0 || Data[g].Lists.count(l) == 0)
			Data[g].Lists[l].clear();
		PerformAutoSave();
	}

	void GINIE::Add(string group, string list, string value) {
		auto g = Trim(Upper(group));
		auto l = Trim(Upper(list));
		auto v = Trim(value);
		Data[g].Lists[l].push_back(v);
		PerformAutoSave();
	}

	unsigned int GINIE::ListCount(string group, string list) {
		auto g = Trim(Upper(group));
		auto l = Trim(Upper(list));
		return Data[g].Lists[l].size();
	}

	vector<string> GINIE::List(string group, string list) {
		return Data[Trim(Upper(group))].Lists[Trim(Upper(list))];
	}

	void GINIE::FromFile(string file,bool allownonexistent,bool merge) {
		LastError = "";
		if (!FileExists(file)) {
			GCHAT("File not found! Starting empty!");
			if (!allownonexistent) JamError("File \"" + file + "\" does not exist!");
			return; // Return anyway! No file means nothing to do anyway.
		}
		GCHAT("Loading: " + file);
		auto src = LoadString(file);
		// cout << "LOADED:\n" << src << "END\n"; // debug!
		Parse(src,merge);
	}
	void GINIE::ToFile(string file)	{
		GCHAT("Saving GINIE: " + file);
		SaveString(file, UnParse());
	}

	typedef union {
		char c;                    // Char
		unsigned char b;           // Byte
		int i;                     // Integer
		unsigned int ui;           // Unsigned Integer
		long long l;               // Long
		unsigned long long ul;     // Unsinged Long;
		size_t s;
		char buf[20];
	} _bc;

	static void vecaddul(vector<char>* ret,unsigned long long v) {
		_bc d; d.s = v;
		for (auto i = 0; i < sizeof(unsigned long long); ++i) ret->push_back(d.buf[i]);
	}

	static void vecaddstr(vector<char>* ret, string v) {
		vecaddul(ret, v.size());
		for (auto i = 0; i < v.size(); ++i) ret->push_back(v[i]);
	}

	static unsigned long long vecul(vector<char>&buf,unsigned int* p){
		_bc d;
		for (auto i = 0; i < sizeof(unsigned long long); ++i) d.buf[i]=buf[*p++];
		return d.ul;
	}
	static string vecstr(vector<char>& buf, unsigned int* p) {
		auto s = vecul(buf, p);
		string ret{ "" };
		for (unsigned long long i = 0; i < s; ++i) s += buf[*p++];
		return ret;
	}

	std::vector<char> GINIE::ByteUnParse() {
		vector<char> ret{ 'G','E','N','I','E','\26' };
		for (std::map<string, VGINIE>::iterator it = Data.begin(); it != Data.end(); ++it) {
			ret.push_back(1);
			vecaddstr(&ret, it->first);
			for (std::map<string, string>::iterator itv = Data[it->first].Values.begin(); itv != Data[it->first].Values.end(); ++itv) {
				ret.push_back(2);
				vecaddstr(&ret, itv->first);
				vecaddstr(&ret, itv->second);
			}
			for (std::map<string, vector<string>>::iterator itv = Data[it->first].Lists.begin(); itv != Data[it->first].Lists.end(); ++itv) {
				ret.push_back(3);
				vecaddstr(&ret,itv->first);
				vecaddul(&ret, itv->second.size());
				for (int i = 0; i < itv->second.size(); i++) {
					vecaddstr(&ret, itv->second[i]);
				}
			}
		}
		ret.push_back(255);
		return std::vector<char>();
	}

	void GINIE::ByteParse(vector<char> b,bool merge) {
		const char* check = "GENIE\26";
		unsigned int p{ 0 };
		for (unsigned char i = 0; check[i]; ++i) if (check[i] != b[p++]) {
			cout << "ERROR! Byte code not recognized as GENIE byte code\n";
			return;
		}
		if (!merge) this->Clear();
		string TAG{ "" };
		while (p < b.size()) {
			auto wtag{ b[p++] };
			switch (wtag) {
			case 1:
				TAG = vecstr(b, &p);
				break;
			case 2:
				Value(vecstr(b, &p), vecstr(b, &p));
				break;
			case 3: {
				auto n = vecstr(b, &p);
				auto s = vecul(b, &p);
				for (unsigned long long i = 0; i < s; i++) Data[TAG].Lists[n].push_back(vecstr(b, &p));
			}
				  break;
			case 0:
			case 255:
				return;
			default:
				cout << "ERROR! Unknown tag in GENIE byte code " << wtag << "!\n";
				return;
			}
		}
		
	}
	
	void GINIE::ByteParse(char* src,bool merge) {		
		int n = sizeof(src) / sizeof(src[0]);
		std::vector<char> Buf(src, src + n);
		ByteParse(Buf,merge);
	}
}