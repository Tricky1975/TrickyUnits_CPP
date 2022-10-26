// Lic:
// Source/Hex.cpp
// HHex
// version: 22.10.26
// Copyright (C) 2022 Jeroen P. Broks
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
#include <QuickTypes.hpp>

#include <string>
#include <QuickTypes.hpp>

#define MH(type,sz)\
	std::string HHex(type c) {\
		char ret[100];\
		sprintf_s(ret,sz,c);\
		return ret;\
	}

namespace TrickyUnits {

	MH(char, "%02x");
	MH(byte, "%02x");

	MH(int16, "%04x");
	MH(uint16, "%04x");

	MH(int32, "%08x");
	MH(uint32, "%08x");

	MH(int64, "%016x");
	MH(uint64, "%016x");

}