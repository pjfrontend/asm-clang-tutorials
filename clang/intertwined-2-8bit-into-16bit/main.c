#include <stdio.h>
#include <stdint.h>
#include <string.h>

// https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
const char *byte_to_binary(int x)
{
    static char b[9];
    b[0] = '\0';

    int z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

const char *word_to_binary(int x)
{
    static char b[17];
    b[0] = '\0';

    int z;
    for (z = 32768; z > 0; z >>= 1)
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
        unsigned char slice_a = a >> i & 0b1;
        printf("slice_a %d\n", slice_a);
        unsigned char slice_b = b >> i & 0b1;
        printf("slice_b %d\n", slice_b);

        uint16_t offset_a = slice_a << i * 2 + 1;
        printf("%s\n", word_to_binary(offset_a));
        output |= offset_a;

        uint16_t offset_b = slice_b << i * 2;
        printf("%s\n", word_to_binary(offset_b));
        output |= offset_b;

        printf("output %d\n", output);
    }
    return output;
}

int main(int argc, char *argv[])
{
    printf("%s\n", word_to_binary(interleave_2_8bit_into_16bit(0b01111111, 0b11111110)));
    return 0;
}