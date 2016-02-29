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
	owner = ent;
	transform = ent->transform;

	graphic = ent->GetComponent<Graphic2D>();
	graphic->SetAlignCenter(false);
}

#include "../../../../InputHandler.h"
#include "Vector2.h"

void HoverText::Update(double dt)
{
	transform->Position() = offset + Input.GetCursorPos().GetVector3();
}

#include "../../../../FontManager.h"
#include "../../../../Font.h"

void HoverText::SetText(const char * text)
{
	this->text->GetComponent<TextRenderer2D>()->SetText(text);
	
	Vector3 size = FontManager::Instance().GetFont()->GetTextSize(text).GetVector3() * this->text->transform->GetSize();
	this->text->transform->SetPosition(0, size.y * 0.5f, 0);

	offset.x = -size.x;
	transform->Size() = size;
}
