#pragma once
#include "WorldState.h"

namespace goap 
{
    class Effect
    {
    public:
        virtual bool ResolvesAny(const WorldState& state) = 0;
        virtual void Resolve(WorldState& state) = 0;
    };
}
