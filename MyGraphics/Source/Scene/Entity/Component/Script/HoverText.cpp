#include "../../Entity.h"
#include "HoverText.h"

#include "../Graphic2D.h"
#include "../TextRenderer2D.h"
#include "../Transform.h"

HoverText::HoverText()
{
}

HoverText::~HoverText()
{
}

void HoverText::Init(Entity * ent)
{
	transform = ent->transform;

	graphic = ent->GetComponent<Graphic2D>();
	graphic->SetAlignCenter(false);

	SetActive(false);
}

#include "../../../../InputHandler.h"
#include "Vector2.h"

void HoverText::Update(double dt)
{
	transform->Position() = Input.GetCursorPos().GetVector3();
}

void HoverText::SetText(const char * text)
{
	this->text->SetText(text);
}
