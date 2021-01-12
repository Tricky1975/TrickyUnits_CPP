// Lic:
// Source/Bye.cpp
// Bye
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
#include "..\Headers\Bye.hpp"
#include <vector>

using std::vector;

namespace TrickyUnits {

	static vector<ByeSequence> BSVector;
	static DefiniteBye DBFunction{ nullptr };

	void AddBye(ByeSequence BS) { BSVector.push_back(BS); }
	void DefBye(DefiniteBye DB) { DBFunction = DB; }
	
	void Bye(int exitcode) {
		for (auto S : BSVector) S();
		if (DBFunction) DBFunction(exitcode);
		exit(exitcode);
	}
}