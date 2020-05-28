#include "PlannedAction.h"

goap::PlannedAction::PlannedAction(int id, void* target)
    : id_(id)
    , target_(target)
{
}

goap::PlannedAction::PlannedAction(const PlannedAction& other)
    : id_(other.id_)
    , target_(other.target_)
{
}

goap::PlannedAction& goap::PlannedAction::operator=(const PlannedAction& other)
{
    this->id_ = other.id_;
    this->target_ = other.target_;
    return *this;
}

int goap::PlannedAction::GetId()
{
    return this->id_;
}

void* goap::PlannedAction::GetTarget()
{
    return this->target_;
}
