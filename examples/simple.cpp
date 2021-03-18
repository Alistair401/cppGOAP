#include <iostream>
#include "Planner.h"
#include "SimpleEffect.h"
#include "SimplePrecondition.h"
#include "SimpleAction.h"

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
    start.Set(HAS, nullptr, NUMBER);

    goap::WorldState goal;
    goal.Set(HUNGRY, nullptr, false);

    std::shared_ptr<goap::SimpleAction> eat = std::make_shared<goap::SimpleAction>(EAT, 1);
    eat->AddPrecondition(new goap::SimplePrecondition(HAS, nullptr, PIZZA));
    eat->AddEffect(new goap::SimpleEffect(HUNGRY, nullptr, false));

    std::shared_ptr<goap::SimpleAction> order = std::make_shared<goap::SimpleAction>(ORDER, 1);
    order->AddPrecondition(new goap::SimplePrecondition(HAS, nullptr, NUMBER));
    order->AddEffect(new goap::SimpleEffect(HAS, nullptr, PIZZA));

    std::shared_ptr<goap::SimpleAction> cook = std::make_shared<goap::SimpleAction>(COOK, 10);
    cook->AddPrecondition(new goap::SimplePrecondition(HAS, nullptr, RECIPE));
    cook->AddEffect(new goap::SimpleEffect(HAS, nullptr, PIZZA));

    std::vector<std::shared_ptr<goap::Action>> actions{ eat, order, cook };
    std::vector<goap::EvaluatedAction> plan = goap::Planner::Plan(start, goal, actions);

    std::unordered_map<int, std::string> actionLookup;
    actionLookup[ORDER] = "ORDER";
    actionLookup[EAT] = "EAT";
    actionLookup[COOK] = "COOK";

    std::unordered_map<int, std::string> objectLookup;
    objectLookup[RECIPE] = "RECIPE";
    objectLookup[NUMBER] = "NUMBER";
    objectLookup[PIZZA] = "PIZZA";

    for (const auto& action : plan)
    {
        std::cout << actionLookup[action.id] << std::endl;
    }
}