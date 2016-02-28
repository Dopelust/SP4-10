#include "StateHandler.h"
#include "StateObject.h"

#include "../../../Entity.h"

StateHandler::StateHandler()
{
}

StateHandler::~StateHandler()
{
}

void StateHandler::Update(double dt)
{
	for (auto& state : pool)
	{
		if (state == GetState())
			continue;

		if (state->ReachedTarget())
			state->owner->SetActive(false);
	}
}

void StateHandler::AddState(StateObject * state)
{
	pool.push_back(state);
	state->menu = this;
}

StateObject * StateHandler::GetState()
{
	if (stack.empty())
		return NULL;

	return stack.back();
}

void StateHandler::Push(StateObject * state)
{
	if (GetState())
		GetState()->Disappear(true);

	stack.push_back(state);
	state->owner->SetActive(true);
	state->Appear();
}

bool StateHandler::Pop()
{
	if (stack.empty())
		return false;

	GetState()->Disappear(false);
	stack.pop_back();

	if (GetState())
	{
		GetState()->Appear();
		GetState()->owner->SetActive(true);
	}

	return true;
}