#include "OpenSet.h"
#include <algorithm>

goap::Node goap::OpenSet::Pop()
{
    Node front = this->data.front();
    this->data.erase(this->data.begin());
    return front;
}

void goap::OpenSet::Add(Node&& n)
{
    auto it = std::lower_bound(begin(this->data),
                               end(this->data),
                               n);
    this->data.emplace(it, std::move(n));
}

goap::Node* goap::OpenSet::Find(const goap::WorldState& ws)
{
    auto itr = std::find_if(begin(this->data), end(this->data), [&](const goap::Node& n) { return ws.meetsGoal(n.ws_); });
    if (itr == end(this->data))
    {
        return nullptr;
    }
    else
    {
        return &(*itr);
    }
}

size_t goap::OpenSet::Size()
{
    return this->data.size();
}

void goap::OpenSet::Update(int id)
{
    std::sort(begin(this->data), end(this->data));
}

