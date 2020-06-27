#include "Planner.h"

#include <algorithm>
#include <cassert>

#include "OpenSet.h"

namespace 
{
    std::vector<goap::Node>::iterator Find(std::vector<goap::Node>& set, const goap::WorldState& ws)
    {
        return std::find_if(begin(set), end(set), [&](const goap::Node& n) { return n.ws_ == ws; });
    }

    bool MemberOf(std::vector<goap::Node>& set, const goap::WorldState& ws)
    {
        return Find(set, ws) != end(set); 
    }
}

std::vector<goap::PlannedAction> goap::Planner::Plan(
    const WorldState& start,
    const WorldState& goal,
    const std::vector<std::shared_ptr<Action>>& actions,
    const DistanceFunctionMap& distanceFunctions)
{
    OpenSet open;
    std::vector<Node> closed;

    Node initialNode(goal, 0, start.DistanceTo(goal), 0);

    open.Add(std::move(initialNode));

    while (open.Size() > 0) 
    {
        closed.push_back(std::move(open.Pop()));
        Node& current = closed.back();

        if (start.Satisfies(current.ws_)) 
        {
            std::vector<PlannedAction> the_plan;
            
            do 
            {
                the_plan.push_back(current.action_.value());
                auto itr = std::find_if(begin(closed), end(closed), [&](const Node& n) { return n.id_ == current.parent_id_; });
                current = *itr;
            } while (current.parent_id_ != 0);

            return the_plan;
        }

        for (const auto& potential_action : actions) 
        {
            WorldState preconditions;
            WorldState effects;
            PlannedAction planned = potential_action->Act(current.ws_, preconditions, effects);
            if (planned.Success() == false)
            {
                continue;
            }

            WorldState discovered(current.ws_);
            if (!discovered.TryResolve(effects))
            {
                continue;
            }
            
            if (!discovered.TryAdd(preconditions))
            {
                continue;
            };

            if (MemberOf(closed, discovered)) 
            {
                continue;
            }

            Node* p_outcome_node = open.Find(discovered);
            if (p_outcome_node == nullptr) 
            {
                Node found(discovered, current.g_ + potential_action->GetCost(), start.DistanceTo(discovered), current.id_, planned);
                open.Add(std::move(found));
            }
            else
            {
                int tentativeCost = current.g_ + potential_action->GetCost();
                if (tentativeCost < p_outcome_node->g_) 
                {
                    p_outcome_node->parent_id_ = current.id_;
                    p_outcome_node->g_ = tentativeCost;
                    p_outcome_node->h_ = start.DistanceTo(discovered);
                    p_outcome_node->action_ = planned;

                    open.Update(p_outcome_node->id_);
                }
            }
        }
    }

    // If there's nothing left to evaluate, then we have no possible path left
    return std::vector<goap::PlannedAction>();
}
