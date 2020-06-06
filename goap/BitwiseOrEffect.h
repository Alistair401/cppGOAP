#pragma once
#include "Effect.h"

namespace goap 
{
    class BitwiseOrEffect : public Effect 
    {
    public:
        BitwiseOrEffect(int variable, int value);

        virtual void Apply(WorldState& state) override;

    private:
        int variable;
        Value value;
    };
}

