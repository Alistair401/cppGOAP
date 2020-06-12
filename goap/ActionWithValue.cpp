#include "ActionWithValue.h"

goap::ActionWithValue::ActionWithValue(int id, int cost, Value value)
    : SimpleAction(id, cost)
    , value_(value)
{
}

goap::PlannedAction goap::ActionWithValue::Plan() const
{
    return PlannedAction(this->id_, this->value_);
}
