#include "Canvas.h"

CanvasUI::CanvasUI() : focus(NULL)
{
}

void CanvasUI::SetFocus(Button * focus)
{
	this->focus = focus;
}

Button * CanvasUI::GetFocus()
{
	return focus;
}

void CanvasUI::Init(Entity* ent)
{

}

void CanvasUI::Update(double dt)
{
	focus = NULL;
}