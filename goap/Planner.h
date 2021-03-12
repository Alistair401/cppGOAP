/**
 * @class Planner
 * @brief Implements an A* algorithm for searching the action space
 *
 * @date July 2014
 * @copyright (c) 2014 Prylis Inc. All rights reserved.
 */

#pragma once

#include "Action.h"
#include "DistanceFunctionMap.h"

namespace goap {
    class Planner {
    public:
        Planner() = delete;
        Planner(const Planner& other) = delete;

        static std::vector<EvaluatedAction> Plan(
            const WorldState& start,
            const WorldState& goal,
            const std::vector<std::shared_ptr<Action>>& actions,
            void* world = nullptr,
            const DistanceFunctionMap& distanceFunctions = DistanceFunctionMap());
    };
}