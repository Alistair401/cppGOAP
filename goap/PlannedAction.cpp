#include "PlannedAction.h"

goap::PlannedAction goap::PlannedAction::Fail()
{
    PlannedAction failed;
    failed.success_ = false;
    return failed;
}

goap::PlannedAction::PlannedAction()
    : id_(-1)
    , success_(true)
{
}

goap::PlannedAction::PlannedAction(int id)
    : id_(id)
    , success_(true)
{
}

goap::PlannedAction::PlannedAction(int id, const goap::Value& value)
    : id_(id)
    , value_(value)
    , success_(true)
{
}

goap::PlannedAction::PlannedAction(const PlannedAction& other)
    : id_(other.id_)
    , value_(other.value_)
    , success_(other.success_)
{
}

goap::PlannedAction& goap::PlannedAction::operator=(const PlannedAction& other)
{
    this->id_ = other.id_;
    this->value_ = other.value_;
    return *this;
}

int goap::PlannedAction::GetId() const
{
    return this->id_;
}

const goap::Value& goap::PlannedAction::GetValue() const
{
    return this->value_;
}

bool goap::PlannedAction::Success() const
{
    return this->success_;
}
