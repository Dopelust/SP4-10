#pragma once

#include "../../Component.h"

class MenuObject;
class MenuScript;
class LevelSelectScript;
class OptionScript;
class Sound;

class MenuHandler : public Component
{
public:
	MenuHandler();
	~MenuHandler();

	LevelSelectScript* levelselect;
	MenuScript* menu;
	OptionScript* option;

	void Init(Entity* ent);
	void Update(double dt);
	void Exit();

	void Switch(MenuObject* state);

private:
	MenuObject* state;
	Sound* bgm;
};