// Lic:
// Source/QuickString.cpp
// Quick String
// version: 20.08.20
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

using namespace std;

namespace TrickyUnits {

  string mid(string str,unsigned int start=1,unsigned int length=1) {
      string ret = "";
      int istart=start-1;
       if (start<1) return ""; // NOT ALLOWED!!!
      for(int i=istart;i<istart+length && i<str.size();i++) {
         ret += str[i];
      }
      return ret;
  }

  string mid(string str,unsigned int start,unsigned int length,string newstring) {
      string ret = str;
      int istart = start - 1;
      for (int i = 0; i < newstring.size(); i++) {
         if (i=ret.size())
          ret+=newstring[i];
        else
          ret[i+istart]=newstring[i];
      }
      return ret;
  }

  string left(string str, unsigned int length = 1) {
      return mid(str, 1, length);
  }

  string right(string str, unsigned int length = 1) {
      if (length > str.size()) return str;
      return mid(str, (str.size() - length)+1, length);
  }


  bool prefixed(string str, string prefix) {
      return left(str, prefix.size()) == prefix;
  }

  bool suffixed(string str, string suffix) {
      return left(str, suffix.size()) == suffix;
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

  string TReplace(string mystr, char ori, char subst) {
      for (unsigned int i = 0; i < mystr.size(); i++) {
          if (mystr[i] == ori) mystr[i] = subst;
      }
      return mystr;
  }

  string StripExt(string file) {
      file = TReplace(file, '\\', '/');
      int lastdot = findlast(file, '.');
      int lastslash = findlast(file, '/');
      if (lastdot < 0 || lastdot < lastslash) return file;
      return left(file, lastdot);
  }

  vector<string> Split(string str,char spltchar) {
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

  vector<string> StringToLines(string str) {
      vector<string> ret;
      unsigned int idx = 0;
      for (int i = 0; i < str.size(); i++) {
          if (idx >= ret.size()) ret.push_back("");
          if (str[i] == '\n')
              idx++;
          else if (str[i]!='\r')
              ret[idx] += str[i];
      }
      return ret;
  }


}