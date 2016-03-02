#pragma once

#include "../../Component.h"
#include "StateObject.h"

#include <map>
using namespace::std;

class Button;
class PageSystem;

class EnemyInfoScript : public StateObject
{
public:
	EnemyInfoScript();
	~EnemyInfoScript();

	void Init(Entity* ent);
	void Update(double dt);	

private:
	void InitEnemy(Entity *ent);

	Button *back;
};