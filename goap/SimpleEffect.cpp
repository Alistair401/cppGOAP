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

bool goap::SimpleEffect::ResolvesAny(WorldState& state)
{
    auto found = state.vars_.find({ this->variable, this->subject });
    return found != state.vars_.end() && found->second == this->value;
}

void goap::SimpleEffect::Resolve(WorldState& state)
{
    state.Erase(this->variable, this->subject);
}
