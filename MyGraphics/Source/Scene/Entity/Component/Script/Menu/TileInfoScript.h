#pragma once

#include "StateObject.h"

#include <map>
using namespace::std;

class Button;

class TileInfoScript : public StateObject
{
public:
	TileInfoScript();
	~TileInfoScript();

	void Init(Entity* ent);
	void Update(double dt);

	void AddButton(Button* button, Entity* info);

private:
	Entity* first;
	Entity* select;

	map<Button*, Entity*> buttonMap;
	void Show(Entity* info);
};