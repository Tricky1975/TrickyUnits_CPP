#pragma once

namespace TrickyUnits {

	// Not needed as TRand does this automatically, but hey, better be safe than sorry! When seed is 0, the time will be used as seed.
	void TRandSeed(unsigned int seed=0); 
	int TRand(unsigned int Max);
	int TRand(int Min,int Max);

}
