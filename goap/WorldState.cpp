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

void goap::WorldState::set(int var_id, const Value& value)
{
    this->vars_[var_id] = value;
}

void goap::WorldState::setBool(int var_id, bool value)
{
    this->vars_.emplace(var_id, value);
}

void goap::WorldState::setFloat(int var_id, float value)
{
    this->vars_.emplace(var_id, value);
}

void goap::WorldState::setInt(int var_id, int value)
{
    this->vars_.emplace(var_id, value);
}

void goap::WorldState::setVector(int var_id, const std::vector<Value>& values)
{
    this->vars_.emplace(var_id, values);
}

void goap::WorldState::setVector(int var_id, std::vector<Value>&& values)
{
    this->vars_.emplace(var_id, std::move(values));
}

void goap::WorldState::erase(int var_id)
{
    this->vars_.erase(var_id);
}

bool goap::WorldState::operator==(const WorldState& other) const {
    return (vars_ == other.vars_);
}

bool goap::WorldState::meetsGoal(const WorldState& goal_state) const {
    for (const auto& kvp : goal_state.vars_) 
    {
        auto maybeVariable = this->vars_.find(kvp.first);

        if (maybeVariable == this->vars_.end()) 
        {
            return false;
        }

        if ((maybeVariable->second == kvp.second) == false) 
        {
            return false;
        }
    }

    return true;
}

int goap::WorldState::distanceTo(const WorldState& goal_state) const {
    int result = 0;

    for (const auto& kv : goal_state.vars_) {
        auto itr = vars_.find(kv.first);
        if (itr == end(vars_) || (itr->second == kv.second) == false) {
            ++result;
        }
    }

    return result;
}