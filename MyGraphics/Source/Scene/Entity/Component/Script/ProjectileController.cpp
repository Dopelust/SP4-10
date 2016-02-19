#include "ProjectileController.h"
#include "../../Component/Transform.h"
#include "../../Entity.h"
#include "../../../Projectile/ProjectileDatabase.h"
#include "../../../Entity/EntityFactory.h"
#include "../Physics/RigidBody.h"

Projectile::Projectile() :
distTravelled(0),
pierce(0)
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

void Projectile::Update(double dt)
{
	if (pierce < 0 || distTravelled > GetDistance()*GetDistance())
	{
		EntityFactory::Destroy(this->owner);
	}
	else
	{
		distTravelled += rigid->velocity.LengthSquared();
	}
}

#include "../../Collision.h"

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
		//col.entity->GetComponent<Enemy>()->stun(duration);
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
	return GetData().speed;
}

float Projectile::GetDistance()
{
	return GetData().distance;
}

float Projectile::GetPierce()
{
	return GetData().pierce;
}
