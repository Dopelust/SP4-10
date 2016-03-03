#pragma once

#include "../../Component.h"
#include "StateObject.h"

#include <map>
using namespace::std;

class Button;
class PageSystem;

class ShortcutInfoScript : public StateObject
{
public:
	ShortcutInfoScript();
	~ShortcutInfoScript();

	void Init(Entity* ent);
	void Update(double dt);	

private:
	void InitTowers(Entity *ent);
};