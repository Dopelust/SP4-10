#pragma once

#include "MenuObject.h"

class Button;

class MenuScript : public MenuObject
{
public:
	MenuScript();
	~MenuScript();

	void Init(Entity* ent);
	void Update(double dt);

private:
	Button* play;
	Button* resume;

	Button* editor;
	Button* option;
	Button* exit;
};