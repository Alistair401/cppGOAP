#include "BitwiseOrEffect.h"

goap::BitwiseOrEffect::BitwiseOrEffect(int variable, int value)
    : variable(variable)
    , value(value)
{
}

void goap::BitwiseOrEffect::Apply(WorldState& state)
{
    auto found = state.vars_.find(this->variable);
    if (found == state.vars_.end()) 
    {
        state.set(this->variable, this->value);
    }
    else
    {
        state.set(this->variable, this->value | found->second);
    }
}
