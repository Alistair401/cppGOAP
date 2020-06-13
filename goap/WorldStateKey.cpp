#include "WorldStateKey.h"

bool goap::WorldStateKey::operator==(const WorldStateKey& other) const
{
    return this->variable == other.variable 
        && this->subject == other.subject;
}
