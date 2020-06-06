#include "PlannedAction.h"

goap::PlannedAction::PlannedAction()
    : id_(-1)
{
}

goap::PlannedAction::PlannedAction(int id)
    : id_(id)
{
}

goap::PlannedAction::PlannedAction(int id, const goap::Value& value)
    : id_(id)
    , value_(value)
{
}

goap::PlannedAction::PlannedAction(const PlannedAction& other)
    : id_(other.id_)
    , value_(other.value_)
{
}

goap::PlannedAction& goap::PlannedAction::operator=(const PlannedAction& other)
{
    this->id_ = other.id_;
    this->value_ = other.value_;
    return *this;
}

int goap::PlannedAction::GetId()
{
    return this->id_;
}

const goap::Value& goap::PlannedAction::GetValue()
{
    return this->value_;
}
