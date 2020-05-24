#include "SimplePrecondition.h"

goap::SimplePrecondition::SimplePrecondition(int variable, bool value)
    : variable(variable)
    , value(value)
{
}

bool goap::SimplePrecondition::IsMet(const WorldState& state) const
{
    auto maybeVariable = state.vars_.find(this->variable);
    return maybeVariable != state.vars_.end() && maybeVariable->second == this->value;
}
