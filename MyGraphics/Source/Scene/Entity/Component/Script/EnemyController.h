#ifndef ENEMY_CONTROLLER_H
#define ENEMY_CONTROLLER_H

#include "../Component.h"

class Node;
class EnemyData;
class EnemyController :
	public Component
{
public:
	EnemyController();
	~EnemyController();

	void Init(Entity* ent);
	void LateInit(int enemyTier);
	void Update(double dt);
	void SetNode(Node* startNode);
	void Pop();
	void Slow(float slowAmount, float duration);
	void Stun(float duration);

	EnemyData& GetData();

	float originalSpeed, movementSpeed;
	Node* startNode;
	int steps;
	
	bool done, slowed, stunned;
	float statusTimer;
	float statusDuration;

	int tier;

private:
	void UpdateDirection();

	Entity* owner;
	Node* moveNode;

	Vector3 target;
	Vector3 directionN;
};

#endif