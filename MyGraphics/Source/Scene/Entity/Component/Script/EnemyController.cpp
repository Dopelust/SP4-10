#include "EnemyController.h"
#include "../../../AStar/AStar.h"
#include "Vector2.h"
#include "../../EntityFactory.h"
#include "../../../Enemy/EnemyData.h"
#include "../../../Enemy/EnemyDatabase.h"

EnemyController::EnemyController() :
done(false),
slowed(false),
stunned(false),
moveNode(NULL),
steps(0),
statusTimer(0),
statusDuration(0),
tier(0)
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

	//owner->GetComponent<Graphic2D>()->SetTexture(Resource.GetTexture(enemyTexture.c_str()));

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
		Vector3 target;
		target = Scene::scene->grid->GetPosition(Vector2(moveNode->x, moveNode->y));

		owner->transform->Position() += (target - owner->transform->GetPosition()).Normalized() * movementSpeed * (float)dt;

		if (owner->transform->GetPosition().DistSquared(target) < 1 * 1)
		{
			owner->transform->Position() = target;
			moveNode = moveNode->child;
			++steps;
		}
	}
	else
	{
		done = true;
	}
}

void EnemyController::SetNode(Node* startNode)
{
	if (startNode != NULL)
		this->moveNode = startNode->child;
}

#include "../../EntityFactory.h"

void EnemyController::Pop()
{
	if (tier > 1)
	{
		for (int i = 0; i < GetData().split; ++i)
		{
			EntityFactory::GenerateEnemy(this->owner->transform->GetPosition().GetVector2(), --tier);
		}
	}
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