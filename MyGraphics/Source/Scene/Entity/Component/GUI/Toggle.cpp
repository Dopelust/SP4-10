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
	return toggle;
}

void Toggle::SetToggle(bool toggle)
{
	this->toggle = toggle;
}

void Toggle::Init(Entity * ent)
{
	button = ent->GetComponent<Button>();
}

void Toggle::Update(double dt)
{
	if (button->IsState())
		toggle = !toggle;
}
