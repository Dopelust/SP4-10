#include "Canvas.h"
#include "Popup.h"

CanvasUI::CanvasUI() : focus(NULL), popup(NULL)
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

void CanvasUI::SetPopup(Popup* popup)
{
	if (this->popup && this->popup != popup)
		this->popup->Close();

	this->popup = popup;
}

void CanvasUI::ClosePopup()
{
	this->popup = NULL;
}

Popup * CanvasUI::GetPopup()
{
	return popup;
}

void CanvasUI::Init(Entity* ent)
{

}

void CanvasUI::Update(double dt)
{
	focus = NULL;
}