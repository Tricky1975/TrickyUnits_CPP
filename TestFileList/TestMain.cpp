// Lic:
// TestFileList/TestMain.cpp
// Tricky's Units - File List
// version: 20.11.14
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
#include <iostream>
#include "../Headers/FileList.hpp"
#include "../Headers/Platform.hpp"
using namespace TrickyUnits;
using namespace std;

int main() {
	cout << "Testing on " << Platform() << endl;
	string tdir{ "E:/Projects/Applications/VisualStudio/TrickyUnits" };
	cout << "Analysing: " << tdir << endl;
	//auto test = FileList(tdir);
	auto test = GetTree(tdir);
	for (auto f : test) cout << "> " << f << endl;
}