#pragma once

#include "../../Component.h"
#include "LevelSelectObject.h"

#include <map>
using namespace::std;

class Button;

class LevelSelectScript : public Component, public LevelSelectObject
{
public:
	LevelSelectScript();
	~LevelSelectScript();

	void Init(Entity* ent);
	void Update(double dt);
	
	void AddLevel(const char* name, const char* level, const Vector2& position, Entity* owner, bool lock);

private:
	map<string, Button*> levels;
};