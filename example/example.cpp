#include <iostream>
#include "Planner.h"
#include "SimpleEffect.h"
#include "SimplePrecondition.h"
#include "SimpleAction.h"
#include "ActionWithValue.h"

enum ActionId
{
	ORDER,
	EAT,
	COOK,
};

enum VerbId
{
	HUNGRY,
	HAS,
};

enum ObjectId 
{
	RECIPE = 0x1,
	NUMBER = 0x2,
	PIZZA  = 0x4
};

int main()
{
    goap::WorldState start;
    start.Set(HUNGRY, nullptr, true);
    start.Set(HAS, nullptr, NUMBER);

    goap::WorldState goal;
    goal.Set(HUNGRY, nullptr, false);

    std::shared_ptr<goap::ActionWithValue> eat = std::make_shared<goap::ActionWithValue>(EAT, 1, goap::Value(PIZZA));
    eat->AddPrecondition(new goap::SimplePrecondition(HAS, nullptr, PIZZA));
    eat->AddEffect(new goap::SimpleEffect(HUNGRY, nullptr, false));

    std::shared_ptr<goap::ActionWithValue> order = std::make_shared<goap::ActionWithValue>(ORDER, 1, goap::Value(PIZZA));
    order->AddPrecondition(new goap::SimplePrecondition(HAS, nullptr, NUMBER));
    order->AddEffect(new goap::SimpleEffect(HAS, nullptr, PIZZA));

    std::shared_ptr<goap::ActionWithValue> cook = std::make_shared<goap::ActionWithValue>(COOK, 10, goap::Value(PIZZA));
    cook->AddPrecondition(new goap::SimplePrecondition(HAS, nullptr, RECIPE));
    cook->AddEffect(new goap::SimpleEffect(HAS, nullptr, PIZZA));

    std::vector<std::shared_ptr<goap::Action>> actions{ eat, order, cook };
    std::vector<goap::PlannedAction> plan = goap::Planner::Plan(start, goal, actions);

    std::unordered_map<int, std::string> actionLookup;
    actionLookup[ORDER] = "ORDER";
    actionLookup[EAT] = "EAT";
    actionLookup[COOK] = "COOK";

    std::unordered_map<int, std::string> objectLookup;
    objectLookup[RECIPE] = "RECIPE";
    objectLookup[NUMBER] = "NUMBER";
    objectLookup[PIZZA] = "PIZZA";

    while (plan.size() > 0) 
    {
        goap::PlannedAction a = plan.back();
        std::cout << actionLookup[a.GetId()];
        if (a.GetValue().GetType() == goap::Type::INT) 
        {
            std::cout << " " << objectLookup[a.GetValue().AsInt()];
        }
        std::cout << std::endl;
        plan.pop_back();
    }
}