#pragma once

#include "OpenSet.h"

namespace goap
{
    enum class SlicedPlanState 
    {
        IN_PROGRESS,
        PLAN_FOUND,
        PLAN_READY,

        NO_PLAN
    };

    class SlicedPlan
    {
    public:
        SlicedPlan(const WorldState& start,
                   const WorldState& goal,
                   const std::vector<std::shared_ptr<Action>>& actions,
                   void* world = nullptr,
                   const DistanceFunctionMap& distanceFunctions = DistanceFunctionMap());

        void RunToCompletion();
        void RunIterations(int iterations);

        void Finalize();

        const std::vector<goap::EvaluatedAction>& Result = this->plan;
        const SlicedPlanState& State = this->state;

    private:
        WorldState start;
        WorldState goal;
        std::vector<std::shared_ptr<Action>> actions;
        void* world;
        DistanceFunctionMap distanceFunctions;

        OpenSet open;
        NodeVector closed;
        SlicedPlanState state;

        std::vector<goap::EvaluatedAction> plan;
    };
}

