#pragma once

#include "common/Exports.hpp"

namespace ma
{

    //typedef struct bitarray {
    //	unsigned short length; /* number of significant bits */
    //	unsigned char *value;
    //} bitarray;
    //
    //bitarray V1, V2;
    //char *V1V2;

    ///
    /// https://en.wikipedia.org/wiki/Bit_array
    ///
    /// Other literature:
    /// http://bytes.com/topic/c/answers/264520-shift-concatenate-char
    /// http://stackoverflow.com/questions/8085521/bitshift-char-array
    /// http://stackoverflow.com/questions/10367616/bitwise-shifting-array-of-chars
    /// http://stackoverflow.com/questions/9560029/of-int-char-float-and-bool-which-is-smallest#
    /// http://stackoverflow.com/questions/4975340/int-to-unsigned-int-conversion
    /// http://embeddedgurus.com/stack-overflow/2009/08/a-tutorial-on-signed-and-unsigned-integers/
    /// http://www.mathcs.emory.edu/~cheung/Courses/255/Syllabus/1-C-intro/bit-array.html
    /// https://www.c-plusplus.net/forum/162990-full
    ///
    class  MA_API BitArray
    {
    public:
        BitArray(int size);
        ~BitArray();
        bool GetBit(int index) const;
        void SetBit(int index, bool value);
        void Print();
    private:
        unsigned short m_size;  // relevant BIT size (size in bits)
        unsigned char* m_arr;
    };

    // TODO: abstract Bitarray to Btmask
    //class  MA_API Bitmask
    //{
    //public:
    //    Bitmask(int size);
    //    Bitmask(int height, int width);
    //    ~Bitmask();
    //    bool GetBit(int index) const;
    //    bool GetBit(int index_x, int index_y) const;
    //    void SetBit(int index, bool value);
    //    void SetBit(int index_x, int index_y, bool value);
    //    void Print();
    //private:
    //    unsigned short m_size;  // relevant BIT size (size in bits)
    //    unsigned short m_width;
    //    unsigned char* m_arr;
    //};
}
