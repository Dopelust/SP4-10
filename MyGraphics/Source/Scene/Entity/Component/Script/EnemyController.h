#ifndef ENEMY_CONTROLLER_H
#define ENEMY_CONTROLLER_H

#include "../Component.h"

#include "Vector2.h"

class Node;
class EnemyData;
struct Vector2;

class EnemyController :
	public Component
{
public:
	EnemyController();
	~EnemyController();

	void Init(Entity* ent);
	void LateInit(int enemyTier);
	void Update(double dt);
	void SetNode(Node* startNode, int pathFinderNo);
	void UpdatePath();
	void Pop();
	void Slow(float slowAmount, float duration);
	void Stun(float duration);

	EnemyData& GetData();
	
	int tier;
	float originalSpeed, movementSpeed;

	bool done, slowed, stunned;
	float statusTimer;
	float statusDuration;

	int steps;
	int pathFinderNo;
	Vector2 indexPos;

	bool pop;

	int parentID;

private:
	void UpdateDirection();

	Entity* owner;
	Node* moveNode;

	Vector3 target;
	Vector3 directionN;
};

#endif