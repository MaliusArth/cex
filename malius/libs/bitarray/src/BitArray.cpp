#include <malius/BitArray.hpp>
#include <climits>
#include <cassert>
#include <iostream>

namespace ma
{

#define char_index(bit_index) (int)(bit_index/CHAR_BIT)

    // size in bits
    BitArray::BitArray(int size)
    {
        m_size = static_cast<unsigned short>(size);
        // n-tes array element
        //7 / 8 = 0,875
        //9 / 8 = 1,125

        // n-tes bit im char
        //7 % 8 = 7
        //9 % 8 = 1

        // ceilf(size / CHAR_BIT);
        // size = 13
        // 13 / 8 = 1.625
        // ceilf(13/8) = 2
        // 1.625 + 0.9 = 2.525 (2)
        // 1 / 8 = 0.125
        // 0.125 + 0.9 = 1.025 (1)
        m_arr = new unsigned char[static_cast<int>((size / CHAR_BIT) + 0.9f)]{};	// int cast truncates fractional values, returning integral value; ceil if has factorials (going in 0.125 steps due to 1 / 8, so could as well be 0.875f)

        // TODO: find better way to initialize array with zeros!
        /*for (int i = 0; i < (int)(size / CHAR_BIT); ++i)
        {
        m_arr[(int)(i / CHAR_BIT)] = 0;
        }*/

        //std::cout << "Created char array of size: " << (sizeof(m_arr) / sizeof(*m_arr)) << std::endl;
        std::cout << "size: " << m_size << std::endl;
    };
    BitArray::~BitArray()
    {
        delete[] m_arr;
    };

    ///
    /// http://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit-in-c-c?rq=1
    /// index: The index of the accessed bit
    /// return: Returns the bit at the index of the bit array
    ///
    bool BitArray::GetBit(int index) const
    {
        //assert(index >= 0 && (index / CHAR_BIT) < m_size);
        if (index >= 0 && (index / CHAR_BIT) < m_size)
        {
            return ((m_arr[static_cast<int>(index / CHAR_BIT)] >> (index % CHAR_BIT)) & 1);
        }
        else
        {
            // ERROR: out of bounds
            std::cout << "Out of bounds" << std::endl;
            return false;		// TODO
        }

        ////
        // index = 0,1,2,3,4,5,6,7|8,9,10,11,12,13,14,15|16,17,...
        // index = 1
        // 1 / 8 = 0.125 => 0-tes array element
        // 1 % 8 = 1 => 1-tes bit

        // ACTUALLY!!!
        // index =	7,6,5,4,	 |	 3,2,1,0|
        //			15,14,13,12, | 11,10,9,8|
        //			....		 |	..,17,16|
        ////
    };
    // http://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit-in-c-c?rq=1
    void BitArray::SetBit(int index, bool value)
    {
        // number ^= (-x ^ number) & (1 << n);
        // set the bit at position 2 for number 64
        // x = 0 (false) / 1 (true)
        // n = 2
        // number = 64
        // 64 XOR (-1 XOR 64) AND (1 << 2)
        // (-1 XOR 64) = -65 [1111 1111 XOR 1011 1111]
        // (1 << 2) = 4	[0000 0100]


        //TODO:	bounds checking via assert?
        //assert(index >= 0 && (index / CHAR_BIT) < m_size);
        if (index >= 0 && index < m_size)
        {
            //number ^= (-x ^ number) & (1 << n);
            m_arr[/*(int)*/char_index(index)] ^= (-static_cast<int>(value) ^ m_arr[/*(int)*/char_index(index)]) & (1 << (index % CHAR_BIT));
        }
        else
        {
            // ERROR: out of bounds
            std::cout << "Out of bounds" << std::endl;
        }
    };
    void BitArray::Print(void) const
    {
        int j = 0;
        for (int i = 0; i < m_size; ++i)
        {
            if (/*(int)*/char_index(i) > j)
            {
                j++;
                std::cout << std::endl;
            }
            printf("%c", GetBit(i) ? '1' : '0');
        }
        printf("\n");
    }
}
