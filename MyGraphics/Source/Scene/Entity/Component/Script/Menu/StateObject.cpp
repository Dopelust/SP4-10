#include "StateObject.h"

StateObject::StateObject() : rate(1)
{
}

StateObject::~StateObject()
{
}

#include "../../../Entity.h"
#include "../../Transform.h"

#include "../../../../Scene.h"

void StateObject::Init(Entity * ent)
{
	owner = ent;
	transform = ent->transform;
}

void StateObject::Update(double dt)
{
	transform->Position() += (target.GetVector3() - transform->Position()) * rate * dt;
}
void StateObject::Appear()
{
	target.Set(0, 0);
}

void StateObject::Disappear(bool left)
{
	if (left)
		target.Set(-Scene::scene->GetResolutionX(Scene::scene->canvas), 0);
	else
		target.Set(Scene::scene->GetResolutionX(Scene::scene->canvas), 0);
}

bool StateObject::ReachedTarget()
{
	return transform->GetPosition().DistSquared(target.GetVector3()) < 1;
}
