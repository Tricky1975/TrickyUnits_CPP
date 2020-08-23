// Lic:
// Source/QuickStream.cpp
// Quick Stream
// version: 20.08.23
// Copyright (C) 2020 Jeroen P. Broks
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

// I hope I can make this code as portable as possible, so I am not interested in using Microsoft's own solutions that are non-standard!
#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

// Base C/C++ stuff
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

// Tricky's Units
#include "../Headers/QuickString.hpp"
#include "../Headers/QuickStream.hpp"


namespace TrickyUnits {
	using namespace std;

	bool FileExists(char* file) {
		// Very extremely dirty, but it works!
		bool ret;
		FILE* bt = fopen(file, "rb");
		ret = (bt != NULL);
		if (bt != NULL) fclose(bt);
		return ret;
	}

	bool FileExists(string file) {
		// return FileExists(file.c_str());
		char af[502]; // A bit of a margin to cover up the null-terminator.
		if (file.size() > 500) {
			cout << "ERROR! FileExists(<<char[" << file.size() <<"]>>): File name too long! It's over 500!\n"; 
			return false;
		}
		strcpy(af, file.c_str());
		return FileExists(af);
	}

	string LoadString(string file) {
		std::ifstream ifs(file);
		std::string content((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));
		// cout << "LOADED FROM FILE: " << file << "\n" << content << "\END\n";
		return content;
	}

	void SaveString(string file, string stringvalue) {
		std::ofstream out(file);
		out << stringvalue;
		out.close();
}

	vector<string> LoadLines(string file){
		return StringToLines(LoadString (file));
	}

}