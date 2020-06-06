#include "SimpleAction.h"

goap::SimpleAction::SimpleAction(int id, int cost)
    : goap::Action(id, cost)
{
}

bool goap::SimpleAction::OperableOn(const goap::WorldState& ws) const
{
    for (const auto& precond : preconditions_) 
    {
        if (precond->IsMet(ws) == false) 
        {
            return false;
        }
    }
    return true;
}

goap::PlannedAction goap::SimpleAction::ActOn(WorldState& ws) const
{
    for (const auto& effect : effects_) 
    {
        effect->Apply(ws);
    }

    return PlannedAction(this->id_);
}

void goap::SimpleAction::AddPrecondition(Precondition* p)
{
    this->preconditions_.emplace_back(p);
}

void goap::SimpleAction::AddEffect(Effect* e)
{
    this->effects_.emplace_back(e);
}
