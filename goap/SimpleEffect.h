#pragma once
#include "Effect.h"

namespace goap
{
    class SimpleEffect : public Effect
    {
    public:
        SimpleEffect(int variable, bool value);
        SimpleEffect(int variable, int value);

        virtual bool ResolvesAny(WorldState& state) override;
        virtual void Resolve(WorldState& state) override;

    private:
        int variable;
        Value value;
    };
}
