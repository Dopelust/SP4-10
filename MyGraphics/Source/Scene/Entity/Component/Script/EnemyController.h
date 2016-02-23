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
	void LateInit(int enemyTier);
	void Update(double dt);
	void Pop();
	void Slow(float slowAmount, float duration);
	void Stun(float duration);

	EnemyData& GetData();
	
	int tier;
	float originalSpeed, movementSpeed;

	bool done, slowed, stunned;
	float statusTimer;
	float statusDuration;

	Vector2 GetIndex();

	bool pop;

	int parentID;

private:
	Entity* owner;
	PathFinder* path;

	Vector3 target;
	Vector3 directionN;
};

#endif