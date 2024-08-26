#include <iostream>
#include "utils/DomainToRange.hpp"

int main()
{
    // Example usage
    RangeConversionParameters params = {5.0, 10.0, 0.0, 100.0, 50.0};

    double result = convertDomainToRange(params);
    std::cout << "Converted value: " << result << std::endl;

    return 0;
}
