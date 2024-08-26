#include <iostream>
#include <cstdint>
#include <string.h>

const char *byte_to_binary(int x)
{
    static char b[9];
    b[0] = '\0';

    for (int z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

const char *word_to_binary(int x)
{
    static char b[17];
    b[0] = '\0';

    for (int z = 32768; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

uint16_t interleave_2_8bit_into_16bit(uint8_t a, uint8_t b)
{
    uint16_t output = 0;
    for (size_t i = 0; i < 8; i++)
    {
        unsigned char slice_a = (a >> i) & 0b1;
        // std::cout << "slice_a " << static_cast<int>(slice_a) << std::endl;
        unsigned char slice_b = (b >> i) & 0b1;
        // std::cout << "slice_b " << static_cast<int>(slice_b) << std::endl;

        uint16_t offset_a = slice_a << (i * 2 + 1);
        // std::cout << word_to_binary(offset_a) << std::endl;
        output |= offset_a;

        uint16_t offset_b = slice_b << (i * 2);
        output |= offset_b;

        // std::cout << "output " << output << std::endl;
    }
    return output;
}

int main()
{
    std::cout << word_to_binary(interleave_2_8bit_into_16bit(0b11111111, 0b00000000)) << std::endl;
    return 0;
}
