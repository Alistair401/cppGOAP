#include "NodeVector.h"

const goap::Node& goap::NodeVector::PushBack(Node&& n)
{
    this->data_.emplace_back(std::move(n), n.ws_.GetHashCode());
    return this->data_.back().first;
}

goap::Node* goap::NodeVector::Find(const WorldState& ws)
{
    size_t hash = ws.GetHashCode();
    auto itr = std::find_if(this->data_.begin(), this->data_.end(), [=](const NodeHashPair& p) { return p.second == hash && p.first.ws_ == ws; });
    if (itr == this->data_.end())
    {
        return nullptr;
    }
    else
    {
        return &itr->first;       
    }
}

const goap::Node& goap::NodeVector::At(int i) const
{
    return this->data_.at(i).first;
}

goap::Node& goap::NodeVector::At(int i)
{
    return this->data_.at(i).first;
}

goap:: Node& goap::NodeVector::Front()
{
    return this->data_.front().first;
}

goap::Node& goap::NodeVector::Back()
{
    return this->data_.back().first;
}

void goap::NodeVector::PopBack()
{
    this->data_.pop_back();
}

std::size_t goap::NodeVector::Size() const
{
    return this->data_.size();
}

std::size_t goap::NodeVector::IndexOf(int id) const
{
    auto itr = std::find_if(this->data_.begin(), this->data_.end(), [=](const NodeHashPair& p) { return p.first.id_ == id; });
    if (itr == this->data_.end())
    {
        return this->data_.size();
    }
    else
    {
        return static_cast<size_t>(std::distance(this->data_.begin(), itr));
    }
}
