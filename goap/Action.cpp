#include "Action.h"
#include "WorldState.h"

goap::Action::Action(int id, int cost)
{
    this->id_ = id;
    this->cost_ = cost;
}

bool goap::Action::operableOn(const WorldState& ws) const {
    for (const auto& precond : preconditions_) 
    {
        if (precond->IsMet(ws) == false)
        {
            return false;
        }
    }
    return true;
}

goap::WorldState goap::Action::actOn(const WorldState& ws) const {
    goap::WorldState tmp(ws);
    for (const auto& effect : effects_)
    {
        effect->Apply(tmp);
    }
    return tmp;
}

void goap::Action::AddPrecondition(Precondition* p)
{
    this->preconditions_.emplace_back(p);
}

void goap::Action::AddEffect(Effect* e)
{
    this->effects_.emplace_back(e);
}
