#include "SlicedPlan.h"
#include <limits>

goap::SlicedPlan::SlicedPlan(
    const WorldState& start,
    const WorldState& goal,
    const std::vector<std::shared_ptr<Action>>& actions,
    void* world,
    const DistanceFunctionMap& distanceFunctions)
    : start(start)
    , goal(goal)
    , actions(actions)
    , world(world)
    , distanceFunctions(distanceFunctions)
    , state(SlicedPlanState::IN_PROGRESS)
{
    Node initialNode(goal, 0, start.DistanceTo(goal, distanceFunctions), 0);

    open.Add(std::move(initialNode));
}

void goap::SlicedPlan::RunToCompletion()
{
    while (this->state == SlicedPlanState::IN_PROGRESS)
    {
        this->RunIterations(std::numeric_limits<int>::max());
    }
}

void goap::SlicedPlan::RunIterations(int iterations)
{
    for (int i = 0; i < iterations && this->open.Size() > 0; i++) 
    {
        closed.PushBack(std::move(open.Pop()));
        Node& current = closed.Back();

        if (start.Satisfies(current.ws_))
        {
            this->state = SlicedPlanState::PLAN_FOUND;
            return;
        }

         for (const auto& potential_action : this->actions)
         {
            std::vector<EvaluatedAction> planned = potential_action->Act(this->world, current.ws_);
            if (planned.empty())
            {
                continue;
            }

            for (const auto& planned_action : planned)
            {
                WorldState discovered(current.ws_);
                if (!discovered.TryResolve(planned_action.effects))
                {
                    continue;
                }

                if (!discovered.TryAdd(planned_action.preconditions))
                {
                    continue;
                };

                if (closed.Find(discovered))
                {
                    continue;
                }

                Node* p_outcome_node = this->open.Find(discovered);
                if (p_outcome_node == nullptr)
                {
                    Node found(discovered, current.g_ + planned_action.cost, this->start.DistanceTo(discovered, this->distanceFunctions), current.id_, planned_action);
                    this->open.Add(std::move(found));
                }
                else
                {
                    int tentativeCost = current.g_ + planned_action.cost;
                    if (tentativeCost < p_outcome_node->g_)
                    {
                        p_outcome_node->parent_id_ = current.id_;
                        p_outcome_node->g_ = tentativeCost;
                        p_outcome_node->h_ = this->start.DistanceTo(discovered, distanceFunctions);
                        p_outcome_node->action_ = planned_action;

                        this->open.Update(*p_outcome_node);
                    }
                }
            }
        }
    }

    if (open.Size() == 0)
    {
        this->state = SlicedPlanState::NO_PLAN;
    }
}

void goap::SlicedPlan::Finalize()
{
    const Node* foundPlanCurrent = &this->closed.Back();

    while (foundPlanCurrent->parent_id_ != 0)
    {
        this->plan.push_back(foundPlanCurrent->action_.value());
        foundPlanCurrent = &this->closed.At(this->closed.IndexOf(foundPlanCurrent->parent_id_));
    }

    this->state = SlicedPlanState::PLAN_READY;
}
