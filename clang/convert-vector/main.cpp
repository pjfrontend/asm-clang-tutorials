#include "utils/intStringVector.hpp"

int main()
{
    // Example usage
    std::vector<std::vector<std::string>> stringVector = {
        {"123", "456", "789"},
        {"10", "20", "30"}};

    try
    {
        std::vector<std::vector<unsigned int>> intVector = convertToUnsignedIntVector(stringVector);

        // Print result
        for (const auto &row : intVector)
        {
            for (unsigned int num : row)
            {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Example usage
    std::vector<std::vector<unsigned int>> intVector = {
        {123, 456, 789},
        {10, 20, 30}};

    std::vector<std::vector<std::string>> stringVector2 = convertToStringVector(intVector);

    // Print result
    for (const auto &row : stringVector2)
    {
        for (const auto &str : row)
        {
            std::cout << str << " ";
        }
        std::cout << std::endl;
    }

    // Example usage
    std::vector<std::vector<std::string>> stringVector3 = {
        {"123", "456", "789"},
        {"10", "20", "30"}};

    try
    {
        std::vector<unsigned int> intVector = convertToUnsignedInt1DVector(stringVector3);

        // Print result
        for (unsigned int num : intVector)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
