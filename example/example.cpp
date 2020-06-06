#include <iostream>
#include "Planner.h"
#include "SimpleEffect.h"
#include "SimpleAction.h"
#include "BitwiseOrEffect.h"
#include "MaskPrecondition.h"
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
    start.setBool(HUNGRY, true);
    start.setInt(HAS, NUMBER | RECIPE);

    goap::WorldState goal;
    goal.setBool(HUNGRY, false);

    std::shared_ptr<goap::ActionWithValue> eat = std::make_shared<goap::ActionWithValue>(EAT, 1, goap::Value(PIZZA));
    eat->AddPrecondition(new goap::MaskPrecondition(HAS, PIZZA));
    eat->AddEffect(new goap::SimpleEffect(HUNGRY, false));

    std::shared_ptr<goap::ActionWithValue> order = std::make_shared<goap::ActionWithValue>(ORDER, 1, goap::Value(PIZZA));
    order->AddPrecondition(new goap::MaskPrecondition(HAS, NUMBER));
    order->AddEffect(new goap::BitwiseOrEffect(HAS, PIZZA));

    std::shared_ptr<goap::ActionWithValue> cook = std::make_shared<goap::ActionWithValue>(COOK, 10, goap::Value(PIZZA));
    cook->AddPrecondition(new goap::MaskPrecondition(HAS, RECIPE));
    cook->AddEffect(new goap::BitwiseOrEffect(HAS, PIZZA));

    goap::Planner planner;
    std::vector<std::shared_ptr<goap::Action>> actions{ eat, order, cook };
    std::vector<goap::PlannedAction> plan = planner.plan(start, goal, actions);

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