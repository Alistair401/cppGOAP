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

bool goap::SimpleEffect::ResolvesAny(WorldState& state)
{
    auto found = state.vars_.find(this->variable);
    return found != state.vars_.end() && found->second == this->value;
}

void goap::SimpleEffect::Resolve(WorldState& state)
{
    state.erase(this->variable);
}
