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
