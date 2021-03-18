#include "SimpleAction.h"

goap::SimpleAction::SimpleAction(int id, int cost)
    : cost(cost), goap::Action(id)
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

std::vector<goap::EvaluatedAction> goap::SimpleAction::Act(void* world, const WorldState& state)
{
    goap::EvaluatedAction evaluated;

    evaluated.id = this->id_;
    evaluated.cost = this->cost;

    for (const auto& effect : this->effects_)
    {
        effect->Apply(evaluated.effects);
    }

    for (const auto& precondition : this->preconditions_)
    {
        precondition->Apply(evaluated.preconditions);
    }

    return { evaluated };
}
