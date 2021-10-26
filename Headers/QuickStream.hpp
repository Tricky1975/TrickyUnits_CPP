// Lic:
// Headers/QuickStream.hpp
// Quick Stream (header)
// version: 21.10.26
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


	class True_OutFile;
	typedef shared_ptr<True_OutFile> OutFile;
	OutFile WriteFile(string fname, int endian = 1);

	class True_OutFile {
	private:
		std::string FileName;
		std::ofstream stream;
		bool closed{ false };
		int endian{ 1 }; // 0 = don't check! 1 = little endian! 2 = big endian!
		int sysendian;
		bool endmatch();
		unsigned long long Written{ 0 };
	public:

		/// <summary>
		/// When set true (default) this automatically closes a file when this instance is disposed from the memory
		/// Only set to false when you know what you are doing. This class is to be used as a shared pointer only after all.
		/// </summary>
		bool AutoClose{ true };

		True_OutFile(std::string _filename,int endian=1);
		~True_OutFile();
		void Write(char c);
		void Write(unsigned char c);
		
		// Some syntax checking editors (like Visual Studio) won't like the way this is defined and show warning lines.
		// These lines warning that the actual function doesn't exist, while in fact, it does. But I was lazy, so I chose a dirty way to do this!
		void Write(int i);
		void Write(unsigned int i);
		void Write(long long i);
		void Write(unsigned long long i);
		void Write(string s, bool raw = false);
		void Write(vector<char> buf, bool storelength = false);

		void WriteCString(const char* str);

		unsigned long long Size();

		void Close();
	};

}
#endif