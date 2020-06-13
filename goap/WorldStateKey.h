#pragma once
#include <functional>

namespace goap
{
    struct WorldStateKey
    {
        int variable;
        void* subject;

        bool operator==(const WorldStateKey& other) const;
    };

    // https://stackoverflow.com/questions/2590677/how-do-i-combine-hash-values-in-c0x
    template <typename T, typename... Rest>
    void hash_combine(std::size_t& seed, const T& v, const Rest&... rest)
    {
        seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        (hash_combine(seed, rest), ...);
    }
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
