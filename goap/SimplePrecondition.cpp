#include "SimplePrecondition.h"

goap::SimplePrecondition::SimplePrecondition(int variable, void* subject, bool value)
    : variable(variable)
    , subject(subject)
    , value(value)
{
}

goap::SimplePrecondition::SimplePrecondition(int variable, void* subject, int value)
    : variable(variable)
    , subject(subject)
    , value(value)
{
}

void goap::SimplePrecondition::Apply(WorldState& state) const
{
    state.Set(this->variable, this->subject, this->value);
}
