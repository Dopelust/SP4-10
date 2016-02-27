#pragma once

#include "MenuObject.h"

class Button;

class LevelSelectScript : public MenuObject
{
public:
	LevelSelectScript();
	~LevelSelectScript();

	void Init(Entity* ent);
	void Update(double dt);

	void PlayLevel(const char* level);

private:
	Button* level1,*level2,*level3,*level4;
	Button* custom;
	Button* back;
};