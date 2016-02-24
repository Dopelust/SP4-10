#include "ScaleScript.h"

#include "Vector2.h"
#include "../Transform.h"
#include "../../Entity.h"

ScaleScript::ScaleScript() : rate(0)
{
}

ScaleScript::~ScaleScript()
{
}

void ScaleScript::Init(Entity* entity)
{
	owner = entity;
}

void ScaleScript::Update(double dt)
{
	float resolution = owner->transform->Size().x / owner->transform->Size().y;

	owner->transform->Size().x += dt * rate;
	owner->transform->Size().y += dt * rate * resolution;
}