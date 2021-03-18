#pragma once
#include <functional>
#include "Value.h"

namespace goap
{
    using DistanceFunction = std::function<int(const Value&, const Value*)>;

    class DistanceFunctionMap
    {
    public:
        const DistanceFunction& Get(int variable) const;

        void Set(int variable, DistanceFunction f);

    private:
        DistanceFunction defaultDistance = [](const Value& a, const Value* b)
        {
            if (b == nullptr)
            {
                return 1;
            }
            else
            {
                return a == (*b) ? 0 : 1;
            }
        };

        std::unordered_map<int, DistanceFunction> functions;
    };
}
