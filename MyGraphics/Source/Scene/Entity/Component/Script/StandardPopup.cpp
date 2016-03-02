#include "StandardPopup.h"
#include "../../Entity.h"
#include "../GUI/Button.h"
#include "../TextRenderer2D.h"

StandardPopup::StandardPopup() : ok (NULL), cancel (NULL), close (NULL)
{
}

StandardPopup::~StandardPopup()
{
}

#include "../GUI/Popup.h"

void StandardPopup::PopUp(const char * text)
{
	this->text->SetText(text);
	popup->PopUp();
}

void StandardPopup::Close()
{
	popup->Close();
}

bool StandardPopup::IsOK()
{
	return ok->IsState();
}

bool StandardPopup::IsCancel()
{
	return cancel->IsState();
}

void StandardPopup::Init(Entity * ent)
{
	popup = ent->GetComponent<Popup>();
}

void StandardPopup::Update(double dt)
{
	if ((cancel && cancel->IsState()) || (close && close->IsState()))
		popup->Close();
}
