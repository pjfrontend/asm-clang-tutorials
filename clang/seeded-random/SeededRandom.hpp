#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

class SeededRandom
{
private:
    double seed;

public:
    SeededRandom(int seed) : seed(seed) {}

    double random();
    int randomInRange(int min, int max);
    int randomInRangeExceptFor(int min, int max, const std::vector<int> &except);
    int choice(const std::vector<int> &arr);
    std::vector<int> shuffle(const std::vector<int> &unshuffled);
};
