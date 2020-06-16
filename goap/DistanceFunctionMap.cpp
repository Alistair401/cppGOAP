#include "DistanceFunctionMap.h"

const goap::DistanceFunction& goap::DistanceFunctionMap::Get(int variable) const
{
    auto found = this->functions.find(variable);

    if (found == this->functions.end())
    {
        return this->defaultDistance;
    }
    else 
    {
        return found->second;
    }
}

void goap::DistanceFunctionMap::Set(int variable, DistanceFunction f)
{
    this->functions[variable] = f;
}
