#pragma once
#include "Precondition.h"
namespace goap 
{
    class SimplePrecondition : public Precondition 
    {
    public:
        SimplePrecondition(int variable, bool value);
        SimplePrecondition(int variable, int value);

        virtual void Apply(WorldState& state) const override;

    private:
        int variable;
        Value value;
    };
}

