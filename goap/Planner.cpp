#include "Planner.h"

#include <algorithm>
#include <cassert>
#include <iostream>

namespace 
{
    /**
    Moves the given Node (an rvalue reference) into the 'open' list.
    @param an rvalue reference to a Node that will be moved to the open list
    */
    void AddToOpenList(std::vector<goap::Node>& open, goap::Node&& n)
    {
        // insert maintaining sort order
        auto it = std::lower_bound(begin(open),
                                   end(open),
                                   n);
        open.emplace(it, std::move(n));
    }

    /**
    Pops the first Node from the 'open' list, moves it to the 'closed' list, and
    returns a reference to this newly-closed Node. Its behavior is undefined if
    you call on an empty list.
    @return a reference to the newly closed Node
    */
    goap::Node& PopAndClose(std::vector<goap::Node>& open, std::vector<goap::Node>& closed)
    {
        assert(!open.empty());
        closed.push_back(std::move(open.front()));
        open.erase(open.begin());

        return closed.back();
    }

    std::vector<goap::Node>::iterator Find(std::vector<goap::Node>& set, const goap::WorldState& ws)
    {
        return std::find_if(begin(set), end(set), [&](const goap::Node& n) { return n.ws_ == ws; });
    }

    bool MemberOf(std::vector<goap::Node>& set, const goap::WorldState& ws)
    {
        return Find(set, ws) != end(set); 
    }

    int CalculateHeuristic(const goap::WorldState& now, const goap::WorldState& goal)
    {
        return now.distanceTo(goal);
    }
}

std::vector<goap::PlannedAction> goap::Planner::plan(const WorldState& start, const WorldState& goal, const std::vector<std::shared_ptr<Action>>& actions) {
    if (start.meetsGoal(goal)) 
    {
        return std::vector<goap::PlannedAction>();
    }

    std::vector<Node> open;
    std::vector<Node> closed;

    Node starting_node(goal, 0, CalculateHeuristic(goal, start), 0, nullptr);

    open.push_back(std::move(starting_node));

    while (open.size() > 0) 
    {
        // Look for Node with the lowest-F-score on the open list. Switch it to closed,
        // and hang onto it -- this is our latest node.
        Node& current(PopAndClose(open, closed));

        // Is our current state the goal state? If so, we've found a path, yay.
        if (start.meetsGoal(current.ws_)) 
        {
            std::vector<PlannedAction> the_plan;
            
            do 
            {
                the_plan.push_back(current.action_->Plan());
                auto itr = std::find_if(begin(open), end(open), [&](const Node& n) { return n.id_ == current.parent_id_; });
                if (itr == end(open)) 
                {
                    itr = std::find_if(begin(closed), end(closed), [&](const Node& n) { return n.id_ == current.parent_id_; });
                }
                current = *itr;
            } while (current.parent_id_ != 0);

            return the_plan;
        }

        // Check each node REACHABLE from current -- in other words, where can we go from here?
        for (const auto& potential_action : actions) 
        {
            if (potential_action->ResolvesAny(current.ws_)) 
            {
                WorldState toResolve(current.ws_);
                potential_action->Resolve(toResolve);

                // Skip if already closed
                if (MemberOf(closed, toResolve)) 
                {
                    continue;
                }

                // Look for a Node with this WorldState on the open list.
                auto p_outcome_node = Find(open, toResolve);
                if (p_outcome_node == end(open)) 
                {
                    // Make a new node, with current as its parent, recording G & H
                    Node found(toResolve, current.g_ + potential_action->GetCost(), CalculateHeuristic(toResolve, start), current.id_, potential_action.get());
                    // Add it to the open list (maintaining sort-order therein)
                    AddToOpenList(open, std::move(found));
                }
                else 
                {
                    // check if the current G is better than the recorded G
                    if (current.g_ + potential_action->GetCost() < p_outcome_node->g_) 
                    {
                        p_outcome_node->parent_id_ = current.id_;                  // make current its parent
                        p_outcome_node->g_ = current.g_ + potential_action->GetCost(); // recalc G & H
                        p_outcome_node->h_ = CalculateHeuristic(toResolve, start);
                        p_outcome_node->action_ = potential_action.get();

                        // resort open list to account for the new F
                        // sorting likely invalidates the p_outcome_node iterator, but we don't need it anymore
                        std::sort(begin(open), end(open));
                    }
                }
            }
        }
    }

    // If there's nothing left to evaluate, then we have no possible path left
    return std::vector<goap::PlannedAction>();
}
