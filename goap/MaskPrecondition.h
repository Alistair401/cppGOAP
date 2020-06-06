#pragma once
#include "Precondition.h"

namespace goap 
{
    class MaskPrecondition : public Precondition 
    {
    public:
        MaskPrecondition(int variable, int value);

        virtual bool IsMet(const WorldState& state) const override;

    private:
        int variable;
        int value;
    };
}

