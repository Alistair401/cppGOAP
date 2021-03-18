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
    Node front = this->data.Front();
    this->Swap(0, this->Size() - 1);
    this->data.PopBack();
    this->DownHeapBubble(0);
    return front;
}

void goap::OpenSet::Add(Node&& n)
{
    this->data.PushBack(std::move(n));
    this->UpHeapBubble(static_cast<int>(data.Size()) - 1);
}

goap::Node* goap::OpenSet::Find(const goap::WorldState& ws)
{
    return this->data.Find(ws);
}

int goap::OpenSet::Size()
{
    return static_cast<int>(this->data.Size());
}

void goap::OpenSet::Update(const goap::Node& n)
{
    int index = static_cast<int>(this->data.IndexOf(n.ws_));
    this->UpHeapBubble(index);
}

void goap::OpenSet::Swap(int indexA, int indexB)
{
    if (indexA != indexB)
    {
        this->data.Swap(indexA, indexB);
    }
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

    if (lchild < data.Size() && this->Score(lchild) < this->Score(smallest)) 
    {
        smallest = lchild;
    }

    if (rchild < data.Size() && this->Score(rchild) < this->Score(smallest)) 
    {
        smallest = rchild;
    }

    if (smallest != index)
    {
        this->Swap(smallest, index);
        this->DownHeapBubble(smallest);
    }
}

int goap::OpenSet::Score(int index) const
{
    return this->data.At(index).f();
}

