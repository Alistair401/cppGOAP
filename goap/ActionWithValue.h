#pragma once
#include "SimpleAction.h"
namespace goap 
{
    class ActionWithValue : public SimpleAction
    {
    public:
        ActionWithValue(int id, int cost, Value value);
        virtual PlannedAction Act(const WorldState& state, WorldState& preconditions, WorldState& effects) override;
    private:
        Value value_;
    };
}

