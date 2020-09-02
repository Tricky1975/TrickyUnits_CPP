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
        ~TrBank();
    };
}