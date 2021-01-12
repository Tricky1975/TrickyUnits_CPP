// Lic:
// Headers/Bank.hpp
// Bank
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
#pragma once
#include <cstddef>

namespace TrickyUnits{
    class TrBank {
    private:
        char* buf = NULL;
        unsigned long long size = 0;
    public:
        static bool EnforceLittleEndian;
        bool AutoKill = true;
        void Poke(unsigned long long offs, char value);
        void Poke(unsigned long long offs, unsigned char value);
        void Poke(unsigned long long offs, int value);
        void Poke(unsigned long long offs, unsigned int value);
        void Poke(unsigned long long offs, long long value);
        void Poke(unsigned long long offs, unsigned long long value);
        char PeekChar(unsigned long long offs);
        unsigned char PeekByte(unsigned long long offs);
        int PeekInt32(unsigned long long offs);
        long long PeekInt64(unsigned long long offs);
        unsigned int PeekUInt32(unsigned long long offs);
        unsigned long long PeekUInt64(unsigned long long offs);
        void Create(unsigned long long bufsize);
        void Kill();
        unsigned long long Size();
        ~TrBank();
    };
}