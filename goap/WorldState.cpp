#include "WorldState.h"

void goap::WorldState::Set(int variable, void* subject, Value value)
{
    this->values_[{ variable, subject }] = value;
}

const goap::Value* goap::WorldState::Get(int variable, void* subject) const
{
    auto found = this->values_.find({ variable, subject });
    return found == this->values_.end() ? nullptr : &found->second;
}

int goap::WorldState::DistanceTo(const WorldState& other, const DistanceFunctionMap& distanceFunctions) const
{
    int result = 0;

    for (const auto& kv : other.values_)
    {
        auto itr = this->values_.find(kv.first);
        const DistanceFunction& distanceFunction = distanceFunctions.Get(kv.first.variable);
        const Value* currentValue = nullptr;
        if (itr != this->values_.end())
        {
            currentValue = &itr->second;
        }
        result += distanceFunction(kv.second, currentValue);
    }

    return result;
}

bool goap::WorldState::Satisfies(const WorldState& other) const
{
    for (const auto& kv : other.values_)
    {
        auto itr = this->values_.find(kv.first);
        if (itr == this->values_.end() || itr->second != kv.second)
        {
            return false;
        }
    }

    return true;
}

bool goap::WorldState::TryResolve(const WorldState& other)
{
    int resolved = 0;
    for (const auto& kv : other.values_)
    {
        auto itr = this->values_.find(kv.first);
        if (itr != this->values_.end())
        {
            if (itr->second == kv.second)
            {
                this->values_.erase(kv.first);
                resolved++;
            } 
            else
            {
                return false;
            }
        }
    }
    return resolved != 0;
}

bool goap::WorldState::TryAdd(const WorldState& other)
{
    for (const auto& kv : other.values_)
    {
        auto itr = this->values_.find(kv.first);
        
        if (itr != this->values_.end() && itr->second != kv.second)
        {
            return false;
        }

        this->values_[kv.first] = kv.second;
    }

    return true;
}

bool goap::WorldState::TryApply(const WorldState& other)
{
    for (const auto& kv : other.values_)
    {
        auto itr = this->values_.find(kv.first);

        if (itr != this->values_.end() && itr->second == kv.second)
        {
            return false;
        }

        this->values_[kv.first] = kv.second;
    }

    return true;
}

std::size_t goap::WorldState::GetHashCode() const
{
    std::size_t sum = 0;
    
    for (const auto& kv : this->values_)
    {
        std::size_t hash = 0;
        goap::hash_combine(hash, kv.first, kv.second);
        sum += hash;
    }

    return sum;
}

bool goap::WorldState::operator==(const WorldState& other) const
{
    return this->values_ == other.values_;
}
