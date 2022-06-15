#include <iostream>
#include "../Headers/Platform.hpp"
#include "../Headers/QCol.hpp"

#ifdef Tricky_Windows
#include <Windows.h>
#endif

using namespace std;


namespace TrickyUnits{

	bool qColErrorShow{ true };
	static void err(string er) {
		if (qColErrorShow) cout << "QCOL ERROR> " << er << endl;
	}
	
#pragma region Windows Console
	static void Win_Color(qColor f, qColor b) {
		if ((int)f < 0 || (int)f>15) { err("Foreground out of bounds!"); return; }
		if ((int)b < 0 || (int)b>15) { err("Background out of bounds!"); return; }
		auto
			fg{ (byte)f },
			bg{ (byte)b };
#ifndef Tricky_Windows
		qColErrorShow("This driver only works in Windows!");
		return
#else
		auto hConsole{ GetStdHandle(STD_OUTPUT_HANDLE) };
		SetConsoleTextAttribute(hConsole, fg+(bg*16));
#endif

	}

	void Win_Reset() { WinQCol.Color(qColor::Grey, qColor::Black); }
#pragma endregion


#pragma region ANSI
	byte W2A(qColor c) {
		switch (c) {
		case qColor::Black: return 0;
		case qColor::DarkGrey: return 60;
		case qColor::Red: return 1;
		case qColor::Pink: return 61;
		case qColor::Green: return 2;
		case qColor::LightGreen: return 62;
		case qColor::Brown: return 3;
		case qColor::Yellow: return 63;
		case qColor::Blue: return 4;
		case qColor::LightBlue: return 64;
		case qColor::Magenta: return 5;
		case qColor::LightMagenta: return 65;
		case qColor::Cyan: return 6;
		case qColor::LightCyan: return 66;
		case qColor::Grey: return 7;
		case qColor::White: return 67;
		default:
			err("Unknown color! I cannot convert this to ASNI! (" + to_string((byte)c) + ")");
			return 0;
		}
	}

	static void ANSI_Color(qColor f, qColor b) {
		if ((int)f < 0 || (int)f>15) { err("Foreground out of bounds!"); return; }
		if ((int)b < 0 || (int)b>15) { err("Background out of bounds!"); return; }
		auto
			fg{ W2A(f) },
			bg{ W2A(b) };
		printf("\x1b[%dm\x1b[%dm", 30 + fg, 40 + bg);
	}

	static void ANSI_Reset() { printf("\x1b[0m"); }
#pragma endregion

	TmpPlateQCol
		WinQCol{ Win_Color,Win_Reset,"Windows Console"},
		ANSI{ ANSI_Color,ANSI_Reset, "ANSI"},
#ifdef Tricky_Windows
		*QCol{ &WinQCol };
#else
		*QCol{ &ANSI };
#endif



	void TmpPlateQCol::Write(qColor c, std::string w) {
		Color(c, qColor::Black);
		printf(w.c_str());
	}

	void TmpPlateQCol::Doing(string a, string b, string cl) {
		Write(Doing1, a+":");
		for (auto i = a.size(); i < DoingTab; ++i) printf(" ");
		Write(Doing2, b + cl);
	}
	void TmpPlateQCol::Doing(string a, int b, string cl) { Doing(a, to_string(b), cl); }

	void TmpPlateQCol::Error(string msg) {
		Write(Error1, "ERROR> ");
		Write(Error2, msg);
		cout << endl;
	}

	void TmpPlateQCol::Green(string a) { Write(qColor::Green, a); }
	void TmpPlateQCol::LGreen(string a) { Write(qColor::LightGreen, a); }
	void TmpPlateQCol::Red(string a) { Write(qColor::Red, a); }
	void TmpPlateQCol::Pink(string a) { Write(qColor::Pink, a); }
	void TmpPlateQCol::Dark(string a) { Write(qColor::DarkGrey, a); }
	void TmpPlateQCol::Yellow(string a) { Write(qColor::Yellow, a); }

	TmpPlateQCol::TmpPlateQCol(QColColor c, QColReset r,string n) {
		Color = c;
		Reset = r;
		Name = n;
	}
}