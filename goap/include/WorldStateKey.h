#pragma once
#include <functional>
#include "Hash.h"

namespace goap
{
    struct WorldStateKey
    {
        int variable;
        void* subject;

        bool operator==(const WorldStateKey& other) const;
    };
}

namespace std {

    template <>
    struct hash<goap::WorldStateKey> {
        std::size_t operator()(const goap::WorldStateKey& k) const
        {
            size_t h = 0;
            goap::hash_combine(h, k.subject, k.variable);
            return h;
        }
    };

    template <>
    struct less<goap::WorldStateKey> 
    {
        bool operator()(const goap::WorldStateKey& lhs, const goap::WorldStateKey& rhs) const
        {
            return std::tie(lhs.variable, lhs.subject) < std::tie(rhs.variable, rhs.subject);
        }
    };
}
