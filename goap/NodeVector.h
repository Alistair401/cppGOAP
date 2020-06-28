#pragma once

#include <vector>
#include <unordered_set>
#include "Node.h"

namespace goap
{
    using NodeHashPair = std::pair<Node, std::size_t>;

    class NodeVector
    {
    public:
        const Node& PushBack(Node&& n);
        Node* Find(const WorldState& ws);
        const Node& At(int i) const;
        Node& At(int i);
        Node& Front();
        Node& Back();
        void PopBack();
        std::size_t Size() const;
        std::size_t IndexOf(int id) const;
        std::size_t IndexOf(const WorldState& ws) const;
        void Swap(int ia, int ib);
    private:

        void EraseHashIndexPair(size_t hash, size_t index);

        std::multimap<size_t, size_t> hashIndices_;
        std::vector<NodeHashPair> data_;
    };
}

