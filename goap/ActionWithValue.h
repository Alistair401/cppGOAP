#pragma once
#include "SimpleAction.h"
namespace goap 
{
    class ActionWithValue : public SimpleAction
    {
    public:
        ActionWithValue(int id, int cost, Value value);
        virtual PlannedAction Plan() const override;
    private:
        Value value_;
    };
}

