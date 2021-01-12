// Lic:
// Headers/GameVars.hpp
// Game Vars (header)
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