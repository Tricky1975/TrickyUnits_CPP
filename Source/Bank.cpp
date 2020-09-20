// Lic:
// Source/Bank.cpp
// Bank
// version: 20.09.20
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

#undef TrickyUnits_TestBanking

#include <iostream>
#include "../headers/Bank.hpp"
#include "../Headers/CheckEndian.hpp"

typedef union convert {
    char arch[10];
    char valch;
    unsigned char valuch;    
    int valint32;
    unsigned int valuint32;
    long long valint64;
    unsigned long long valuint64;
    // will do for now, but may be replaced over time.
} convert;

#define CPokeLarge(value)\
    for(unsigned long long i=0;i<sizeof(value);++i){\
        if (EnforceLittleEndian && !IsLittleEndian())\
            Poke((sizeof(value)-1)-i,cv.arch[i]);\
        else\
            Poke(i,cv.arch[i]);\
    }

#define CPeekLarge()\
    convert cv;\
    for (unsigned long long i = 0; i < sizeof(ret); ++i) {\
        if (EnforceLittleEndian && !IsLittleEndian())\
            cv.arch[i] = PeekChar((sizeof(ret) - 1) - i);\
        else\
            cv.arch[i] = PeekChar(i);\
    }\
    return ret;

    

namespace TrickyUnits {
    bool TrBank::EnforceLittleEndian = true;

    void TrBank::Poke(unsigned long long offs, char value) {
        if (buf == NULL) {
            std::cout << "\aCannot poke in non-defined bank";
            return;
        }
        if (offs >= size) {
            std::cout << "\aPoke index out of range!";
            return;
        }
        buf[offs] = value;
    }
    void TrBank::Poke(unsigned long long offs, unsigned char value) {
        if (buf == NULL) {
            std::cout << "\aCannot poke in non-defined bank";
            return;
        }
        if (offs >= size) {
            std::cout << "\aPoke index out of range!";
            return;
        }
        convert cv; cv.valuch = value;
        buf[offs] = cv.valch;
    }

    void TrBank::Poke(unsigned long long offs, int value) {
        convert cv;
        cv.valint32 = value;
        CPokeLarge(value);
    }

    void TrBank::Poke(unsigned long long offs, unsigned int value) {
        convert cv;
        cv.valuint32 = value;
        CPokeLarge(value);
    }

    void TrBank::Poke(unsigned long long offs, long long value) {
        convert cv;
        cv.valint64 = value;
        CPokeLarge(value);
    }

    void TrBank::Poke(unsigned long long offs, unsigned long long value) {
        convert cv;
        cv.valuint64 = value;
        CPokeLarge(value);
    }

    unsigned char TrBank::PeekByte(unsigned long long offs) {
        if (buf == NULL) {
            std::cout << "\aCannot poke in non-defined bank";
            return 0;
        }
        if (offs >= size) {
            std::cout << "\aPoke index out of range!";
            return 0;
        }
        convert cv;
        cv.valch=buf[offs];
        return cv.valuch;
    }

    int TrBank::PeekInt32(unsigned long long offs) { int ret=0; CPeekLarge(); }
    long long TrBank::PeekInt64(unsigned long long offs) { long long ret=0; CPeekLarge(); }
    unsigned int TrBank::PeekUInt32(unsigned long long offs) { unsigned int ret=0; CPeekLarge(); }
    unsigned long long TrBank::PeekUInt64(unsigned long long offs) { unsigned long long ret=0; CPeekLarge(); }

    void TrBank::Create(unsigned long long offs) {
        if (AutoKill && buf) Kill();
        buf = new char[offs];
        size = offs;
    }

    void TrBank::Kill() { 
#ifdef TrickyUnits_TestBanking
        std::cout << "A bank holding " << size << " bytes was disposed!\n";
#endif
        delete[] buf; size = 0; buf = 0; 
    }

    unsigned long long TrBank::Size() {
        return size;
    }

    TrBank::~TrBank() {
        if (AutoKill && buf) Kill();
    }


    char TrBank::PeekChar(unsigned long long offs) {
        if (buf == NULL) {
            std::cout << "\aCannot poke in non-defined bank";
            return 0;
        }
        if (offs >= size) {
            std::cout << "\aPoke index out of range!";
            return 0;
        }
        return buf[offs];
    }

}
    
#ifdef TrickyUnits_TestBanking
    int main() {
        TrickyUnits::TrBank Test;
        Test.Create(10);
        for (int i = -10000000; i <= 10000000; i+=5) {
            Test.Poke(0, i);
            std::cout << "Num:" << i << "\t byte1:" << (int)Test.PeekByte(0) << "\t byte2:" << (int)Test.PeekByte(1) << "\t byte3:" << (int)Test.PeekByte(2) << "\t byte4:" << (int)Test.PeekByte(3)<<"\n";
        }
        return 0;
    }
#endif