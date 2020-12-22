#pragma once
#include "WorldState.h"

namespace goap
{
    struct EvaluatedAction
    {
        int id = -1;
        WorldState preconditions;
        WorldState effects;
    };
}
