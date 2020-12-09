#pragma once


namespace TrickyUnits {
	typedef void (*ByeSequence) ();
	typedef void (*DefiniteBye)(int exitcode);

	void AddBye(ByeSequence BS);
	void DefBye(DefiniteBye DB);
	void Bye(int exitcode=0);
}