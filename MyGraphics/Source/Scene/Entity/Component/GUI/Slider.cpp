#include "Slider.h"
#include "Button.h"
#include "../../Entity.h"
#include "../Transform.h"
#include "../../../../InputHandler.h"
#include "Vector2.h"
#include "../TextRenderer2D.h"

Slider::Slider() : transform(NULL), button(NULL), text(NULL), click(false), type(SLIDER_HORIZONTAL), valueType(SLIDER_INTEGER), min(0), max(1), value(0.5f), prev(0.5f)
{
}

Slider::~Slider()
{
}

void Slider::Init(Entity * ent)
{
	button = ent->GetComponent<Button>();
	transform = ent->transform;
}

void Slider::Update(double dt)
{
	prev = value;

	if (click)
	{
		if (Input.IsMouseRelease(0))
			click = false;
		else
			SetPosition(Input.GetCursorPos());
	}
	else
	{
		if (button->IsState(Button::STATE_CLICK))
		{
			click = true;
		}
		else if (guide->IsState(Button::STATE_CLICK))
		{
			click = true;
			SetPosition(Input.GetCursorPos());
		}
		else
			click = false;
	}
}

void Slider::SetValue(float value)
{
	value = Math::Clamp(value, min, max);

	this->value = value;

	Vector2& min = guide->GetMinCoord().GetVector2();
	Vector2& max = guide->GetMaxCoord().GetVector2();

	SetPosition(min + (max - min) * (value - this->min) / (this->max - this->min));
}

bool Slider::ValueChanged()
{
	return prev != value;
}

float Slider::GetValue()
{
	switch (valueType)
	{
	case SLIDER_FLOAT:
		return value;
		break;
	case SLIDER_INTEGER:
		return (int)(value + 0.5f);
		break;
	}
}

void Slider::SetMin(float min)
{
	this->min = min;
}

void Slider::SetMax(float max)
{
	this->max = max;
}

#include "Utility.h"

void Slider::SetText(TextRenderer2D * text)
{
	this->text = text;
	text->SetText(ToString(value).c_str());
}

void Slider::SetPosition(const Vector2 & position)
{
	Vector2& parent = guide->transform->GetPosition().GetVector2();
	Vector3& min = guide->GetMinCoord();
	Vector3& max = guide->GetMaxCoord();

	switch (type)
	{
	case SLIDER_HORIZONTAL:
		transform->Position().x = Math::Clamp(position.x, min.x, max.x) - parent.x;
		value = this->min + (transform->Position().x / (max.x - min.x) + 0.5f) * (this->max - this->min);

		fill->Size().x = transform->Position().x - min.x + parent.x;
		fill->Position().x = fill->Size().x * 0.5f - (max.x - min.x) * 0.5f;

		break;
	case SLIDER_VERTICAL:
		transform->Position().y = Math::Clamp(position.y, min.y, max.y) - parent.y;
		value = this->min + (transform->Position().y / (max.y - min.y) + 0.5f) * (this->max - this->min);

		fill->Size().y = transform->Position().y - min.y + parent.y;
		fill->Position().y = fill->Size().y * 0.5f - (max.y - min.y) * 0.5f;

		break;
	}

	button->UpdateState();

	if (text)
		text->SetText(ToString(GetValue()).c_str());
}
