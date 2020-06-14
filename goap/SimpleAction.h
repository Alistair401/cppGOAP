#pragma once
#include "Action.h"

namespace goap 
{
    class SimpleAction : public Action 
    {
    public:
        SimpleAction(int id, int cost);

        void AddPrecondition(Precondition* p);
        
        void AddEffect(Effect* e);

        virtual bool ResolvesAny(WorldState& ws) const override;
        virtual PlannedAction Resolve(WorldState& ws) const override;

    private:
        std::vector<std::shared_ptr<Precondition>> preconditions_;
        std::vector<std::shared_ptr<Effect>> effects_;
    };
}

