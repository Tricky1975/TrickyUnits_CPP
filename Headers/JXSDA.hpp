#pragma once
#include <vector>

namespace TrickyUnits {

	enum class jxda_error { Ok, NotJXDA, TooSmall, DictionaryIndexError, UnpackSizeOverflow, UnpackSizeUnderflow };


	void jxsda_pack(char *source,int ssize,char *target,int &tsize);
	std::vector<char> jxsda_pack(char *source,int size);
	jxda_error jxsda_unpack(char *source,int ssize,char *target, int tsize);
	std::vector<char> jxsda_unpack(char *source, int ssize, int tsize);

}
