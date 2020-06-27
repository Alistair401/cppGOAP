#include "ActionWithValue.h"

goap::ActionWithValue::ActionWithValue(int id, int cost, Value value)
    : SimpleAction(id, cost)
    , value_(value)
{
}

goap::PlannedAction goap::ActionWithValue::Act(const WorldState& state, WorldState& preconditions, WorldState& effects)
{
    SimpleAction::Act(state, preconditions, effects);
    return PlannedAction(this->id_, this->value_);
}
