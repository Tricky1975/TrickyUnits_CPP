#include "..\Headers\JXSDA.hpp"
// Lic:
// Source/JXSDA.cpp
// JXSDA
// version: 20.11.10
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

// Important NOTE!
// This only works in a LITTLE ENDIAN environment!

#include <iostream>
#include <vector>
#include <string.h>

#include "../Headers/JXSDA.hpp"

#define byte unsigned char

namespace TrickyUnits{

    using namespace std;

    typedef union icv {
        char buf[8];
        unsigned char bytes[8];
        int integer;
    }icv;

    class bread {
    private:
        int pos = 0;
        int siz;
        char* buf;
    public:

        bool EOB() { return pos >= siz; }

        char RChar() {
            return buf[pos++];
        }

        icv Read(int bytes) {
            icv ret;
            for (int i = 0; i < 8; i++) {
                if (i < bytes) ret.buf[i] = RChar(); else ret.buf[i] = 0;
            }
        }

        unsigned char ReadByte() {
            icv c = Read(1);
            return c.bytes[0];
        }

        int ReadInt() {
            auto c = Read(4);
            return c.integer;
        }

        void RStr(char* k, int size, bool term=true) {
            int i = 0;
            while (i < size) k[i++] = RChar();
            if (term) k[i++] = 0;
        }


        bread(char* buffer,int size) {
            siz = size;
            buf = buffer;
        }
    };

    void jxsda_pack(char* source, int ssize, char* target, int& tsize) {
        cout << "Packing is NOT yet supported!\n";
    }

    std::vector<char> jxsda_pack(char* source, int size) {
        cout << "Packing is NOT yet supported!\n";
        return std::vector<char>();
    }

    byte b2b(byte b) {
        switch (b) {
        case 64: return 8;
        case 32: return 4;
        case 16: return 2;
        case 8: return 1;
        default: return 0;
        }
    }

    jxda_error jxsda_unpack(char* source, int ssize, char* target, int tsize) {
        // The goto statement is only meant to make sure if the code is gonna require memory allocations (I'll try to avoid them) that in case of errors the release codes are always run
        auto ecode = jxda_error::Ok;
        vector<icv> Dictionary;
        char header[10];
        bread MS(source, ssize);
        byte ubit;
        byte pbit;
        byte rest;
        int dsiz;
        vector<byte> restbuf;
        int opos = 0;
        byte rlen = 0;
        byte wlen = 0;
        if (ssize < 25) { ecode = jxda_error::TooSmall; goto einde; }
        MS.RStr(header, 6);
        if (strcmp(header, "JXSDA\x1a") != 0) { ecode = jxda_error::NotJXDA; goto einde; }
        ubit = MS.ReadByte();
        pbit = MS.ReadByte();
        rest = MS.ReadByte();
        dsiz = MS.ReadInt();
        rlen = b2b(pbit);
        wlen = b2b(ubit);
        for (int i = 0; i < dsiz; i++) Dictionary.push_back(MS.Read(rlen));
        for (int i = 0; i < rest; i++) restbuf.push_back(MS.ReadByte());
        while (!MS.EOB()) {
            auto r = MS.Read(rlen);            
            if (r.integer >= Dictionary.size()) { ecode = jxda_error::DictionaryIndexError; goto einde; }
            for (int i = 0; i < wlen; i++) {
                if (opos >= tsize) { ecode = jxda_error::UnpackSizeOverflow; goto einde; }
                target[opos++] = Dictionary[r.integer].buf[i];
            }
        }
        for (byte b : restbuf) {
            if (opos >= tsize) { ecode = jxda_error::UnpackSizeOverflow; goto einde; }
            target[opos++] = b;
        }
        if (opos < tsize) { ecode = jxda_error::UnpackSizeUnderflow; goto einde; }
        // TODO: Actual code!
        einde:
        return ecode;
    }

    std::vector<char> jxsda_unpack(char* source, int ssize, int tsize) {
        auto obuf = new char[tsize];
        auto e = jxsda_unpack(source, ssize, obuf, tsize);
        if (e != jxda_error::Ok) {
            cout << "\x7 SOMETHING WENT WRONG IN UNPACKING! (" << (int)e << ")   EXPECT FAULTY DATA!\n";
        }

        return std::vector<char>(obuf,obuf+tsize);
    }



}