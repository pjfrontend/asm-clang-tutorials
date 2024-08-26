#include <iostream>
#include "utils/lfsr.hpp"

int main()
{
    uint8_t value = 0xAB; // Example value
    uint8_t result_right_shift = lfsr_fibonacci_right_shift_8bit(value);
    uint8_t result_left_shift = lfsr_fibonacci_left_shift_8bit(result_right_shift);

    std::cout << "Original value: " << std::hex << static_cast<int>(value) << std::endl;
    std::cout << "Right shift result: " << std::hex << static_cast<int>(result_right_shift) << std::endl;
    std::cout << "Left shift result: " << std::hex << static_cast<int>(result_left_shift) << std::endl;

    value = 0xA; // Example value
    result_right_shift = lfsr_fibonacci_right_shift_4bit(value);
    result_left_shift = lfsr_fibonacci_left_shift_4bit(result_right_shift);

    std::cout << "Original value: " << std::hex << static_cast<int>(value) << std::endl;
    std::cout << "Right shift result: " << std::hex << static_cast<int>(result_right_shift) << std::endl;
    std::cout << "Left shift result: " << std::hex << static_cast<int>(result_left_shift) << std::endl;

    for (size_t i = 1; i < 20; i++)
    {
        value = lfsr_fibonacci_right_shift_4bit(value);
        std::cout << i << " : " << std::hex << static_cast<int>(value) << std::endl;
    }

    return 0;
}
