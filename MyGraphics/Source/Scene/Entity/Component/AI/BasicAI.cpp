#include "BasicAI.h"
#include "../../Entity.h"
#include "../Transform.h"
#include "../Physics/RigidBody2D.h"

BasicAI::BasicAI() : target(NULL), transform(NULL), rigid(NULL)
{
}

BasicAI::~BasicAI()
{
}

void BasicAI::Init(Entity * ent)
{
	transform = ent->transform;
	rigid = ent->GetComponent<RigidBody2D>();
}

#include "Vector2.h"

void BasicAI::Update(double dt)
{
	if (target)
	{
		Vector3 direction = (target->transform->GetPosition() - transform->GetPosition()).Normalized();
		transform->Rotation().z = Math::RadianToDegree(atan2(direction.y, direction.x));
	}
}
