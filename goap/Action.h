/**
 * @class Action
 * @brief Operates on the world state.
 *
 * @date  July 2014
 * @copyright (c) 2014 Prylis Inc.. All rights reserved.
 */

#pragma once

#include <unordered_map>
#include <memory>
#include "Effect.h"
#include "Precondition.h"

namespace goap {
    struct WorldState;

    class Action {
    private:
        int id_; 
        int cost_;

        std::vector<std::shared_ptr<Precondition>> preconditions_;
        std::vector<std::shared_ptr<Effect>> effects_;

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
        void AddEffect(Effect* e);

        int GetCost() const { return cost_; }
        int Id() const { return id_; }
    };

}