#include "Toggle.h"
#include "Button.h"
#include "../../Entity.h"

Toggle::Toggle() : toggle(NULL)
{
}

Toggle::~Toggle()
{
}

bool Toggle::IsToggled()
{
	if (toggle)
	{
		return *toggle;
	}

	return false;
}

void Toggle::SetToggle(bool* toggle)
{
	this->toggle = toggle;
}

void Toggle::Init(Entity * ent)
{
	button = ent->GetComponent<Button>();
}

void Toggle::Update(double dt)
{
	if (toggle && button->IsState())
		*toggle = !*toggle;
}
