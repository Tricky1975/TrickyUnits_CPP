#pragma once
#include <map>
#include <string>
#include <vector>

#define VarMap() ReffedVar()
#define VarKeys() Vars()

namespace TrickyUnits {
	bool VarReg(std::map<std::string, std::string> V);
	std::map<std::string, std::string>* ReffedVar();
	std::string VarCall(std::string K, bool Debug = false);
	std::string VarStr(std::string Str);
	void VarDef(std::string, std::string value);
	void VarClearAll();
	void VarClear(std::string K);
	size_t VarCount();
	std::string VarKey(size_t i);
	std::vector<std::string> Vars();
}