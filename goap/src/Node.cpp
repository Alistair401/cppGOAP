#include "Node.h"
int goap::Node::last_id_ = 0;

goap::Node::Node(const WorldState state, int g, int h, int parent_id)
    : ws_(state)
    , g_(g)
    , h_(h)
    , parent_id_(parent_id)
    , action_({})
{
    id_ = ++last_id_;
}

goap::Node::Node(const WorldState state, int g, int h, int parent_id, const EvaluatedAction& action)
    : ws_(state)
    , g_(g)
    , h_(h)
    , parent_id_(parent_id)
    , action_(action)
{
    id_ = ++last_id_;
}

int goap::Node::f() const
{
    return g_ + h_;
}
