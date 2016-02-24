#include "EnemyController.h"
#include "../../../AStar/AStar.h"
#include "../../EntityFactory.h"
#include "../../../Enemy/EnemyData.h"
#include "../../../Enemy/EnemyDatabase.h"

StageManager* EnemyController::stage = NULL;

EnemyController::EnemyController() :
done(false),
slowed(false),
stunned(false),
pop(false),
path(NULL),
statusTimer(0),
statusDuration(0),
tier(0),
originalSpeed(0),
movementSpeed(0),
popCount(0)
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
#include "StageManager.h"
#include "PathFinder.h"

void EnemyController::Update(double dt)
{
	if (!path)
		path = owner->GetComponent<PathFinder>();

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
			statusTimer = 0;
		}
	}

	if (stunned)
		return;

	if (path->HasPath())
	{
		Vector3& target = Scene::scene->grid->GetPosition(path->GetTarget());

		directionN = (target - owner->transform->GetPosition()).Normalized();
		owner->transform->Position() += directionN * movementSpeed * (float)dt;

		if (owner->transform->GetPosition().DistSquared(target) < 4 * 4)
		{
			if (path->IsEndOfPath())
				done = true;
			else
				path->Traverse();
		}
	}
	else
	{
		for (auto& end : stage->EndPoints())
		{
			if (GetIndex().DistSquared(end) < 4 * 4)
			{
				done = true;
				break;
			}
		}
	}
}

#include "../../EntityFactory.h"

void EnemyController::Pop(int popCount)
{
	if (tier > 1)
	{
		pop = true;
		this->popCount = popCount;
	}
	
	done = true;

	EntityFactory::GenerateParticle(owner->transform->GetPosition().GetVector2(), owner->transform->GetSize().GetVector2(), "Puff", "Puff");
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

int EnemyController::GetTier()
{
	return tier;
}

EnemyData& EnemyController::GetData()
{
	return EnemyDatabase::GetData(tier);
}

Vector2 EnemyController::GetIndex()
{
	return Scene::scene->grid->GetIndex(owner->transform->GetPosition()).GetVector2();
}
