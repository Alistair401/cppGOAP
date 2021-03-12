#include "Planner.h"
#include "SlicedPlan.h"

std::vector<goap::EvaluatedAction> goap::Planner::Plan(
    const WorldState& start,
    const WorldState& goal,
    const std::vector<std::shared_ptr<Action>>& actions,
    void* world,
    const DistanceFunctionMap& distanceFunctions)
{
    SlicedPlan plan(start, goal, actions, world, distanceFunctions);

    plan.RunToCompletion();

    if (plan.State == SlicedPlanState::NO_PLAN)
    {
        return {};
    }

    plan.Finalize();

    return plan.Result;
}
