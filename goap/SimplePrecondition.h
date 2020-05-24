#pragma once
#include "Precondition.h"
namespace goap 
{
    class SimplePrecondition : public Precondition 
    {
    public:
        SimplePrecondition(int variable, bool value);

        virtual bool IsMet(const WorldState& state) const override;

    private:
        int variable;
        bool value;
    };
}

