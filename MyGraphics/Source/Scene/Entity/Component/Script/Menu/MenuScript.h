#pragma once

#include "StateObject.h"

class Button;

class MenuScript : public StateObject
{
public:
	MenuScript();
	~MenuScript();

	void Init(Entity* ent);
	void Update(double dt);

private:
	Button* play;
	Button* resume;

	Button* option;
	Button* notebook;
	Button* achievement;
	Button* exit;
};