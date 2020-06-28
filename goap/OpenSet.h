#pragma once
#include "NodeVector.h"

namespace goap
{
    class OpenSet
    {
        public:
            Node Pop();
            void Add(Node&& n);
            Node* Find(const goap::WorldState& ws);
            int Size();
            void Update(int id);
        private:
            void Swap(int indexA, int indexB);
            void UpHeapBubble(int index);
            void DownHeapBubble(int index);
            int Score(int index) const;
            NodeVector data;
    };
}

