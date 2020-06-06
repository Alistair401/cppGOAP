#pragma once
#include "Action.h"

namespace goap 
{
    class SimpleAction : public Action 
    {
    public:
        SimpleAction(int id, int cost);

        virtual bool OperableOn(const goap::WorldState& ws) const override;

        virtual PlannedAction ActOn(WorldState& ws) const override;
        
        void AddPrecondition(Precondition* p);
        
        void AddEffect(Effect* e);

    private:

        std::vector<std::shared_ptr<Precondition>> preconditions_;
        std::vector<std::shared_ptr<Effect>> effects_;
    };
}

