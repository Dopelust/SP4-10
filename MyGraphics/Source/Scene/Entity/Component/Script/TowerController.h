#ifndef TOWER_CONTROLLER_H
#define TOWER_CONTROLLER_H

#include "../Component.h"
#include "Vector2.h"

#include <string>
#include <vector>

using namespace::std;

struct TowerData;
class StageManager;
class SpriteRenderer;
class Entity;

// Script that controls tower
class TowerController : public Component
{
public:
	enum TowerState
	{
		SEARCHING,
		FIRE,
		MAX_STATE,
	};

	TowerState state;

	enum FireMode
	{
		FIRST,
		LAST,
		STRONGEST,
		MAX_MODE,
	};

	FireMode fireMode;

	TowerController();
	~TowerController();

	void Init(Entity* ent);
	void Init(string type);

	void Update(double dt);

	bool Upgrade();
	bool IsMaxUpgrade();

	bool Hover(Vector2& hoverIndex);
	
	Entity* owner;
	Entity* target;
	// Which index on the grid the tower is on
	Vector2 index; 

	string type;
	int upgrade;

	TowerData* GetData();
	int GetCost();
	int GetDamage();
	float GetCooldown();
	int GetRange();
	string GetProjectileType();

	// Timers
	float firingTimer;
	float searchTimer;

	Vector2 direction;
	float rotation;

	vector<Entity*> entityList;
	StageManager* stageManager;

	SpriteRenderer* rank;

private:
	bool SearchForTarget();
	// Check whether current target left range or is still alive
	bool CheckTarget();
	void TargetRotation(float dt);
	void Fire();
};

#endif