/**
 * @class Planner
 * @brief Implements an A* algorithm for searching the action space
 *
 * @date July 2014
 * @copyright (c) 2014 Prylis Inc. All rights reserved.
 */

#pragma once

#include "Action.h"
#include "PlannedAction.h"
#include "Node.h"
#include "WorldState.h"

#include <ostream>
#include <unordered_map>
#include <vector>

namespace goap {
    class Planner {
    public:
        Planner() = delete;
        Planner(const Planner& other) = delete;

        /**
         Actually attempt to formulate a plan to get from start to goal, given a pool of
         available actions.
         @param start the starting worldstate
         @param goal the goal worldstate
         @param actions the available action pool
         @return a vector of Actions in REVERSE ORDER - use a reverse_iterator on this to get stepwise-order
         @exception std::runtime_error if no plan could be made with the available actions and states
         */
        static std::vector<PlannedAction> plan(const WorldState& start, const WorldState& goal, const std::vector<std::shared_ptr<Action>>& actions);
    };
}