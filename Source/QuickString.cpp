// Lic:
// Source/QuickString.cpp
// Quick String
// version: 20.10.06
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
#include <string>
#include <vector>
#include <algorithm>
// #include <iostream> 
#include "../Headers/QuickString.hpp"


// 3rd party
// #include "3rd_party/md5.hpp"

using namespace std;

namespace TrickyUnits {

    string mid(string str, unsigned int start , unsigned int length ) {
        string ret = "";
        int istart = start - 1;
        if (start < 1) return ""; // NOT ALLOWED!!!
        for (int i = istart; i < istart + length && i < str.size(); i++) {
            ret += str[i];
        }
        return ret;
    }

    string mid(string str, unsigned int start, unsigned int length, string newstring) {
        string ret = str;
        int istart = start - 1;
        for (int i = 0; i < newstring.size(); i++) {
            if (i = ret.size())
                ret += newstring[i];
            else
                ret[i + istart] = newstring[i];
        }
        return ret;
    }

    string left(string str, unsigned int length ) {
        return mid(str, 1, length);
    }

    string right(string str, unsigned int length) {
        if (length > str.size()) return str;
        return mid(str, (str.size() - length) + 1, length);
    }
    //string right(string str, size_t length) { return right(str, (unsigned int)length); }


    bool prefixed(string str, string prefix) {
        return left(str, prefix.size()) == prefix;
    }

    bool suffixed(string str, string suffix) {
        return right(str, suffix.size()) == suffix;
    }

    /// <summary>
    /// Find last occurance of a character in a string
    /// </summary>
    /// <param name="str"></param>
    /// <param name="ch"></param>
    /// <returns>The index number of the last occurance or -1 when the character has not been found at all</returns>
    int findlast(string str, char ch) {
        int i = str.size();
        do {
            i--;
        } while (i > 0 && str[i] != ch);
        return i;
    }

    int findlast(string haystack, string needle) {
        int i = haystack.size() - needle.size();
        if (i < 0) return -1;
        do {
            i--;
        } while (i > 0 && mid(haystack, i, needle.size()) != needle);
        return i;
    }

    int findfirst(string str, char ch) {
        for (int i = 0; i < str.size(); i++)
            if (str[i] == ch) return i;
        return -1;
    }

    string TReplace(string mystr, char ori, char subst) {
        for (unsigned int i = 0; i < mystr.size(); i++) {
            if (mystr[i] == ori) mystr[i] = subst;
        }
        return mystr;
    }

    std::string TReplace(std::string mystr, std::string ori, std::string subst) {
        /* bugged
        std::string ret ="";
        auto olen = mystr.size();
        auto slen = ori.size();
        unsigned p = 1;
        while (p + slen <= olen) {
            if (mid(mystr, p, slen) == ori) {
                ret += subst;
                p +=slen;
            } else {
                ret += mystr[p-1];
                p++;
            }
        }
        return ret;
        */
        //* Fixed?
        std::string ret = "";
        auto olen = mystr.size();
        auto slen = ori.size();
        unsigned p = 1;
        while (p <= olen) {
            if ((p - 1) + slen <= olen && mid(mystr, p, slen) == ori) {
                ret += subst;
                p += slen;
                //cout << p << ":"<<olen<<endl;
            } else {
                ret += mystr[p - 1];
                p++;
            }
        }
        return ret;
        //*/
    }

    std::string ExtractDir(std::string file) {
        file = TReplace(file, '\\', '/');
        int lastslash = findlast(file, '/');
        if (lastslash < -1) return "";
        return left(file, lastslash);        
    }

    std::string StripDir(std::string file) {
        file = TReplace(file, '\\', '/');
        int lastslash = findlast(file, '/');
        if (lastslash < -1) return file;
        auto ret = right(file,file.size()-lastslash);
        while (ret.size() && ret[0] == '/') ret = right(ret, ret.size() - 1);
        return ret;
    }

    string StripExt(string file) {
        file = TReplace(file, '\\', '/');
        int lastdot = findlast(file, '.');
        int lastslash = findlast(file, '/');
        if (lastdot < 0 || lastdot < lastslash) return file;
        return left(file, lastdot);
    }

    vector<string> Split(string str, char spltchar) {
        vector<string> ret;
        unsigned int idx = 0;
        for (int i = 0; i < str.size(); i++) {
            if (idx >= ret.size()) ret.push_back("");
            if (str[i] == spltchar)
                idx++;
            else
                ret[idx] += str[i];
        }
        return ret;
    }

    vector<string> Split(string str, char spltchar,int max) {
        vector<string> ret;
        unsigned int idx = 0;
        for (int i = 0; i < str.size(); i++) {
            if (idx >= ret.size()) ret.push_back("");
            if (str[i] == spltchar && idx<max)
                idx++;
            else
                ret[idx] += str[i];
        }
        return ret;
    }


    vector<string> StringToLines(string str) {
        vector<string> ret;
        unsigned int idx = 0;
        for (int i = 0; i < str.size(); i++) {
            if (idx >= ret.size()) ret.push_back("");
            if (str[i] == '\n')
                idx++;
            else if (str[i] != '\r')
                ret[idx] += str[i];
        }
        return ret;
    }

    string Trim(string str) {
        string ret = "";
        bool begun = false;
        // before!
        for (int i = 0; i < str.size(); ++i) {
            begun = begun || (str[i] != ' ' && str[i] != '\t' && str[i] != '\r' && str[i] != '\n');
            if (begun)
                ret += str[i];
        }
        if (ret == "") return ""; // No need to go on if the string's empty now!
        /*
        for (int i = str.size() - 1; i >= 0; --i) {
            if (str[i] != ' ' && str[i] != '\t' && str[i] != '\r' && str[i] != '\n') return ret;
            ret[i] = '\0';
        }
        */
        while (            
            ret[ret.size() - 1] == ' ' ||
            ret[ret.size() - 1] == '\t' ||
            ret[ret.size() - 1] == '\n' ||
            ret[ret.size() - 1] == '\t'
            ) {
            // cout << ret << " (" << ret.size() << ")\n";
            ret = left(ret, ret.size() - 1);
            if (ret == "") return "";
        }
        return ret; // Should never happen, but at least this prevents crashes, exceptions, whatever!
    }

    void Trans2Upper(string& str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper); 
    }

    void Trans2Lower(string& str) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    }


    string Upper(string str)  {
        string ret = str;
        Trans2Upper(ret);
        return ret;
    }

    std::string Lower(std::string str) {
        string ret = str;
        Trans2Lower(ret);
        return ret;
    }

    string bsdec(const char* str) {
        string ret = "";
        for (int i = 0; str[i]; i++) {
            auto c = str[i];
            if (c == ' ' || (c >= 'a' && c <= 'z') || (c >= '0' && c <= ':') || (c >= 'A' && c <= 'Z'))
                ret += c;
            else {
                char fme[10];
                sprintf_s(fme, 6, "\\%03d", c);
                ret += fme;
            }
        }
        return ret;
    }
    string bsdec(string str) { return bsdec(str.c_str()); }

    std::string hashmd5(std::string str) {
        /* original
            auto hash = ConstexprHashes::md5("jaklsdjlkad");
            cout << hex;
            for (auto i : hash) {
                cout << (static_cast<int>(i) & 0xff);
            }
            cout << endl;
        */
        return "Not yet operational"; 
    }

    std::string Hex(int num) {
        char H[10];
        sprintf_s(H, "%08X", num);
        return std::string(H);
    }

    std::string StringJoin(std::string lnk, std::vector<std::string> strs) {
        string ret{ "" };
        for (auto s : strs) {
            if (ret.size()) ret += lnk;
            ret += s;
        }
        return ret;
    }


    string ExtractExt(std::string file){
        file = TReplace(file, '\\', '/');
        int lastdot = findlast(file, '.');
        int lastslash = findlast(file, '/');
        if (lastdot < 0 || lastdot < lastslash) return "";
        return file.substr(lastdot + 1); //left(file, lastdot);
    }
     
}