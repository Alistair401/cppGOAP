#pragma once

namespace goap 
{
    class PlannedAction
    {
    public:
        PlannedAction(int id, void* target);
        PlannedAction(const PlannedAction& other);
        PlannedAction& operator=(const PlannedAction& other);

        int GetId();
        void* GetTarget();
    private:
        int id_;
        void* target_;
    };
}
