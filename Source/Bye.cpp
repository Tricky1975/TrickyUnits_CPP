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