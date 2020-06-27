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

goap::PlannedAction goap::SimpleAction::Act(const WorldState& state, WorldState& preconditions, WorldState& effects)
{
    for (const auto& effect : this->effects_) {
        effect->Apply(effects);
    }

    for (const auto& precondition : this->preconditions_) {
        precondition->Apply(preconditions);
    }

    return PlannedAction(this->id_);
}
