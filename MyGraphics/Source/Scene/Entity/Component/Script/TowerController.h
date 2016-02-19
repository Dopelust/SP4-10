#ifndef TOWER_CONTROLLER_H
#define TOWER_CONTROLLER_H

#include "../Component.h"
#include "Vector2.h"

#include <string>
using namespace::std;

class TowerData;

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
	bool Upgrade(bool path, int pathNo);
	bool Hover(Vector2& hoverIndex);
	
	Entity* owner;
	Entity* target;
	// Which index on the grid the tower is on
	Vector2 index; 

	string type, upgrade;

	TowerData* GetData();
	int GetCost();
	float GetCooldown();
	int GetRange();
	string GetProjectileType();

	// Timers
	float firingTimer;
	float searchTimer;

	Vector2 direction;

private:
	bool SearchForTarget();
	// Check whether current target left range or is still alive
	bool CheckTarget();
	void TargetRotation();
	void Fire();
};

#endif