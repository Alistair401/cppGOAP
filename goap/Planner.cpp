#include "Planner.h"

#include <algorithm>

#include "OpenSet.h"

std::vector<goap::EvaluatedAction> goap::Planner::Plan(
    const WorldState& start,
    const WorldState& goal,
    const std::vector<std::shared_ptr<Action>>& actions,
    const DistanceFunctionMap& distanceFunctions)
{
    OpenSet open;
    NodeVector closed;

    Node initialNode(goal, 0, start.DistanceTo(goal, distanceFunctions), 0);

    open.Add(std::move(initialNode));

    while (open.Size() > 0) 
    {
        closed.PushBack(std::move(open.Pop()));
        Node& current = closed.Back();

        if (start.Satisfies(current.ws_)) 
        {
            std::vector<EvaluatedAction> the_plan;
            
            do 
            {
                the_plan.push_back(current.action_.value());
                current = closed.At(closed.IndexOf(current.parent_id_));
            } while (current.parent_id_ != 0);

            return the_plan;
        }

        for (const auto& potential_action : actions) 
        {
            std::vector<EvaluatedAction> planned = potential_action->Act(current.ws_);
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

                Node* p_outcome_node = open.Find(discovered);
                if (p_outcome_node == nullptr)
                {
                    Node found(discovered, current.g_ + potential_action->GetCost(), start.DistanceTo(discovered, distanceFunctions), current.id_, planned_action);
                    open.Add(std::move(found));
                }
                else 
                {
                    int tentativeCost = current.g_ + potential_action->GetCost();
                    if (tentativeCost < p_outcome_node->g_)
                    {
                        p_outcome_node->parent_id_ = current.id_;
                        p_outcome_node->g_ = tentativeCost;
                        p_outcome_node->h_ = start.DistanceTo(discovered, distanceFunctions);
                        p_outcome_node->action_ = planned_action;

                        open.Update(*p_outcome_node);
                    }
                }
            }
        }
    }

    // If there's nothing left to evaluate, then we have no possible path left
    return {};
}
