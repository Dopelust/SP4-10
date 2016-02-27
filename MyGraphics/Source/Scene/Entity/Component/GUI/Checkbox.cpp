#include "Toggle.h"
#include "Checkbox.h"
#include "../../Entity.h"

Checkbox::Checkbox()
{
}

Checkbox::~Checkbox()
{
}

bool Checkbox::IsCheck()
{
	return toggle->IsToggled();
}

void Checkbox::SetCheck(bool check)
{
	toggle->SetToggle(check);
}

void Checkbox::Init(Entity * ent)
{
	toggle = ent->GetComponent<Toggle>();
}

void Checkbox::Update(double dt)
{
	check->SetActive(toggle->IsToggled());
}
