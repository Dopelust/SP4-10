#ifndef ENEMY_CONTROLLER_H
#define ENEMY_CONTROLLER_H

#include "../Component.h"

class Node;
class EnemyController :
	public Component
{
public:
	EnemyController();
	~EnemyController();

	void Init(Entity* ent);
	void LateInit(std::string enemyTexture, int enemyTier, float enemySpeed);
	void Update(double dt);
	void SetNode(Node* startNode);
	void Pop();

	int tier;
	float movementSpeed;
	Node* startNode;
	
	bool done;

private:
	Entity* owner;

	Node* moveNode;
};

#endif