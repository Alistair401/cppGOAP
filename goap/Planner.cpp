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

    int CalculateHeuristic(const goap::WorldState& now, const goap::WorldState& goal, const goap::DistanceFunctionMap& distanceFunctionMap)
    {
        return now.DistanceTo(goal, distanceFunctionMap);
    }
}

std::vector<goap::PlannedAction> goap::Planner::Plan(
    const WorldState& start,
    const WorldState& goal,
    const std::vector<std::shared_ptr<Action>>& actions,
    const DistanceFunctionMap& distanceFunctions)
{
    if (start.meetsGoal(goal)) 
    {
        return std::vector<goap::PlannedAction>();
    }

    WorldState unsatisfied(goal);
    start.Satisfy(unsatisfied);

    OpenSet open;
    std::vector<Node> closed;

    Node starting_node(unsatisfied, 0, CalculateHeuristic(start, unsatisfied, distanceFunctions), 0);

    open.Add(std::move(starting_node));

    while (open.Size() > 0) 
    {
        // Look for Node with the lowest-F-score on the open list. Switch it to closed,
        // and hang onto it -- this is our latest node.
        closed.push_back(std::move(open.Pop()));
        Node& current = closed.back();

        if (start.meetsGoal(current.ws_)) 
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
            if (potential_action->ResolvesAny(start, current.ws_)) 
            {
                WorldState toResolve(current.ws_);
                goap::PlannedAction planned = potential_action->Resolve(start, toResolve);
                start.Satisfy(toResolve);

                // Skip if already closed
                if (MemberOf(closed, toResolve)) 
                {
                    continue;
                }

                // Look for a Node with this WorldState on the open list.
                Node* p_outcome_node = open.Find(toResolve);
                if (p_outcome_node == nullptr) 
                {
                    // Make a new node, with current as its parent, recording G & H
                    Node found(toResolve, current.g_ + potential_action->GetCost(), CalculateHeuristic(start, toResolve, distanceFunctions), current.id_, planned);
                    // Add it to the open list (maintaining sort-order therein)
                    open.Add(std::move(found));
                }
                else 
                {
                    // check if the current G is better than the recorded G
                    int tentativeCost = current.g_ + potential_action->GetCost();
                    if (tentativeCost < p_outcome_node->g_) 
                    {
                        p_outcome_node->parent_id_ = current.id_;
                        p_outcome_node->g_ = tentativeCost;
                        p_outcome_node->h_ = CalculateHeuristic(start, toResolve, distanceFunctions);
                        p_outcome_node->action_ = planned;

                        open.Update(p_outcome_node->id_);
                    }
                }
            }
        }
    }

    // If there's nothing left to evaluate, then we have no possible path left
    return std::vector<goap::PlannedAction>();
}
