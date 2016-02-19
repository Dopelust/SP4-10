#include "Component.h"

Component::Component() : active(true)
{
}

Component::~Component()
{
}

void Component::Init(Entity* entity)
{
}

void Component::Update(double dt)
{
}

void Component::Draw(const Mtx44& parent)
{
}

void Component::OnCollisionEnter(const Collision& col)
{
}

bool Component::IsActive()
{
	return active;
}
void Component::SetActive(bool active)
{
	this->active = active;
}