// Lic:
// Source/QuickStream.cpp
// Quick Stream
// version: 22.10.26
// Copyright (C) 2020, 2021, 2022 Jeroen P. Broks
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
#include "../Headers/QuickTypes.hpp"
#include "../Headers/TrickyTime.hpp"


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

	void LoadChars(vector<char>*vec,string file) {
		//std::vector<char> vec;
		vec->clear();
#ifdef QS4Windows
		// Slow, unworthy, but otherwise Microsoft blocks this out.
		// Microsoft HATES efficient code, so it seems.
		char buff;
		std::ifstream bt;
		bt.open(file);
		while (!bt.eof()) {
			bt.read(&buff, 1);
			vec->push_back(buff);
		}
		bt.close();		
#else
		if (FILE* fp = fopen("filename", "r")) {
			char buf[1024];
			while (size_t len = fread(buf, 1, sizeof(buf), fp)) {
				vec->insert(vec->end(), buf, buf + len);
			}
			fclose(fp);
		}
#endif
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

	bool FileDelete(std::string file, bool noerrormsg) {
		auto er = remove(file.c_str());
		if (er == 0) return true;
		if (!noerrormsg) {
			char err[300];
			sprintf_s(err, "Deleting file failed (code: %04d)", er);
			perror(err);
		}
		return false;
	}

	std::string CurrentDir() {
		char* cwd = _getcwd(0, 0); // **** microsoft specific ****
		std::string working_directory{ TReplace(cwd,'\\','/') };
		std::free(cwd);
		return working_directory;

	}

	void ChangeDir(std::string dir) {
#ifdef _WIN32
		_chdir(dir.c_str());
#else
		chdir(dir.c_str());
#endif
	}

	std::ifstream::pos_type FileSize(std::string filename) {
		std::ifstream in(filename.c_str(), std::ifstream::ate | std::ifstream::binary);
		return in.tellg();
	}

	std::string FileDate(std::string FileName) {
		struct stat st;  // declaration of the stat
		struct tm tm; //declaration of tm pointer

		char filename1[500]; strcpy_s(filename1, FileName.c_str());
		char datestring[256];
		stat(filename1, &st);
		tm = _localtime(&st.st_mtime);
		strftime(datestring, sizeof(datestring), "%m-%d-%Y %H.%M.%S", &tm);
		std::string ret{ datestring };
		return TReplace(ret,'.',':');
	}

	OutFile WriteFile(string fname, int endian) {
		return make_shared<True_OutFile>(fname,endian);
	}

	InFile ReadFile(std::string fname, int endian) {
		return make_shared<True_InFile>(fname, endian);
	}

	
	vector<string> LoadLines(string file){
		return StringToLines(LoadString (file));
	}

	union _ce {
		char ac[20];
		char c;
		unsigned char uc;
		int i;
		int16 i16;
		uint16 ui16;
		unsigned int ui;
		long long l;
		unsigned long long ul;
	};

	bool True_OutFile::endmatch() {		return (!endian) || (endian==sysendian); }


	True_OutFile::True_OutFile(std::string _filename, int _endian) {
		stream = std::ofstream(_filename.c_str(),std::ios::binary);
		FileName = _filename;
		// What endian type does the CPU have?
		_ce ce; ce.i = 256;
		if (ce.ac[1]) sysendian = 1; else sysendian = 2;
	}

	True_OutFile::~True_OutFile() { if (AutoClose) Close(); }

	void True_OutFile::Write(char c) { stream << c; Written++; }

	void True_OutFile::Write(unsigned char c) {
		_ce ce; ce.uc = c;
		Write(ce.c);
	}

	void True_OutFile::Write(string s, bool raw) {
		if (!raw) Write((unsigned int)s.size());
		for (int i = 0; i < s.size(); ++i) Write(s[i]);
	}

	void True_OutFile::Write(vector<char> buf, bool storelength) {
		if (storelength) Write((unsigned int)buf.size());
		for (int i = 0; i < buf.size(); ++i) Write(buf[i]);
	}

	void True_OutFile::WriteCString(const char* str) {
		unsigned int i = 0;
		do {
			Write(str[i]);
		} while (str[i++]);
	}

	unsigned long long True_OutFile::Size() {
		return Written;
	}

	void True_OutFile::Close() {		
		if (!closed) stream.close();
	}

#define TOFW(mytype,cem) \
	void True_OutFile::Write(mytype myvar) {\
		_ce ce; ce.cem = myvar;\
		if (endmatch()) \
				for (int i = 0; i < sizeof(mytype); ++i) Write(ce.ac[i]);\
		else\
			for (int i = sizeof(mytype)-1; i>=0; --i) Write(ce.ac[i]);\
	}

	TOFW(int, i);
	TOFW(unsigned int, ui);
	TOFW(long long, l);
	TOFW(unsigned long long, ul);


#pragma region In File
	True_InFile::~True_InFile() {
		Close();
	}
	uint64 True_InFile::Size() {
		return size;
	}
	True_InFile::True_InFile(std::string _filename, int endian) {
		size = FileSize(_filename);
		stream.open(_filename, std::ios::binary);
		//stream = std::ifstream(_filename.c_str(), std::ifstream::ate | std::ifstream::binary);
		_ce ce; ce.i = 256;
		if (ce.ac[1]) sysendian = 1; else sysendian = 2;
		//size = stream.tellg();
		//cout << size << endl;
	}

	void True_InFile::Close() {
		if (!closed) stream.close();
	}
	bool True_InFile::endmatch() { return (!endian) || (endian == sysendian); }

	char True_InFile::ReadChar() {
		char buff;
		stream.read(&buff, 1);
		//cout << read << "/" << size << "\tRead char " << (int)buff << "/" << buff << endl;
		read++;
		return buff;
	}

	byte True_InFile::ReadByte() {
		_ce i;
		i.c = ReadChar();
		//cout << (int)i.c << endl; // debug only!
		return i.uc;
	}

#define REND(mytype)\
	_ce ce;\
	if (endmatch())\
		for (int i = 0; i < sizeof(mytype); ++i) ce.ac[i] = ReadChar();\
	else\
		for (int i = sizeof(mytype) - 1; i >= 0; --i) ce.ac[i] = ReadChar();

	int32 True_InFile::ReadInt() {
		REND(int32);
		return ce.i;
	}

	int16 True_InFile::ReadInt16() {
		REND(int16);
		return (int16)ce.i16;
	}

	int64 True_InFile::ReadLong() {
		REND(int64);
		return ce.l;
	}

	uint32 True_InFile::ReadUInt() {
		REND(uint32);
		return ce.ui;
	}

	uint16 True_InFile::ReadUInt16() {
		REND(uint16);
		return ce.ui16;
	}

	uint64 True_InFile::ReadUInt64() {
		REND(uint64);
		return ce.ul;
	}

	string True_InFile::ReadString(int l) {
		char* buf;
		string ret;
		int ln = l;
		if (!ln) ln = ReadInt();
		buf = new char[ln+1];
		buf[ln] = 0;
		for (int i = 0; i < ln; i++) buf[i] = ReadChar();
		ret = buf;
		delete []buf;
		return ret;
	}

	void True_InFile::ReadChars(char* c, int size) {
		int m = min<int>(sizeof(c), size);
		for (auto i = 0; i < m; i++) c[i] = ReadChar();
	}

	std::vector<char> True_InFile::ReadChars(int size) {
		std::vector<char>ret{};
		for (int i = 0; i < size; i++) ret.push_back(ReadChar());
		return ret;
	}

	void True_InFile::ReadCString(char* c) {
		uint64 s{ sizeof(c) };
		uint64 voorbij{ 0 };
		uint64 i = 0;
		char rc;
		do {
			rc = ReadChar();
			if (i < s) c[i] = rc; else voorbij++;
			i++;
		} while (rc);
		if (voorbij) {
			cout << "ReadCString request went " << voorbij << " character(s) past the char* length (" << s << ")\n";
		}
	}

	void True_InFile::ReadCString(char* c, int size) {
		bool nullfound{ false };
		auto s{ sizeof(c) };
		for (uint64 i = 0; i < size; i++) {
			auto ch{ ReadChar() };
			nullfound = nullfound || (!ch);
			if (i < s) c[i] = ch;
		}
		if (size > s) printf("ReadCString(&0x%x,%d): Error! String is only %llu bytes long", (int)c, size, s);
		if (!nullfound) printf("ReadCString(&0x%x,%d): There is no null-terminator found!", (int)c, size);
	}

	std::string True_InFile::ReadCString() {
		string ret{};
		char r;
		do {
			r = ReadChar();
			if (!r) return ret;
			ret += r;
		} while (true);
	}

	bool True_InFile::EndOfFile() {
		//return stream.eof();
		return read >= size;

	}

#pragma endregion
}