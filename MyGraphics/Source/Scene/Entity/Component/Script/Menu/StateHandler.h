#pragma once

#include "../../Component.h"

#include <vector>
using namespace::std;

class StateObject;

class StateHandler : public Component
{
public:
	StateHandler();
	~StateHandler();

	virtual void Update(double dt);

	void AddState(StateObject* state);

	template<typename T> T* GetState()
	{
		for (auto& state : pool)
		{
			if (typeid(*state) == typeid(T))
			{
				return static_cast<T*>(state);
			}
		}

		return NULL;
	}

	StateObject* GetState();
	void Push(StateObject* state);
	bool Pop();

private:
	vector<StateObject*> stack;
	vector<StateObject*> pool;
};