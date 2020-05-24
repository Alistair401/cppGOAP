#pragma once
#include "WorldState.h"

namespace goap 
{
    class Precondition 
    {
    public:
        virtual bool IsMet(const WorldState& state) const = 0;
    };
}

