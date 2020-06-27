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
#include "DistanceFunctionMap.h"

#include <ostream>
#include <unordered_map>
#include <vector>

namespace goap {
    class Planner {
    public:
        Planner() = delete;
        Planner(const Planner& other) = delete;

        static std::vector<PlannedAction> Plan(
            const WorldState& start,
            const WorldState& goal,
            const std::vector<std::shared_ptr<Action>>& actions,
            const DistanceFunctionMap& distanceFunctions = DistanceFunctionMap());
    };
}