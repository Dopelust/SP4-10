#include "MenuObject.h"

MenuObject::MenuObject() : rate(1), appear(true)
{
}

MenuObject::~MenuObject()
{
}

#include "../../../Entity.h"
#include "../../Transform.h"

void MenuObject::Init(Entity * ent)
{
	transform = ent->transform;
}

void MenuObject::Update(double dt)
{
	if (appear)
	{
		transform->Position() += (target.GetVector3() - transform->Position()) * rate * dt;
	}
	else
	{
		transform->Position() += (position.GetVector3() - transform->Position()) * rate * dt;
	}
}

void MenuObject::Appear()
{
	appear = true;
}

void MenuObject::Disappear()
{
	appear = false;
}
