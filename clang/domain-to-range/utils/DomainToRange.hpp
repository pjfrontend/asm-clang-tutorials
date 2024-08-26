#pragma once

// Define a struct to hold the parameters
struct RangeConversionParameters
{
    double value;
    double domainMax;
    double domainMin;
    double rangeMax;
    double rangeMin;
};

// Function to convert a value from one range to another using the struct
double convertDomainToRange(const RangeConversionParameters &params);