#pragma once
#include "Effect.h"

namespace goap
{
    class SimpleEffect : public Effect
    {
    public:
        SimpleEffect(int variable, void* subject, Value value);
        virtual void Apply(WorldState& state) override;
    private:
        int variable;
        void* subject;
        Value value;
    };
}
