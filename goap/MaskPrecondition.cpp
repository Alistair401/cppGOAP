#include "MaskPrecondition.h"

goap::MaskPrecondition::MaskPrecondition(int variable, int value)
    : variable(variable)
    , value(value)
{
}

bool goap::MaskPrecondition::IsMet(const WorldState& state) const
{
    auto maybeVariable = state.vars_.find(this->variable);
    if (maybeVariable == state.vars_.end())
    {
        return this->value == 0;
    }
    else 
    {
        return (maybeVariable->second.AsInt() & this->value) == this->value; 
    }
}
