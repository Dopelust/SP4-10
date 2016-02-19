#include "TowerController.h"
#include "../../Component/Graphic2D.h"
#include "../../../../Texture.h"
#include "../../../../Assets.h"
#include "../../../Tower/TowerDatabase.h"
#include "../../Component/Transform.h"

TowerController::TowerController() :
state(TowerState::SEARCHING),
fireMode(FireMode::FIRST),
owner(NULL),
target(NULL),
upgrade("INITIAL")
{
}

TowerController::~TowerController()
{

}

void TowerController::Init(Entity* ent)
{
	this->owner = ent;
}

#include "../../../Projectile/ProjectileDatabase.h"

void TowerController::Init(string type)
{
	this->type = type;
}

void TowerController::Update(double dt)
{
	firingTimer += (float)dt;

	switch (state)
	{
		case TowerState::SEARCHING:
		{
			searchTimer += (float)dt;
			if (searchTimer > 0.5f && CheckTarget() == false)
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
			// If target goes out of range or dies
			if (CheckTarget())
			{
				state = TowerState::SEARCHING;
				break;
			}
			// Create projectile, set rotation
			else if (firingTimer > GetCooldown())
			{
				firingTimer = 0;
			}
			TargetRotation();
		}
		break;
	}

}

bool TowerController::Upgrade(bool path, int pathNo)
{
	if (path)
	{
		if (upgrade == "UPGRADE2")
		{
			if (pathNo == 1)
			{
				upgrade = "PATH1UPGRADE1";
			}
			else
			{
				upgrade = "PATH2UPGRADE1";
			}
		}
	}
	else
	{
		if (upgrade == "INITIAL")
		{
			upgrade = "UPGRADE1";
		}
		else if (upgrade == "UPGRADE1")
		{
			upgrade == "UPGRADE2";
		}
		else if (upgrade == "PATH1UPGRADE1")
		{
			upgrade = "PATH1UPGRADE2";
		}
		else
		{
			upgrade = "PATH2UPGRADE2";
		}
	}

	return true;
}

TowerData* TowerController::GetData()
{
	return &TowerDatabase::GetData(type.c_str())[upgrade];
}

int TowerController::GetCost()
{
	return GetData()->cost;
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

bool TowerController::SearchForTarget()
{
	/*
	vector<Entity*> entityList;
	vector<Entity*> targetsInRange;
	
	if (fireMode == FireMode::FIRST)
	{
		for (int i = 0; i < entityList.size(); ++i)
		{
			if ((entityList[i]->transform->GetPosition() - this->owner->transform->GetPosition()).LengthSquared() < range * range)
			{
				currentTarget = entityList[i];
				return true;
			}
		}
	}
	else if (fireMode == FireMode::LAST)
	{
		for (int i = entityList.size(); i > 0; --i)
		{
			if ((entityList[i]->transform->GetPosition() - this->owner->transform->GetPosition()).LengthSquared() < range * range)
			{
				currentTarget = entityList[i];
				return true;
			}
		}
	}
	else
	{
		Entity* mostHealth = entityList[0];
		for (int i = 0; i < entityList.size(); ++i)
		{
			if ((entityList[i]->transform->GetPosition() - this->owner->transform->GetPosition()).LengthSquared() < range * range)
			{
				if (entityList[i]->GetComponent<Enemy>().health > mostHealth->GetComponent<Enemey>().health)
				{
					mostHealth = entityList[i];
				}
			}
		}
		currentTarget = mostHealth;
		return true;
	}
	*/
	return false;
}

bool TowerController::CheckTarget()
{
	if (target == NULL)
		return true;
	/*
	else if (direction.LengthSquared() > range * range || currentTarget->GetComponent<Enemey>().dead)
	{
		return true;
	}
	*/
	return false;
}

#include "MyMath.h"
#include "../../Entity.h"

void TowerController::TargetRotation()
{
	direction = (target->transform->GetPosition() - this->owner->transform->GetPosition()).GetVector2();

	float rotation = Math::RadianToDegree(atan2(direction.y, direction.x));
	this->owner->transform->SetRotation(0, rotation, 0);
}

#include "../../../Entity/EntityFactory.h"

void TowerController::Fire()
{
	EntityFactory::GenerateProjectile(this->owner->transform->GetPosition().GetVector2(), GetProjectileType(), direction.Normalized());
}