#include "OpenSet.h"
#include <algorithm>

namespace
{
    int Parent(int index)
    {
        return (index - 1) / 2;
    }

    int LChild(int index)
    {
        return (index * 2) + 1;
    }

    int RChild(int index)
    {
        return (index * 2) + 2;
    }
}

goap::Node goap::OpenSet::Pop()
{
    Node front = this->data.front();
    this->Swap(0, this->Size() - 1);
    this->data.pop_back();
    this->DownHeapBubble(0);
    return front;
}

void goap::OpenSet::Add(Node&& n)
{
    this->data.push_back(std::move(n));
    this->UpHeapBubble(static_cast<int>(data.size()) - 1);
}

goap::Node* goap::OpenSet::Find(const goap::WorldState& ws)
{
    auto itr = std::find_if(begin(this->data), end(this->data), [&](const goap::Node& n) { return ws == n.ws_; });
    if (itr == end(this->data))
    {
        return nullptr;
    }
    else
    {
        return &(*itr);
    }
}

int goap::OpenSet::Size()
{
    return static_cast<int>(this->data.size());
}

void goap::OpenSet::Update(int id)
{
    auto itr = std::find_if(begin(this->data), end(this->data), [&](const goap::Node& n) { return n.id_ == id; });
    int index = static_cast<int>(std::distance(this->data.begin(), itr));
    this->UpHeapBubble(index);
}

void goap::OpenSet::Swap(int indexA, int indexB)
{
    std::swap(this->data[indexA], this->data[indexB]);
}

void goap::OpenSet::UpHeapBubble(int index)
{
    int parent = Parent(index);
    if (parent >= 0 && this->Score(parent) > this->Score(index))
    {
        this->Swap(parent, index);
        UpHeapBubble(parent);
    }
}

void goap::OpenSet::DownHeapBubble(int index)
{
    int smallest = index;
    int lchild = LChild(index);
    int rchild = RChild(index);

    if (lchild < data.size() && this->Score(lchild) < this->Score(smallest)) 
    {
        smallest = lchild;
    }

    if (rchild < data.size() && this->Score(rchild) < this->Score(smallest)) 
    {
        smallest = rchild;
    }

    if (smallest != index)
    {
        this->Swap(smallest, index);
        this->DownHeapBubble(smallest);
    }
}

int goap::OpenSet::Score(int index)
{
    return this->data.at(index).f();
}

