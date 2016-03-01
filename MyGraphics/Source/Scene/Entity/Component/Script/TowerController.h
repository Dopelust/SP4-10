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
	enum TowerAI
	{
		SEARCH_AND_DESTROY,
		STATIC,
		FIXED_ROTATION,
		MAX_AI,
	};

	TowerAI ai;

	enum TowerState
	{
		SEARCHING,
		FIRE,
		MAX_STATE,
	};

	TowerState state;

	enum FireMode
	{
		CLOSEST,
		FIRST,
		LAST,
		STRONGEST,
		MAX_MODE,
	};

	TowerController();
	~TowerController();

	void Init(Entity* ent);
	void Init(string type);

	void Update(double dt);

	void SetUpgrade(int upgrade);
	bool Upgrade();
	bool IsMaxUpgrade();

	bool Hover(Vector2& hoverIndex);
	
	TowerData* GetData();
	int GetAI();
	int GetCost();
	int GetDamage();
	float GetCooldown();
	int GetRange();
	string GetProjectileType();

	void SetSearchMode(TowerController::FireMode mode);
	TowerController::FireMode GetFireMode();

	// Which index on the grid the tower is on
	Vector2 index; 

	string type;
	int upgrade;

	StageManager* stageManager;

	SpriteRenderer* rank;

private:
	bool SearchForTarget();
	// Check whether current target left range or is still alive
	bool CheckTarget();
	void TargetRotation(float dt);
	void Fire();

	Entity* owner;
	Entity* target;

	FireMode fireMode;

	// Timers
	float firingTimer;
	float searchTimer;

	Vector2 direction;
	float rotation;

	vector<Entity*> entityList;
};

#endif