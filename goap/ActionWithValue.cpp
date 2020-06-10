#include "ActionWithValue.h"

goap::ActionWithValue::ActionWithValue(int id, int cost, Value value)
    : SimpleAction(id, cost)
    , value_(value)
{
}

void goap::ActionWithValue::ActOn(WorldState& ws) const
{
    SimpleAction::ActOn(ws);
}

goap::PlannedAction goap::ActionWithValue::Plan() const
{
    return PlannedAction(this->id_, this->value_);
}
