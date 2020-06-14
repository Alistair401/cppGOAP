#include "SimpleAction.h"

goap::SimpleAction::SimpleAction(int id, int cost)
    : goap::Action(id, cost)
{
}

void goap::SimpleAction::AddPrecondition(Precondition* p)
{
    this->preconditions_.emplace_back(p);
}

void goap::SimpleAction::AddEffect(Effect* e)
{
    this->effects_.emplace_back(e);
}

bool goap::SimpleAction::ResolvesAny(WorldState& ws) const
{
    for (const auto& effect : this->effects_)
    {
        if (effect->ResolvesAny(ws)) 
        {
            return true;
        }
    }

    return false;
}

goap::PlannedAction goap::SimpleAction::Resolve(WorldState& ws) const
{
    for (const auto& effect : this->effects_)
    {
        effect->Resolve(ws);
    }

    for (const auto& precondition : this->preconditions_)
    {
        precondition->Apply(ws);
    }

    return PlannedAction(this->id_);
}
