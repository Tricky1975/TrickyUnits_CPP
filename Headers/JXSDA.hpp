// Lic:
// Headers/JXSDA.hpp
// Jeroen's Xtremely Simplistic Dictionary Algorithm
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
#include <vector>

namespace TrickyUnits {

	enum class jxda_error { Ok, NotJXDA, TooSmall, DictionaryIndexError, UnpackSizeOverflow, UnpackSizeUnderflow };


	void jxsda_pack(char *source,int ssize,char *target,int &tsize);
	std::vector<char> jxsda_pack(char *source,int size);
	jxda_error jxsda_unpack(char *source,int ssize,char *target, int tsize);
	std::vector<char> jxsda_unpack(char *source, int ssize, int tsize);

}