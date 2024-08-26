#include "SeededRandom.hpp"

double SeededRandom::random()
{
    seed = std::sin((seed += 123));
    return seed;
}

int SeededRandom::randomInRange(int min, int max)
{
    int range = max - min + 1;
    // std::cout << "range: " << range << std::endl;
    int num = ((unsigned int)(100 * random()) % range) + min;
    // std::cout << "num: " << num << std::endl;
    return num;
}

int SeededRandom::randomInRangeExceptFor(int min, int max, const std::vector<int> &except)
{
    int payload = randomInRange(min, max);
    if (std::find(except.begin(), except.end(), payload) != except.end())
    {
        return randomInRangeExceptFor(min, max, except);
    }
    return payload;
}

int SeededRandom::choice(const std::vector<int> &arr)
{
    return arr[randomInRange(0, arr.size())];
}

std::vector<int> SeededRandom::shuffle(const std::vector<int> &unshuffled)
{
    std::vector<std::pair<int, double>> temp;
    for (const auto &value : unshuffled)
    {
        temp.push_back({value, random()});
    }
    std::sort(temp.begin(), temp.end(), [](std::pair<int, double> a, std::pair<int, double> b)
              { return a.second < b.second; });
    std::vector<int> shuffled;
    for (const auto &pair : temp)
    {
        shuffled.push_back(pair.first);
    }
    return shuffled;
}
