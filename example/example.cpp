#include "Planner.h"
#include "SimplePrecondition.h"
#include "SimpleEffect.h"
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
	RECIPE,
	NUMBER,
	PIZZA
};

int main()
{
	goap::WorldState start;
	start.setBool(HUNGRY, true);
    start.setInt(HAS, NUMBER);

	goap::WorldState goal;
	goal.setBool(HUNGRY, false);

	std::shared_ptr<goap::SimpleAction> eat = std::make_shared<goap::SimpleAction>(EAT, 1);
    eat->AddPrecondition(new goap::SimplePrecondition(HAS, PIZZA));
    eat->AddEffect(new goap::SimpleEffect(HUNGRY, false));

    std::shared_ptr<goap::SimpleAction> order = std::make_shared<goap::SimpleAction>(ORDER, 1);
    order->AddPrecondition(new goap::SimplePrecondition(HAS, NUMBER));
    order->AddEffect(new goap::SimpleEffect(HAS, PIZZA));

    std::shared_ptr<goap::SimpleAction> cook = std::make_shared<goap::SimpleAction>(COOK, 10);
    cook->AddPrecondition(new goap::SimplePrecondition(HAS, RECIPE));
    cook->AddEffect(new goap::SimpleEffect(HAS, PIZZA));

	goap::Planner planner;
    std::vector<std::shared_ptr<goap::Action>> actions{ eat, order, cook };
	std::vector<goap::PlannedAction> plan = planner.plan(start, goal, actions);
}