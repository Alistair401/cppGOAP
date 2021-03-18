# cppGOAP 
## A fork of [cpowell/cppGOAP](https://github.com/cpowell/cppGOAP)

Goal Oriented Action Programming (GOAP) is a planning architecture used in video games and other real-time applications. It's best described by Jeff Orkin [here](http://alumni.media.mit.edu/~jorkin/goap.html).

Give the GOAP planner a start and a goal and a list of possible actions and it'll plan a sequence of actions to reach the goal. Defining actions can be simpler and more modular than defining transitions for a finite state machine, plus it allows for more emergent behaviour.

## How to use

### Set up

- Install [CMake](https://cmake.org/).
- Clone this repo.
- Navigate to a directory where you'd like to put build files.
- Decide whether you want to build the library on it's own, or together with the examples.
- Run `cmake -DCMAKE_CONFIGURATION_TYPES="Debug;Release" -DCMAKE_GENERATOR_PLATFORM=x64 -G "Visual Studio 16 2019" <path to CMakeLists.txt>` from the command line. Replace `Visual Studio 16 2019` with whatever build tool you're using. Replace `<path to CMakeLists.txt>` with either the path to the "goap" directory of this repo to build the library, or the path to the root of the repo to build the examples too.
- Open the generated "cppGoap.sln" or build with your build tool.

### Simple usage

Everything provided is in the `goap` namespace.

A plan needs a `start` and a `goal`. These are each given to the planner as a `WorldState`. A `WorldState` is a simplified representation of the world which maps a `variable`/`subject` pair to a `Value`. Each `variable` is an integer identifier, and each `subject` is just a `void*` which you're free to set to whatever you like, as long as it's unique. Each `Value` in a world state can be a `BOOL`, `FLOAT` or `INT`.

```c++
goap::WorldState start;
start.Set(HAS_NUMBER, nullptr, true);
start.Set(HAS_RECIPE, nullptr, true);
start.Set(HUNGRY, nullptr, true);

goap::WorldState goal;
goal.Set(HUNGRY, nullptr, false);
```

A plan is a sequence of actions. An `Action` is given a goal state to act on, and produces `effects` given that `preconditions` are met. A `SimpleAction` class is provided that stores `Effect`s and `Precondition`s, and `SimpleEffect` and `SimplePrecondition` implementations are provided for those. Each `Action` has an integer identifier and a cost.

```c++
std::shared_ptr<goap::SimpleAction> order = std::make_shared<goap::SimpleAction>(ORDER, 1);
eat->AddPrecondition(new goap::SimplePrecondition(HAS_NUMBER, nullptr, true));
eat->AddEffect(new goap::SimpleEffect(HUNGRY, nullptr, false));

std::shared_ptr<goap::SimpleAction> cook = std::make_shared<goap::SimpleAction>(COOK, 5);
eat->AddPrecondition(new goap::SimplePrecondition(HAS_RECIPE, nullptr, true));
eat->AddEffect(new goap::SimpleEffect(HUNGRY, nullptr, false));

std::vector<std::shared_ptr<goap::Action>> actions{ order, cook };
```

The `Planner` class calculates a plan.

```c++
std::vector<goap::PlannedAction> plan = goap::Planner::Plan(start, goal, actions);
```

Finally the plan that is created is a list of `PlannedAction` in order of expected execution.

```c++
for (int i = 0; i < plan.size(); i++)
{
	goap::PlannedAction nextAction = plan[i];
}
```

### Advanced usage

The `Action` abstract class can be extended to create complex and dynamic actions.

```c++
class CustomAction : public goap::Action
{
public:
    CustomAction(int id, int cost)
        : goap::Action(id, cost) {}

    virtual goap::PlannedAction Act(
		const goap::WorldState& goal,
		goap::WorldState& preconditions,
		goap::WorldState& effects) override
    {
		preconditions.Set(...)
		effects.Set(...)

		if (<failure condition>)
			return goap::PlannedAction::Fail();

        return goap::PlannedAction(this->id_);
    }
};
```

Custom actions are able to evaluate the current goal state (this is not necessarily the final goal state of the desired plan), and set the preconditions and effects of the action accordingly.

A `DistanceFunctionMap` can be passed to the planner to override the default distance between non-equal values. These distances functions inform the heuristic used to calculate an estimate between each state and a goal state. Providing a custom distance function can help the planner converge on an optimal plan faster, but **be careful** as a distance function that overestimates the distance between two values can cause the planner to produce non-optimal plans.

The `PlannedAction` returned by `Action::Act` can be given a `Value` which will be given as part of the formulated plan. `ActionWithValue` is provided which can be given a constant value to return. This might be useful for cases where an action acts on a specific target or has varying behaviour depending its desired effects.

```c++
std::shared_ptr<goap::ActionWithValue> eatPizza = std::make_shared<goap::ActionWithValue>(EAT, 1, goap::Value(PIZZA));
std::shared_ptr<goap::ActionWithValue> eatCake = std::make_shared<goap::ActionWithValue>(EAT, 1, goap::Value(CAKE));
```
