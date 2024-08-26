#include "SeededRandom.hpp"

int main()
{
    SeededRandom rng(42); // Example seed value
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<int> except = {3};

    std::cout << "Random number: " << rng.random() << std::endl;
    std::cout << "Random in range (1-10): " << rng.randomInRange(1, 10) << std::endl;
    std::cout << "Random in range except for 3: " << rng.randomInRangeExceptFor(1, 10, except) << std::endl;
    std::cout << "Random choice from vector: " << rng.choice(numbers) << std::endl;

    // Example shuffle
    std::vector<int> shuffled = rng.shuffle(numbers);
    std::cout << "Shuffled vector: ";
    for (const auto &num : shuffled)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
