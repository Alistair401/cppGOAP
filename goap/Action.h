/**
 * @class Action
 * @brief Operates on the world state.
 *
 * @date  July 2014
 * @copyright (c) 2014 Prylis Inc.. All rights reserved.
 */

#pragma once

#include <unordered_map>
#include "Precondition.h"

// To support Google Test for private members
#ifndef TEST_FRIENDS
#define TEST_FRIENDS
#endif

namespace goap {
    struct WorldState;

    class Action {
    private:
        int id_; 
        int cost_;         // The numeric cost of this action

        std::vector<std::shared_ptr<Precondition>> preconditions_;

        // Effects are things that happen when this action takes place.
        std::unordered_map<int, bool> effects_;

    public:
        Action(int id, int cost);

        /**
         Is this action eligible to operate on the given worldstate?
         @param ws the worldstate in question
         @return true if this worldstate meets the preconditions
         */
        bool operableOn(const goap::WorldState& ws) const;

        /**
         Act on the given worldstate. Will not check for "eligiblity" and will happily
         act on whatever worldstate you provide it.
         @param the worldstate to act on
         @return a copy worldstate, with effects applied
         */
        WorldState actOn(const WorldState& ws) const;

        void AddPrecondition(Precondition* p);

        /**
         Set the given effect of this action, in terms of variable and new value.
         @param key the name of the effect
         @param value the value that will result
         */
        void setEffect(const int key, const bool value) {
            effects_[key] = value;
        }

        int GetCost() const { return cost_; }

        int Id() const { return id_; }

        TEST_FRIENDS;
    };

}