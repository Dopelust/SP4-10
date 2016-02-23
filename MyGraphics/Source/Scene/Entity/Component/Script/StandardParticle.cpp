#include "StandardParticle.h"

#include "Vector2.h"
#include "../SpriteAnimator.h"
#include "../../Entity.h"

StandardParticle::StandardParticle()
{
}

StandardParticle::~StandardParticle()
{
}

void StandardParticle::Init(Entity* entity)
{
	owner = entity;
	anim = entity->GetComponent<SpriteAnimator>();
}

#include "../../EntityFactory.h"

void StandardParticle::Update(double dt)
{
	if (anim->IsEnded())
		EntityFactory::Destroy(owner);

}