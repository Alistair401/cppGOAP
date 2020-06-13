#pragma once
#include "Effect.h"

namespace goap
{
    class SimpleEffect : public Effect
    {
    public:
        SimpleEffect(int variable, void* subject, bool value);
        SimpleEffect(int variable, void* subject, int value);

        virtual bool ResolvesAny(WorldState& state) override;
        virtual void Resolve(WorldState& state) override;

    private:
        int variable;
        void* subject;
        Value value;
    };
}
