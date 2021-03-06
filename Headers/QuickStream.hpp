// Lic:
// Headers/QuickStream.hpp
// Quick Stream (header)
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
#ifndef INCLUDED_TRICKY_UNIT_QUICKSTREAM
#define INCLUDED_TRICKY_UNIT_QUICKSTREAM
#include <string>
#include <fstream>




namespace TrickyUnits {
	using namespace std;
	bool FileExists(char* file);
	bool FileExists(string file);
	string LoadString(string file);
	void SaveString(string file, string stringvalue);

	bool DirectoryExistsC(const char* folderName);
	bool DirectoryExists(string folderName);

	bool MakeDir(string dir);
	bool MakeDirC(const char* dir);

	std::ifstream::pos_type FileSize(std::string filename);
}
#endif