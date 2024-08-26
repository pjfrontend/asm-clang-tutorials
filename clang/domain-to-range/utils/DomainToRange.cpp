#include "DomainToRange.hpp"

double convertDomainToRange(const RangeConversionParameters &params)
{
    double rangeVal = (params.value - params.domainMin) / (params.domainMax - params.domainMin);
    return (params.rangeMax - params.rangeMin) * rangeVal + params.rangeMin;
}