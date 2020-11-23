#include "NodeVector.h"
#include <algorithm>

const goap::Node& goap::NodeVector::PushBack(Node&& n)
{
    size_t hash = n.ws_.GetHashCode();
    this->data_.emplace_back(std::move(n), hash);
    this->hashIndices_.emplace(hash, this->data_.size() - 1);
    return this->data_.back().first;
}

goap::Node* goap::NodeVector::Find(const WorldState& ws)
{
    size_t hash = ws.GetHashCode();
    auto found = this->hashIndices_.equal_range(hash);
    auto itr = std::find_if(found.first, found.second, [&](const std::pair<const size_t, size_t>& p) { return this->data_[p.second].first.ws_ == ws; });
    if (itr == found.second)
    {
        return nullptr;
    }
    else
    {
        return &this->data_[itr->second].first;       
    }
}

const goap::Node& goap::NodeVector::At(std::size_t i) const
{
    return this->data_.at(i).first;
}

goap::Node& goap::NodeVector::At(std::size_t i)
{
    return this->data_.at(i).first;
}

goap::Node& goap::NodeVector::Front()
{
    return this->data_.front().first;
}

goap::Node& goap::NodeVector::Back()
{
    return this->data_.back().first;
}

void goap::NodeVector::PopBack()
{
    const NodeHashPair& back = this->data_.back();
    size_t index = this->data_.size() - 1;
    size_t hash = back.second;
    this->EraseHashIndexPair(hash, index);
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

std::size_t goap::NodeVector::IndexOf(const WorldState& ws) const
{
    size_t hash = ws.GetHashCode();
    auto found = this->hashIndices_.equal_range(hash);
    auto itr = std::find_if(found.first, found.second, [&](const std::pair<const size_t, size_t>& p) { return this->data_[p.second].first.ws_ == ws; });
    if (itr == found.second)
    {
        return this->data_.size();
    }
    else
    {
        return itr->second;
    }
}

void goap::NodeVector::Swap(int ia, int ib)
{
    size_t hashA = this->data_[ia].second;
    size_t hashB = this->data_[ib].second;

    this->EraseHashIndexPair(hashA, ia);
    this->EraseHashIndexPair(hashB, ib);

    std::swap(this->data_.at(ia), this->data_.at(ib));

    this->hashIndices_.emplace(hashA, ib);
    this->hashIndices_.emplace(hashB, ia);
}

void goap::NodeVector::EraseHashIndexPair(size_t hash, size_t index)
{
    auto found = this->hashIndices_.equal_range(hash);
    auto itr = std::find_if(found.first, found.second, [&](const std::pair<const size_t, size_t>& p) { return p.second == index; });
    this->hashIndices_.erase(itr);
}
