#include "EnemyController.h"
#include "../../../AStar/AStar.h"
#include "Vector2.h"
#include "../../EntityFactory.h"
EnemyController::EnemyController() :
done(false),
moveNode(NULL)
{
}


EnemyController::~EnemyController()
{
}

void EnemyController::Init(Entity* ent)
{
	this->owner = ent;
}

#include "../Graphic2D.h"
#include "../../Entity.h"
#include "../../Entity.h"
#include "../../Component/Transform.h"
#include "../../../../Assets.h"

void EnemyController::LateInit(string enemyTexture, int enemyTier, float enemySpeed)
{
	owner->GetComponent<Graphic2D>()->SetTexture(Resource.GetTexture(enemyTexture.c_str()));
	tier = enemyTier;
	movementSpeed = enemySpeed;
}

#include "../../../../Grid.h"
#include "../../../Scene.h"

void EnemyController::Update(double dt)
{
	// To Do: Move from tile to tile
	// Enemy contains node which has grid indexes
	// Get real position ( grid->GetIndex(current->x, current->y )
	// Move using this->owner->transform->position += direction * enemySpeed * dt;
	// Move from tile to tile ( current = current->next )
	// Repeat until end

	if (moveNode)
	{
		Vector3 target;
		target = Scene::scene->grid->GetPosition(Vector2(moveNode->x, moveNode->y));

		owner->transform->Position() += (target - owner->transform->GetPosition()).Normalized() * movementSpeed * dt;

		if (owner->transform->GetPosition().DistSquared(target) < 1 * 1)
		{
			owner->transform->Position() = target;
			moveNode = moveNode->child;
		}
	}
	else
		done = true;
}

void EnemyController::SetNode(Node* startNode)
{
	if (startNode != NULL)
		this->moveNode = startNode->child;
}

#include "../../EntityFactory.h"

void EnemyController::Pop()
{
	//EntityFactory::GenerateEnemy(this->owner->transform->GetPosition(), )
}

