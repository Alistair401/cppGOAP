#include "ActionWithValue.h"

goap::ActionWithValue::ActionWithValue(int id, int cost, Value value)
    : SimpleAction(id, cost)
    , value_(value)
{
}

goap::PlannedAction goap::ActionWithValue::ActOn(WorldState& ws) const
{
    SimpleAction::ActOn(ws);
    return PlannedAction(this->id_, this->value_);
}
