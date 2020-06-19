#pragma once
#include "Node.h"

namespace goap
{
    class OpenSet
    {
        public:

            Node Pop();
            void Add(Node&& n);
            Node* Find(const goap::WorldState& ws);
            size_t Size();
            void Update(int id);
        private:
            std::vector<Node> data;
    };
}

