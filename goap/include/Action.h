/**
 * @class Action
 * @brief Operates on the world state.
 *
 * @date  July 2014
 * @copyright (c) 2014 Prylis Inc.. All rights reserved.
 */

#pragma once

#include <unordered_map>
#include <memory>
#include <optional>
#include "Effect.h"
#include "Precondition.h"
#include "EvaluatedAction.h"

namespace goap 
{
    class WorldState;

    class Action 
    {
    protected:
        int id_; 

    public:
        Action(int id);

        virtual std::vector<EvaluatedAction> Act(void* world, const WorldState& goal) = 0;

        int Id() const { return id_; }
    };
}