#pragma once

#include "StateHandler.h"

class StateObject;
class Sound;

class MenuHandler : public StateHandler
{
public:
	MenuHandler();
	~MenuHandler();

	void Init(Entity* ent);
	void Update(double dt);
	void Exit();

private:
	Sound* bgm;
};