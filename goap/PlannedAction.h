#pragma once

namespace goap 
{
    class PlannedAction
    {
    public:
        PlannedAction();
        PlannedAction(int id);
        PlannedAction(const PlannedAction& other);
        PlannedAction& operator=(const PlannedAction& other);

        int GetId();
    private:
        int id_;
    };
}
