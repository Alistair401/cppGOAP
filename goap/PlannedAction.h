#pragma once
#include "Value.h"

namespace goap 
{
    class PlannedAction
    {
    public:
        PlannedAction();
        PlannedAction(int id);
        PlannedAction(int id, const Value& value);
        PlannedAction(const PlannedAction& other);
        PlannedAction& operator=(const PlannedAction& other);

        int GetId() const;
        const Value& GetValue() const;
    private:
        int id_;
        Value value_;
    };
}
