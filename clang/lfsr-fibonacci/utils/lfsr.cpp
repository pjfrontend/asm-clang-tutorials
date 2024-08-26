#include "lfsr.hpp"

uint8_t lfsr_fibonacci_right_shift_8bit(uint8_t value)
{
    uint8_t lfsr = value & 0xff;
    // Polynomial: x^8 + x^4 + x^3 + x^2
    uint8_t bit = (lfsr >> 6) ^ (lfsr >> 5) ^ (lfsr >> 4) ^ lfsr;
    lfsr >>= 1;
    lfsr |= bit << 7;
    return lfsr & 0xff;
}

uint8_t lfsr_fibonacci_left_shift_8bit(uint8_t value)
{
    uint8_t lfsr = value & 0xff;
    uint8_t bit = (lfsr >> 7) ^ (lfsr >> 5) ^ (lfsr >> 4) ^ (lfsr >> 3);
    lfsr <<= 1;
    lfsr |= bit & 1;
    return lfsr & 0xff;
}

uint8_t lfsr_fibonacci_right_shift_4bit(uint8_t value)
{
    uint8_t lfsr = value & 0xf;
    // Polynomial: x^4 + x^3
    uint8_t bit = (lfsr >> 1) ^ lfsr;
    lfsr >>= 1;
    lfsr |= bit << 3;
    return lfsr & 0xf;
}

uint8_t lfsr_fibonacci_left_shift_4bit(uint8_t value)
{
    uint8_t lfsr = value & 0xf;
    uint8_t bit = (lfsr >> 3) ^ lfsr;
    lfsr <<= 1;
    lfsr |= bit & 1;
    return lfsr & 0xf;
}