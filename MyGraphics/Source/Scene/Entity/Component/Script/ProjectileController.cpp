#include "ProjectileController.h"
#include "../../Component/Transform.h"
#include "../../Entity.h"
#include "../../../Projectile/ProjectileDatabase.h"
#include "../../../Entity/EntityFactory.h"
#include "../Physics/RigidBody.h"
#include "../../../Tower/TowerData.h"
#include <iostream>

Projectile::Projectile() :
pierce(0),
speed(0)
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

	rigid->ApplyForce(velocity.GetVector3() * speed);
}

void Projectile::Update(double dt)
{
	if (pierce < 0)
	{
		EntityFactory::Destroy(this->owner);
	}
}

#include "../../Collision.h"
#include "EnemyController.h"
#include "../../../../SoundEngine.h"

void Projectile::OnCollisionEnter(const Collision& col)
{
	if (!col.entity)
	{
		Audio.Play2D("bubble", 0.1f);
		EntityFactory::Destroy(owner);
	}
	else if (col.entity->GetName() == "Enemy" && pierce >= 0)
	{
		EnemyController *ec = col.entity->GetComponent<EnemyController>();
		if (ec->done)
			return;
		
		for (int i = 0; i < pierced.size(); ++i)
		{
			if (pierced[i] == ec->parentID)
				return;
		}

		pierced.push_back(col.entity->GetID());
		--pierce;
		//cout << col.entity->GetComponent<EnemyController>()->GetData().name << endl;
		switch (GetEffect())
		{
		case ProjectileData::NORMAL:
		{
			Audio.Play2D("bubble", 0.1f);
			col.entity->GetComponent<EnemyController>()->Pop();
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

int Projectile::GetPierce()
{
	//return GetData().pierce;
	return pierce;
}
