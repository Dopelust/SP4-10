#pragma once

#include "StateObject.h"

class PageSystem;
class Button;

class LevelHandler : public StateObject
{
public:
	LevelHandler();
	~LevelHandler();

	void Init(Entity* ent);
	void Update(double dt);

private:
	PageSystem* page;

	Button* next;
	Button* prev;

	Button* back;
};