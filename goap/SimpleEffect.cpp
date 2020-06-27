#include "SimpleEffect.h"

goap::SimpleEffect::SimpleEffect(int variable, void* subject, bool value)
    : variable(variable)
    , subject(subject)
    , value(value)
{
}

goap::SimpleEffect::SimpleEffect(int variable, void* subject, int value)
    : variable(variable)
    , subject(subject)
    , value(value)
{
}

void goap::SimpleEffect::Apply(WorldState& state)
{
    state.Set(this->variable, this->subject, this->value);
}
