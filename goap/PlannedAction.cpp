#include "PlannedAction.h"

goap::PlannedAction::PlannedAction(int id)
    : id_(id)
{
}

goap::PlannedAction::PlannedAction(const PlannedAction& other)
    : id_(other.id_)
{
}

goap::PlannedAction& goap::PlannedAction::operator=(const PlannedAction& other)
{
    this->id_ = other.id_;
    return *this;
}

int goap::PlannedAction::GetId()
{
    return this->id_;
}
