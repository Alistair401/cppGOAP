#include "SimpleEffect.h"

goap::SimpleEffect::SimpleEffect(int variable, bool value)
    : variable(variable)
    , value(value)
{
}

goap::SimpleEffect::SimpleEffect(int variable, int value)
    : variable(variable)
    , value(value)
{
}

void goap::SimpleEffect::Apply(WorldState& state)
{
    state.set(this->variable, this->value);
}
