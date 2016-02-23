#include "EnemyController.h"
#include "../../../AStar/AStar.h"
#include "../../EntityFactory.h"
#include "../../../Enemy/EnemyData.h"
#include "../../../Enemy/EnemyDatabase.h"

EnemyController::EnemyController() :
done(false),
slowed(false),
stunned(false),
pop(false),
moveNode(NULL),
steps(0),
statusTimer(0),
statusDuration(0),
tier(0),
originalSpeed(0),
movementSpeed(0)
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

void EnemyController::LateInit(int enemyTier)
{
	this->tier = enemyTier;
	owner->GetComponent<Graphic2D>()->SetTexture(Resource.GetTexture(GetData().name.c_str()));

	originalSpeed = GetData().movementSpeed;
	movementSpeed = originalSpeed;
}

#include "../../../../Grid.h"
#include "../../../Scene.h"

void EnemyController::Update(double dt)
{
	if (stunned || slowed)
	{
		statusTimer += (float)dt;
		if (statusTimer > statusDuration)
		{
			if (slowed)
			{
				slowed = false;
				movementSpeed = originalSpeed;
			}
			else
			{
				stunned = false;
			}
		}
	}

	if (stunned)
		return;

	if (moveNode)
	{
		//target = Scene::scene->grid->GetPosition(Vector2(moveNode->x, moveNode->y));
		UpdateDirection();
		owner->transform->Position() += directionN * movementSpeed * (float)dt;

		if (owner->transform->GetPosition().DistSquared(target) < 1 * 1)
		{
			owner->transform->Position() = target;
			indexPos.Set(moveNode->x, moveNode->y);
			moveNode = moveNode->child;
			//UpdateDirection();
			++steps;
		}
	}
	else
	{
		done = true;
	}
}

void EnemyController::UpdateDirection()
{
	//if (moveNode)
	//{
		target = Scene::scene->grid->GetPosition(Vector2(moveNode->x, moveNode->y));
		directionN = (target - owner->transform->GetPosition()).Normalized();
	//}
}

void EnemyController::SetNode(Node* startNode, int pathFinderNo)
{
	if (startNode != NULL)
	{
		this->pathFinderNo = pathFinderNo;
		this->moveNode = startNode->child;
		indexPos.Set(moveNode->x, moveNode->y);
		UpdateDirection();
	}
}

const struct { int x, y; } succ[4] = { { 0, -1 }, { 0, 1 }, { 1, 0 }, { -1, 0 } };

#include "PathFinder.h"

void EnemyController::UpdatePath()
{
	Node* node = owner->GetComponent<PathFinder>()->GetStart();

	moveNode = node->child;

	/*Node* checkNode;
	checkNode = node;

	Node* shortest;
	int shortestStep = 999;

	while (checkNode)
	{
		if (checkNode->x == indexPos.x && checkNode->y == indexPos.y)
		{
			moveNode = checkNode->child;
			return;
		}

		int steps = abs((checkNode->x - indexPos.x)) + abs((checkNode->y - indexPos.y));
		if (steps < shortestStep)
		{
			shortestStep = steps;
			shortest = checkNode;
		}
		else
		{
			checkNode = checkNode->child;
		}
	}

	moveNode = shortest;*/
}

#include "../../EntityFactory.h"

void EnemyController::Pop()
{
	if (tier > 1)
	{
		pop = true;
	}
	
	done = true;
}

void EnemyController::Slow(float slowAmount, float duration)
{
	slowed = true;
	movementSpeed = originalSpeed - slowAmount;
	statusDuration = duration;
}

void EnemyController::Stun(float duration)
{
	stunned = true;
	statusDuration = duration;
}

EnemyData& EnemyController::GetData()
{
	return EnemyDatabase::GetData(tier);
}