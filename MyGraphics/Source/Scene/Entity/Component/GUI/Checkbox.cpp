#include "Toggle.h"
#include "Checkbox.h"
#include "../../Entity.h"

Checkbox::Checkbox()
{
}

Checkbox::~Checkbox()
{
}

void Checkbox::Init(Entity * ent)
{
	toggle = ent->GetComponent<Toggle>();
}

void Checkbox::Update(double dt)
{
	check->SetActive(toggle->IsToggled());
}
