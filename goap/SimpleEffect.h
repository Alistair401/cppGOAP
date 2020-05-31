#pragma once
#include "Effect.h"

namespace goap
{
    class SimpleEffect : public Effect {
    public:
        SimpleEffect(int variable, bool value);
        SimpleEffect(int variable, int value);

        virtual void Apply(WorldState& state) override;

    private:
        int variable;
        Value value;
    };
}
