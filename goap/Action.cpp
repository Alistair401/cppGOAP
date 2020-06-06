#include "Action.h"
#include "WorldState.h"

goap::Action::Action(int id, int cost)
{
    this->id_ = id;
    this->cost_ = cost;
}
