#include "SimplePopup.h"
#include "../../Entity.h"
#include "../GUI/Button.h"
#include "../TextRenderer2D.h"

SimplePopup::SimplePopup() : ok (NULL)
{
}

SimplePopup::~SimplePopup()
{
}

#include "../GUI/Popup.h"

void SimplePopup::PopUp(const char * text)
{
	this->text->SetText(text);
	popup->PopUp();
}

void SimplePopup::Close()
{
	popup->Close();
}

bool SimplePopup::IsOK()
{
	return ok->IsState();
}

void SimplePopup::Init(Entity * ent)
{
	popup = ent->GetComponent<Popup>();
}

void SimplePopup::Update(double dt)
{
}
