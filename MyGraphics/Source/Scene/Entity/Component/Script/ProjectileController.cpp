#include "ProjectileController.h"
#include "../../Component/Transform.h"
#include "../../Entity.h"
#include "../../../Projectile/ProjectileDatabase.h"
#include "../../../Entity/EntityFactory.h"
#include "../Physics/RigidBody.h"
#include "../../../Tower/TowerData.h"
#include <iostream>

Projectile::Projectile() :
pierceCount(0)
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
#include "../Graphic2D.h"
#include "../../../../Assets.h"

void Projectile::LateInit(string name)
{
	this->name = name;
}


void Projectile::SetProperties(TowerData *towerData, Vector2 velocity, float rotation)
{
	this->towerData = towerData;

	pierceCount = towerData->pierce;

	rigid->ApplyForce(velocity.GetVector3() * towerData->speed);

	owner->transform->SetRotation(0, 0, rotation);
}

void Projectile::Update(double dt)
{
	if (pierceCount < 0)
	{
		GenerateParticle();
		EntityFactory::Destroy(this->owner);
	}
}

#include "../../Collision.h"
#include "EnemyController.h"
#include "../../../../SoundEngine.h"
#include "ScaleScript.h"

void Projectile::OnCollisionEnter(const Collision& col)
{
	if (!col.entity)
	{
		PlaySound();
		GenerateParticle();

		EntityFactory::Destroy(owner);
	}
	else if (col.entity->GetName() == "Enemy" && pierceCount >= 0)
	{
		EnemyController *ec = col.entity->GetComponent<EnemyController>();
		if (ec->done)
			return;

		--pierceCount;

		for (int i = 0; i < pierced.size(); ++i)
		{
			if (pierced[i] == ec->parentID || pierced[i] == ec->GetOwnerID())
				return;
		}

		pierced.push_back(col.entity->GetID());
		
		switch (towerData->projectileEffect)
		{
		case 0:
		{
			PlaySound();
		}
		break;
		case 1:
		{
			col.entity->GetComponent<EnemyController>()->Slow(towerData->projectileValue, towerData->effectDuration);
		}
		break;
		case 2:
		{
			col.entity->GetComponent<EnemyController>()->Stun(towerData->effectDuration);
		}
		break;
		case 3:
		{
			PlaySound();
		}
		break;
		}

		col.entity->GetComponent<EnemyController>()->Pop((int)towerData->pierce + 1);
	}
}

void Projectile::SetName(const char * name)
{
	this->name = name;
}

void Projectile::PlaySound()
{
	if (name == "Bubble")
	{
		Audio.Play2D("bubble", 1);
	}
	else if (name == "Water")
	{
		Audio.Play2D(Audio.GetSoundPack("splash"), 0.33f);
	}
}

#include "FadeScript.h"
#include "../SpriteRenderer.h"

void Projectile::GenerateParticle()
{
	if (name == "Bubble")
	{
		Entity* particle = EntityFactory::Generate(owner->parent,
			EntityFactory::CreateGraphic(owner->transform->GetPosition().GetVector2(), owner->transform->GetSize().GetVector2() * 1.2f, Resource.GetTexture("Burst"), Vector4(1, 1, 1)));

		particle->GetComponent<Graphic2D>()->color.w = 0.6f;
		particle->GetComponent<Graphic2D>()->SetLayer(2);

		particle->AddComponent<ScaleScript>()->rate = 32;

		particle->AddComponent<FadeScript>()->rate = -3;
		particle->GetComponent<FadeScript>()->value = &particle->GetComponent<Graphic2D>()->color.w;

	}
	else if (name == "Water")
	{
		Entity* particle = EntityFactory::GenerateParticle(owner->transform->GetPosition().GetVector2(), owner->transform->GetSize().GetVector2() * 0.65f, "Splash", "Splash", 0.6f);

		particle->AddComponent<FadeScript>()->rate = -2;
		particle->GetComponent<FadeScript>()->value = &particle->GetComponent<SpriteRenderer>()->color.w;
	}
}

//ProjectileData& Projectile::GetData()
//{
//	return ProjectileDatabase::GetData(type.c_str());
//}

//int Projectile::GetEffect()
//{
//	//return GetData().effect;
//	towerData->projectileEffect;
//}
//
//float Projectile::GetSpeed()
//{
//	//return GetData().speed;
//	return towerData->speed;
//}
//
//int Projectile::GetPierce()
//{
//	//return GetData().pierce;
//	return towerData->pierce;
//}
