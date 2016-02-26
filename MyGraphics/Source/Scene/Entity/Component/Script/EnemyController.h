#ifndef ENEMY_CONTROLLER_H
#define ENEMY_CONTROLLER_H

#include "../Component.h"

#include "Vector2.h"

class PathFinder;
class EnemyData;
class StageManager;
struct Vector2;

class EnemyController :
	public Component
{
public:
	static StageManager* stage;

	EnemyController();
	~EnemyController();

	void Init(Entity* ent);
	void Init(int enemyTier);
	void LateInit(bool flying = false, int parentID = -1);
	void Update(double dt);
	void Pop(int popCount = 1);
	void Slow(float slowAmount, float duration);
	void Stun(float duration);

	int GetTier();
	int GetOwnerID();
	EnemyData& GetData();
	
	bool done, pop, split, flying;
	int popCount;
	int hits;

	Vector2 GetIndex();
	int steps;

	int parentID;

private:
	Entity* owner;
	PathFinder* path;

	Vector3 target;
	Vector3 directionN;

	int tier;
	float originalSpeed, movementSpeed;

	bool slowed, stunned;
	float statusTimer;
	float statusDuration;
};

#endif