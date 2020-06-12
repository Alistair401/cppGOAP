#include "SimplePrecondition.h"

goap::SimplePrecondition::SimplePrecondition(int variable, bool value)
    : variable(variable)
    , value(value)
{
}

goap::SimplePrecondition::SimplePrecondition(int variable, int value)
    : variable(variable)
    , value(value)
{
}

void goap::SimplePrecondition::Apply(WorldState& state) const
{
    state.set(this->variable, this->value);
}
