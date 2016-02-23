#include "TowerController.h"
#include "../../Component/Graphic2D.h"
#include "../../../../Texture.h"
#include "../../../../Assets.h"
#include "../../../Tower/TowerDatabase.h"
#include "../../Component/Transform.h"
#include "StageManager.h"
#include "../../Entity.h"

#include <iostream>

#include "../../../Scene.h"

TowerController::TowerController() :
state(TowerState::SEARCHING),
fireMode(FireMode::CLOSEST),
owner(NULL),
target(NULL),
upgrade(0),
stageManager(NULL),
searchTimer(0),
firingTimer(0),
direction(0, 0),
rotation(0)
{
}

TowerController::~TowerController()
{

}

#include "../SpriteRenderer.h"
#include "../../../../Spritesheet.h"

void TowerController::Init(Entity* ent)
{
	this->owner = ent;
	stageManager = Scene::scene->root->GetChild("Stage Manager")->GetComponent<StageManager>();
}

#include "../../../Projectile/ProjectileDatabase.h"

void TowerController::Init(string type)
{
	this->type = type;
	stageManager = Scene::scene->root->GetChild("Stage Manager")->GetComponent<StageManager>();
}

void TowerController::Update(double dt)
{
	firingTimer += (float)dt;

	switch (state)
	{
		case TowerState::SEARCHING:
		{
			searchTimer += (float)dt;
			if (searchTimer > 0.1f)
			{
				searchTimer = 0;
				if (SearchForTarget())
				{
					state = TowerState::FIRE;
				}
			}
		}
		break;
		case TowerState::FIRE:
		{
			// Create projectile, set rotation
			if (CheckTarget())
			{
				state = TowerState::SEARCHING;
				break;
			}

			TargetRotation((float)dt);

			if (firingTimer > GetCooldown())
			{
				firingTimer = 0;
				Fire();
				state = TowerState::SEARCHING;
			}
		}
		break;
	}
}

bool TowerController::Upgrade()
{
	upgrade++;
	rank->SetSprite(Resource.GetSpritesheet("Rank")->GetSprite(upgrade));

	return true;
}

bool TowerController::IsMaxUpgrade()
{
	return upgrade == TowerDatabase::GetMaxUpgrade(type.c_str());
}

TowerData* TowerController::GetData()
{
	return &TowerDatabase::GetData(type.c_str())[upgrade];
}

int TowerController::GetCost()
{
	return GetData()->cost;
}

int TowerController::GetDamage()
{
	return GetData()->pierce;
}

float TowerController::GetCooldown()
{
	return GetData()->cooldown;
}

int TowerController::GetRange()
{
	return GetData()->range;
}

string TowerController::GetProjectileType()
{
	return GetData()->projectileName;
}

bool TowerController::Hover(Vector2& hoverIndex)
{
	if (this->index == hoverIndex)
		return true;
	else
		return false;
}

#include "EnemyController.h"

bool TowerController::SearchForTarget()
{
	entityList.clear();
	entityList = stageManager->enemies;

	int range = GetData()->range;

	if (fireMode == FireMode::CLOSEST)
	{
		Entity* closest = NULL;
		float closestDistSq;
		closestDistSq = 99999999.f;

		for (int i = 0; i < entityList.size(); ++i)
		{
			float distSq = (entityList[i]->transform->GetPosition() - this->owner->transform->GetPosition()).LengthSquared();
			if ((entityList[i]->transform->GetPosition() - this->owner->transform->GetPosition()).LengthSquared() < range * range)
			{
				if (distSq < closestDistSq)
				{
					closestDistSq = distSq;
					closest = entityList[i];
				}
			}
		}
		target = closest;
	}
	else if (fireMode == FireMode::FIRST)
	{
		Entity* first = NULL;
		int highestStep = 0;
		for (int i = 0; i < entityList.size(); ++i)
		{
			float distSq = (entityList[i]->transform->GetPosition() - this->owner->transform->GetPosition()).LengthSquared();
			if ((entityList[i]->transform->GetPosition() - this->owner->transform->GetPosition()).LengthSquared() < range * range)
			{
				//if (entityList[i]->GetComponent<EnemyController>()->steps > highestStep)
				{
					//highestStep = entityList[i]->GetComponent<EnemyController>()->steps;
					first = entityList[i];
				}
			}
		}
		target = first;
	}
	else if (fireMode == FireMode::LAST)
	{
		Entity* last = NULL;
		int lowestStep = 999;
		for (int i = entityList.size() - 1; i > 0; --i)
		{
			if ((entityList[i]->transform->GetPosition() - this->owner->transform->GetPosition()).LengthSquared() < range * range)
			{
				//if (entityList[i]->GetComponent<EnemyController>()->steps < lowestStep)
				{
					//lowestStep = entityList[i]->GetComponent<EnemyController>()->steps;
					last = entityList[i];
				}
			}
		}
		target = last;
	}
	else
	{
		Entity* mostHealth = entityList[0];
		for (int i = 0; i < entityList.size(); ++i)
		{
			if ((entityList[i]->transform->GetPosition() - this->owner->transform->GetPosition()).LengthSquared() < range * range)
			{
				if (entityList[i]->GetComponent<EnemyController>()->tier > mostHealth->GetComponent<EnemyController>()->tier)
				{
					mostHealth = entityList[i];
				}
			}
		}
		target = mostHealth;
	}
	
	if (target != NULL)
	{
		direction = (target->transform->GetPosition() - this->owner->transform->GetPosition()).GetVector2();
		return true;
	}

	return false;
}

bool TowerController::CheckTarget()
{
	if (target == NULL)
	{
		return true;
	}
	
	else if (direction.LengthSquared() > GetData()->range * GetData()->range || target->GetComponent<EnemyController>()->done)
	{
		target = NULL;
		return true;
	}
	
	return false;
}

#include "MyMath.h"
#include "../../Entity.h"
#include "Utility.h"

void TowerController::TargetRotation(float dt)
{
	direction = (target->transform->GetPosition() - this->owner->transform->GetPosition()).GetVector2();

	rotation = (atan2(direction.y, direction.x) * 180.f / 3.14f) - 90.f;

	this->owner->transform->SetRotation(0, 0, rotation);
}

#include "../../../Entity/EntityFactory.h"
#include "ProjectileController.h"

void TowerController::Fire()
{
	Entity* proj = EntityFactory::GenerateProjectile(this->owner->transform->GetPosition().GetVector2(), GetProjectileType());
	proj->GetComponent<Projectile>()->SetProperties(GetData(), direction.Normalized(), rotation);
}