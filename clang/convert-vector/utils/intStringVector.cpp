#include "intStringVector.hpp"

unsigned int stringToUnsignedInt(const std::string &str)
{
    unsigned long num = 0;
    try
    {
        num = std::stoul(str); // Convert string to unsigned long
        if (num > std::numeric_limits<unsigned int>::max())
        {
            throw std::out_of_range("Number exceeds unsigned int range");
        }
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        throw;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Out of range: " << e.what() << std::endl;
        throw;
    }
    return static_cast<unsigned int>(num);
}

std::vector<std::vector<unsigned int>> convertToUnsignedIntVector(const std::vector<std::vector<std::string>> &stringVector)
{
    std::vector<std::vector<unsigned int>> result;

    for (const auto &row : stringVector)
    {
        std::vector<unsigned int> intRow;
        for (const auto &str : row)
        {
            intRow.push_back(stringToUnsignedInt(str));
        }
        result.push_back(intRow);
    }

    return result;
}

std::vector<std::vector<std::string>> convertToStringVector(const std::vector<std::vector<unsigned int>> &intVector)
{
    std::vector<std::vector<std::string>> result;

    for (const auto &row : intVector)
    {
        std::vector<std::string> stringRow;
        for (unsigned int num : row)
        {
            stringRow.push_back(std::to_string(num));
        }
        result.push_back(stringRow);
    }

    return result;
}

std::vector<unsigned int> convertToUnsignedInt1DVector(const std::vector<std::vector<std::string>> &stringVector)
{
    std::vector<unsigned int> result;

    for (const auto &row : stringVector)
    {
        for (const auto &str : row)
        {
            result.push_back(stringToUnsignedInt(str));
        }
    }

    return result;
}
