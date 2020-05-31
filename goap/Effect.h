#pragma once
#include "WorldState.h"

namespace goap {
    class Effect {
    public:
        virtual void Apply(WorldState& state) = 0;
    };
}
