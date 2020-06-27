#pragma once
#include "Value.h"

namespace goap 
{
    class PlannedAction
    {
    public:
        static PlannedAction Fail();

        PlannedAction();
        PlannedAction(int id);
        PlannedAction(int id, const Value& value);
        PlannedAction(const PlannedAction& other);
        PlannedAction& operator=(const PlannedAction& other);

        int GetId() const;
        const Value& GetValue() const;
        bool Success() const;
    private:
        bool success_;
        int id_;
        Value value_;
    };
}
