#pragma once
#include <vector>
#include <string>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <stddef.h>
#include <limits>

unsigned int stringToUnsignedInt(const std::string &str);
std::vector<std::vector<unsigned int>> convertToUnsignedIntVector(const std::vector<std::vector<std::string>> &stringVector);
std::vector<std::vector<std::string>> convertToStringVector(const std::vector<std::vector<unsigned int>> &intVector);
std::vector<unsigned int> convertToUnsignedInt1DVector(const std::vector<std::vector<std::string>> &stringVector);