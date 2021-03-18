#include "SimpleEffect.h"

goap::SimpleEffect::SimpleEffect(int variable, void* subject, Value value)
    : variable(variable)
    , subject(subject)
    , value(value)
{
}

void goap::SimpleEffect::Apply(WorldState& state)
{
    state.Set(this->variable, this->subject, this->value);
}
