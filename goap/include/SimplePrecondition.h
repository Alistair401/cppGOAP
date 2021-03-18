#pragma once
#include "Precondition.h"
namespace goap 
{
    class SimplePrecondition : public Precondition 
    {
    public:
        SimplePrecondition(int variable, void* subject, Value value);

        virtual void Apply(WorldState& state) const override;

    private:
        int variable;
        void* subject;
        Value value;
    };
}

