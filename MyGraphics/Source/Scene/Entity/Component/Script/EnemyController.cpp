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
split(false),
flying(false),
path(NULL),
statusTimer(0),
statusDuration(0),
tier(0),
originalSpeed(0),
movementSpeed(0),
parentID(-1),
hits(1),
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

void EnemyController::Init(int enemyTier)
{
	this->tier = enemyTier;
	//owner->GetComponent<Graphic2D>()->SetTexture(Resource.GetTexture(GetData().name.c_str()));
	hits = GetData().hits;
	flying = GetData().flying;
	originalSpeed = GetData().movementSpeed;
	movementSpeed = originalSpeed;
}

void EnemyController::LateInit(bool flying, int parentID)
{
	this->flying = flying;
	this->parentID = parentID;
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

		if (owner->transform->GetPosition().DistSquared(target) < (512 * dt) * (512 * dt))
		{
			if (path->IsEndOfPath())
			{
				if (stage->Hit())
				{
					pop = true;
					done = true;
				}
			}
			else
				path->Traverse();
		}
	}
	else
	{
		for (auto& end : stage->EndPoints())
		{
			if (GetIndex().DistSquared(end) < (512 * dt) * (512 * dt))
			{
				if (stage->Hit())
				{
					pop = true;
					done = true;
				}
			
				break;
			}
		}
	}
}

#include "../../EntityFactory.h"

#include "../SpriteAnimator.h"
#include "Utility.h"

#include "ScaleScript.h"
#include "FadeScript.h"
#include "../SpriteRenderer.h"
#include "../SpriteAnimator.h"

void EnemyController::Pop(int popCount)
{
	Entity* particle = NULL;

	hits -= 1;

	if (hits <= 0)
	{
		if (tier - popCount > 0)
		{
			if (GetData().split > 1)
			{
				split = true;
				done = true;
				popCount = popCount;
			}

			tier -= popCount;
			hits = GetData().hits;

			owner->GetComponent<SpriteAnimator>()->Play(("Jellies" + ToString(tier)).c_str(), true);
		}
		else
		{
			done = true;
			particle = EntityFactory::GenerateParticle(Vector2(), owner->transform->GetSize().GetVector2() * 0.9f, "Puff", "Puff");
		}

		pop = true;
		particle = owner->AttachChild(EntityFactory::CreateParticle(Vector2(), owner->transform->GetSize().GetVector2() * 0.9f, "Puff", "Puff"));
	}

	if (particle)
	{
		particle->AddComponent<FadeScript>()->rate = -3;
		particle->GetComponent<FadeScript>()->value = &particle->GetComponent<SpriteRenderer>()->color.w;
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

int EnemyController::GetTier()
{
	return tier;
}

int EnemyController::GetOwnerID()
{
	return owner->GetID();
}

EnemyData& EnemyController::GetData()
{
	return EnemyDatabase::GetData(tier);
}

Vector2 EnemyController::GetIndex()
{
	return Scene::scene->grid->GetIndex(owner->transform->GetPosition()).GetVector2();
}
