// Lic:
// Source/TRandom.cpp
// Tricky's Random
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
#undef RDEBUG
#include <stdlib.h> 
#include <time.h> 
#include "../Headers/TRandom.hpp"
#ifdef RDEBUG
#include <iostream>
using namespace std;
#endif

namespace TrickyUnits {

	void TRandSeed(unsigned int seed) {
		srand(seed || time(NULL));
	}

	int TRand(unsigned int Max) {
		static bool InitDone{ false };
		if (!InitDone) {
#ifdef RDEBUG
			cout << "Auto-Seeding\n";
#endif 
			TRandSeed();
		InitDone = true;
		}
		return rand() % (Max + 1);
	}

	int TRand(int Min, int Max) {
		auto r = Max - Min;
#ifdef RDEBUG
		cout << "TRand(" << Min << "," << Max << ")   ==> Range=" << r << endl;
#endif 

		if (r <= 0) return 0; // This cannot be done, folks!
		return TRand(r) + Min;
	}
}