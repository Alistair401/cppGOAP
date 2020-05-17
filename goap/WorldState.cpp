#include "WorldState.h"

goap::WorldState::WorldState(const WorldState& other)
    : priority_(other.priority_), name_(other.name_) 
{
    this->vars_ = other.vars_;
}

goap::WorldState::WorldState(const std::string name) : priority_(0), name_(name) {
}

goap::WorldState& goap::WorldState::operator=(const WorldState& other) {
    this->name_ = other.name_;
    this->priority_ = other.priority_;
    this->vars_ = other.vars_;
    return *this;
}

void goap::WorldState::setVariable(const int var_id, const bool value) {
    vars_[var_id] = value;
}

bool goap::WorldState::getVariable(const int var_id) const {
    return vars_.at(var_id);
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

        if (maybeVariable->second != kvp.second) 
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
        if (itr == end(vars_) || itr->second != kv.second) {
            ++result;
        }
    }

    return result;
}