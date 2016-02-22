#include "ProjectileController.h"
#include "../../Component/Transform.h"
#include "../../Entity.h"
#include "../../../Projectile/ProjectileDatabase.h"
#include "../../../Entity/EntityFactory.h"
#include "../Physics/RigidBody.h"
#include "../../../Tower/TowerData.h"
#include <iostream>

Projectile::Projectile() :
distTravelled(0),
pierce(0),
speed(0),
maxDist(0)
{

}

Projectile::~Projectile()
{

}

void Projectile::Init(Entity* ent)
{
	this->owner = ent;
	rigid = ent->GetComponent<RigidBody>();
}

#include "Vector2.h"

void Projectile::LateInit(string type)
{
	this->type = type;
}

void Projectile::SetProperties(TowerData *towerData, Vector2 velocity, float rotation)
{
	owner->transform->SetRotation(0, 0, rotation);

	this->pierce = towerData->pierce;
	this->speed = towerData->speed;
	this->maxDist = towerData->distance;

	rigid->ApplyForce(velocity.GetVector3() * speed);
}

void Projectile::Update(double dt)
{
	if (pierce < 0 || distTravelled > maxDist * maxDist)
	{
		EntityFactory::Destroy(this->owner);
	}
	else
	{
		distTravelled += rigid->velocity.LengthSquared();
	}
}

#include "../../Collision.h"
#include "EnemyController.h"

void Projectile::OnCollisionEnter(const Collision& col)
{
	--pierce;

	switch (GetEffect())
	{
	case ProjectileData::NORMAL:
	{
		//col.entity->GetComponent<Enemy>()->pop
	}
	break;
	case ProjectileData::SLOW:
	{
		//col.entity->GetComponent<Enemy>()->slowdebuff(duration, slow amt);
	}
	break;
	case ProjectileData::STUN:
	{
		col.entity->GetComponent<EnemyController>()->Stun(0.5f);
	}
	break;
	}
}

void Projectile::SetType(const char * type)
{
	this->type = type;
}

ProjectileData& Projectile::GetData()
{
	return ProjectileDatabase::GetData(type.c_str());
}

int Projectile::GetEffect()
{
	return GetData().effect;
}

float Projectile::GetSpeed()
{
	//return GetData().speed;
	return speed;
}

float Projectile::GetDistance()
{
	//return GetData().distance;
	return maxDist;
}

int Projectile::GetPierce()
{
	//return GetData().pierce;
	return pierce;
}
