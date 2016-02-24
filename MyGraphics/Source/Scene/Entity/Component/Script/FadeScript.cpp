#include "FadeScript.h"

#include "Vector2.h"
#include "../../Entity.h"

FadeScript::FadeScript() : rate(0), value(NULL)
{
}

FadeScript::~FadeScript()
{
}

void FadeScript::Init(Entity* entity)
{
	owner = entity;
}

#include "../../EntityFactory.h"

void FadeScript::Update(double dt)
{
	if (value)
	{
		*value += dt * rate;

		if (*value < 0)
			EntityFactory::Destroy(owner);
	}
}