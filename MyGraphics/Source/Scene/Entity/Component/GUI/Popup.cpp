#include "../../../Scene.h"
#include "Canvas.h"
#include "Popup.h"
#include "../../Entity.h"
#include "../../../../InputHandler.h"

Popup::Popup()
{
}

void Popup::PopUp()
{
	owner->SetActive(true);
	Input.Halt();
}

void Popup::Close()
{
	Canvas.ClosePopup();
	owner->SetActive(false);
	Input.Resume();
}

Popup::~Popup()
{
}

const vector<Button*>& Popup::GetButtonList()
{
	return button;
}

void Popup::AddButton(Button * button)
{
	this->button.push_back(button);
}

void Popup::Init(Entity * ent)
{
	owner = ent;
}

void Popup::Update(double dt)
{
	Canvas.SetPopup(this);
}
