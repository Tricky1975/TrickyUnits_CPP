// Lic:
// Source/FileList.cpp
// Tricky's Units - File List
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
#include <algorithm>
#include <iostream>
#include "..\Headers\FileList.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define ForWindows
#include <Windows.h>

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

std::string convLPCWSTRtoString(LPCWSTR wString) {    
        auto size = wcslen(wString) + 1;    
        char* cString = new char[size];   
        for (unsigned long long i = 0; i < size; i++) {
            
                cString[i] = wString[i];
            
        }   
        std::string String{ cString };    
        delete[] cString;
        return String;    
}
//std::wstring stemp = s2ws(myString);
//LPCWSTR result = stemp.c_str();

#endif


std::vector<std::string> TrickyUnits::FileList(std::string Dir, DirWant Want, bool allowhidden, std::string addprefix) {
#ifdef ForWindows
    using namespace std;
    std::vector < std::string > ret;
    string search_path = Dir + "/*.*";
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(s2ws(search_path).c_str(), &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            // read all (real) files in current folder
            // , delete '!' read other 2 default folder . and ..
            auto found{ convLPCWSTRtoString(fd.cFileName) };
            auto allow{ false };
            //cout << found << " / " << fd.cFileName << endl;
            switch (Want) {
            case DirWant::Files:
                if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) { allow = true; }
                break;
            case DirWant::Directories:
                if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) { allow = true; }
                break;
            case DirWant::FilesAndDirectories:
                allow = true;
                break;
            case DirWant::Tree:                
                if ((!allowhidden) && found[0] == '.') { allow = false; } else if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                    auto add = FileList(Dir + "/" + found, DirWant::Tree, allowhidden, addprefix + found + "/");
                    for (auto a : add) ret.push_back(a);
                    allow = false;
                } else {
                    allow = true;
                }
            }
            if ((!allowhidden) && found[0] == '.') { allow = false; }
            if (allow) {
                ret.push_back(addprefix + found);
            }
        } while (::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
    std::sort(ret.begin(), ret.end());
    return ret;
#else
#pragma message("WARNING! FileList is not yet supported by this platform! An empty vector will be returned in stead!")
    return std::vector<std::string>();
#endif
}

std::vector<std::string> TrickyUnits::GetTree(std::string dir, bool allowhidden) {
    return FileList(dir, DirWant::Tree, allowhidden);
}