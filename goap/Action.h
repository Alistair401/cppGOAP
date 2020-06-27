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
#include "PlannedAction.h"

namespace goap 
{
    class WorldState;

    class Action 
    {
    private:
        int cost_;

    protected:
        int id_; 

    public:
        Action(int id, int cost);

        virtual PlannedAction Act(const WorldState& goal, WorldState& preconditions, WorldState& effects) = 0;

        int GetCost() const { return cost_; }
        int Id() const { return id_; }
    };
}