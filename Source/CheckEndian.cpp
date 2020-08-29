// Lic:
// Source/CheckEndian.cpp
// Check Endian
// version: 20.08.29
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
#undef Test_EndianCheck

#include "../Headers/CheckEndian.hpp"

typedef union {
  unsigned char b[8];
  int i;
  _int32 i32;
} ucheck;

namespace TrickyUnits{
  bool IsLittleEndian(){
    ucheck chk;
    chk.i=256;
    return chk.b[1]==1;
  }

  bool IsBigEndian() { return !IsLittleEndian();}

  _int32 Reverse(_int32 i) {
      ucheck iget;
      ucheck iset; 
      for (int j = 0; j < 8; j++) {
          iget.b[j] = 0;
          iset.b[j] = 0;
      }
      iget.i32 = i;
      for (int j = 0; j < sizeof(_int32); ++j) iset.b[sizeof(_int32) - j] = iget.b[j];
      return iset.i32;
  }

  _int32 ToLittleEndian(_int32 i) {
      static bool TLE = IsLittleEndian();
      if (TLE) return i; // System is already little endian, not need to switch this around!
      return Reverse(i);
  }

  _int32 ToBigEndian(_int32 i) {
      static bool TBE = IsBigEndian();
      if (TBE) return i; // System is already little endian, not need to switch this around!
      return Reverse(i);
  }


}


#ifdef Test_EndianCheck
#include <iostream>
using namespace TrickyUnits;

int main(){
  if (IsLittleEndian())
    std::cout << "System is LittleEndian\n";
  else
    std::cout << "System is BigEndian\n";
}

#endif