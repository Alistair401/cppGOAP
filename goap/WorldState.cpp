#include "WorldState.h"

goap::WorldState::WorldState()
    : priority_(0)
{
}

goap::WorldState::WorldState(const WorldState& other)
    : priority_(other.priority_)
{
    this->vars_ = other.vars_;
}

goap::WorldState& goap::WorldState::operator=(const WorldState& other) {
    this->priority_ = other.priority_;
    this->vars_ = other.vars_;
    return *this;
}

void goap::WorldState::Set(int variable, void* subject, const Value& value)
{
    this->vars_[{ variable, subject }] = value;
}

void goap::WorldState::Erase(int variable, void* subject)
{
    this->vars_.erase({ variable, subject });
}

bool goap::WorldState::operator==(const WorldState& other) const {
    return (vars_ == other.vars_);
}

bool goap::WorldState::meetsGoal(const WorldState& goal_state) const {
    if (goal_state.vars_.size() > this->vars_.size())
    {
        return false;
    }

    for (const auto& kvp : goal_state.vars_) 
    {
        auto maybeVariable = this->vars_.find(kvp.first);

        if (maybeVariable == this->vars_.end()) 
        {
            return false;
        }

        if (maybeVariable->second != kvp.second) 
        {
            return false;
        }
    }

    return true;
}

int goap::WorldState::DistanceTo(const WorldState& goal_state, const DistanceFunctionMap& distanceFunctions) const
{
    int result = 0;

    for (const auto& kv : goal_state.vars_) 
    {
        auto itr = this->vars_.find(kv.first);
        const Value* value = nullptr;
        if (itr != end(vars_))
        {
            value = &itr->second;
        }

        result += distanceFunctions.Get(kv.first.variable)(kv.second, value);
    }

    return result;
}