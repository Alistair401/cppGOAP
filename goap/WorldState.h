/**
 * @class WorldState
 * @brief A way of describing the "world" at any point in time.
 *
 * @date  July 2014
 * @copyright (c) 2014 Prylis Inc.. All rights reserved.
 */

#pragma once

#include "Value.h"
#include "WorldStateKey.h"
#include <map>

namespace goap
{
    struct WorldState 
    {
        float priority_; // useful if this is a goal state, to distinguish from other possible goals
        std::map<WorldStateKey, Value> vars_;

        WorldState();
        WorldState(const WorldState& other);
        WorldState& operator=(const WorldState& other);

        void Set(int variable, void* subject, const Value& value);

        void Erase(int variable, void* subject);

        /**
         Useful if this state is a goal state. It asks, does state 'other'
         meet the requirements of this goal? Takes into account not only this goal's
         state variables, but which variables matter to this goal state.
         @param other the state you are testing as having met this goal state
         @return true if it meets this goal state, false otherwise
         */
        bool meetsGoal(const WorldState& goal_state) const;

        /**
         Given the other state -- and what 'matters' to the other state -- how many
         of our state variables differ from the other?
         @param other the goal state to compare against
         @return the number of state-var differences between us and them
         */
        int distanceTo(const WorldState& goal_state) const;

        /**
         Equality operator
         @param other the other worldstate to compare to
         @return true if they are equal, false if not
         */
        bool operator==(const WorldState& other) const;
    };
}