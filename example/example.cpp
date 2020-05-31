#include "Planner.h"
#include "SimplePrecondition.h"
#include "SimpleEffect.h"

enum Action
{
	ORDER,
	EAT,
	COOK,
};

enum Verb 
{
	HUNGRY,
	HAS,
};

enum Object 
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

	goap::Action eat(EAT, 1);
	eat.AddPrecondition(new goap::SimplePrecondition(HAS, PIZZA));
	eat.AddEffect(new goap::SimpleEffect(HUNGRY, false));

	goap::Action order(ORDER, 1);
	order.AddPrecondition(new goap::SimplePrecondition(HAS, NUMBER));
    order.AddEffect(new goap::SimpleEffect(HAS, PIZZA));

	goap::Action cook(COOK, 10);
	cook.AddPrecondition(new goap::SimplePrecondition(HAS, RECIPE));
    cook.AddEffect(new goap::SimpleEffect(HAS, PIZZA));

	goap::Planner planner;
    std::vector<goap::Action> actions{ eat, order, cook };
	std::vector<goap::PlannedAction> plan = planner.plan(start, goal, actions);
}