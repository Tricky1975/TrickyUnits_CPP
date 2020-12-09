// Lic:
// Source/QuickStream.cpp
// Quick Stream
// version: 20.11.15
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
#include <windows.h>
#include <direct.h>
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define QS4Windows
#define MDIR _mkdir
#elif
#define MDIR mkdir
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

#ifdef QS4Windows
	std::wstring s2ws(const std::string& s) {
		int len;
		int slength = (int)s.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		return r;
	}
#endif

	bool FileExists(char* file) {
		// Very extremely dirty, but it works!
		bool ret{ false };
#ifdef QS4Windows
		FILE* bt;
		auto res = fopen_s(&bt, file, "rb");
		ret = res == 0;
		if (res == 0 && bt!=NULL) fclose(bt);
#else
		FILE* bt = fopen(file, "rb");
		ret = (bt != NULL);
		if (bt != NULL) fclose(bt);
#endif
		return ret;
	}

	bool FileExists(string file) {
		// return FileExists(file.c_str());
		char af[502]; // A bit of a margin to cover up the null-terminator.
		if (file.size() > 500) {
			cout << "ERROR! FileExists(<<char[" << file.size() <<"]>>): File name too long! It's over 500!\n"; 
			return false;
		}
		// Microsoft! FUCK YOU FOR "DEPRECATING" (that is not the same as BLOCKING) C standard functions! Assholes!
		// MicroSCHOFT! Is a better name for you (although only the Dutch may understand what I mean).
#ifdef QS4Windows
		strcpy_s(af, file.c_str());
#else
		strcpy(af, file.c_str());
#endif
		return FileExists(af);
	}

#undef LoadString
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

	bool DirectoryExistsC(const char* folderName) {
#ifdef QS4Windows
		WIN32_FIND_DATA data;
		HANDLE hFile = FindFirstFile(s2ws(folderName).c_str(), &data);

		if (hFile == INVALID_HANDLE_VALUE) // directory doesn't exist
			return FALSE;
		else {
			// is it folder or file?
			FindClose(hFile);
			if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				return TRUE;
			return FALSE;
		}
#else
#pragma message("WARNING! The current DirectoryExists() function cannot work on this platform, will therefore always return false")
		return false;
#endif
	}

	bool DirectoryExists(string folderName) {
		return DirectoryExistsC(folderName.c_str());
	}

	bool MakeDir(string dir) {		
		return MakeDirC(dir.c_str());
	}

	bool MakeDirC(const char* dir) {
		if (DirectoryExistsC(dir)) return true;
		char tmp[256];
		char* p = NULL;
		size_t len;

		snprintf(tmp, sizeof(tmp), "%s", dir);
		len = strlen(tmp);
		if (tmp[len - 1] == '/')
			tmp[len - 1] = 0;
		for (p = tmp + 1; *p; p++)
			if (*p == '/') {
				*p = 0;
				//mkdir(tmp, S_IRWXU);
				//if (MDIR(tmp) != 0) return false;
				MDIR(tmp);
				*p = '/';
			}
		return MDIR(tmp) != 0;; //, S_IRWXU);		
	}

	std::ifstream::pos_type FileSize(std::string filename) {
		std::ifstream in(filename.c_str(), std::ifstream::ate | std::ifstream::binary);
		return in.tellg();
	}

	
	vector<string> LoadLines(string file){
		return StringToLines(LoadString (file));
	}

}