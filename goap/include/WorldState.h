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
#include "DistanceFunctionMap.h"

namespace goap
{
    using SubjectValuePair = std::pair<void*, Value>;
    
    class WorldState 
    {
    public:
        void Set(int variable, void* subject, Value value);
        const Value* Get(int variable, void* subject) const;
        const std::vector<SubjectValuePair> Get(int variable) const;

        int DistanceTo(const WorldState& other, const DistanceFunctionMap& distanceFunctions) const;
        bool Satisfies(const WorldState& other) const;
        
        bool TryResolve(const WorldState& other);
        bool TryAdd(const WorldState& other);
        bool TryApply(const WorldState& other);

        std::size_t GetHashCode() const;

        bool operator==(const WorldState& other) const;
    private:
        std::unordered_map<WorldStateKey, Value> values_;
    };
}

namespace std 
{
    template <>
    struct hash<goap::WorldState>
    {
        std::size_t operator()(const goap::WorldState& ws) const
        {
            return ws.GetHashCode();
        }
    };
}