#pragma once
#include "WorldState.h"

namespace goap 
{
    class Precondition
    {
    public:
        virtual void Apply(WorldState& state) const = 0;
    };
}

