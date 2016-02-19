#include "Button.h"
#include "../../Entity.h"
#include "../Transform.h"
#include "../Graphic2D.h"

#include "../../../../InputHandler.h"
#include "Vector2.h"

Vector3 Button::GetMaxCoord()
{
	return transform->GetPosition() + transform->GetSize() * 0.5f;
}

Vector3 Button::GetMinCoord()
{
	return transform->GetPosition() - transform->GetSize() * 0.5f;
}

Vector4 Button::GetHoverColor()
{
	Vector4 color = this->color;

	color.x *= 1.25f;
	color.y *= 1.25f;
	color.z *= 1.25f;

	return color;
}

Vector4 Button::GetClickColor()
{
	Vector4 color = this->color;

	color.x *= 0.75f;
	color.y *= 0.75f;
	color.z *= 0.75f;

	return color;
}

#include "../../../Scene.h"
#include "Canvas.h"

bool Button::IsHover()
{
	Vector2& cursor = Input.GetCursorPos();

	Vector3& min = GetMinCoord();
	Vector3& max = GetMaxCoord();
	
	if (cursor.x > min.x && cursor.x < max.x && cursor.y > min.y && cursor.y < max.y)
	{
		Canvas.SetFocus(this);
		return true;
	}

	return false;
}

Button::Button() : state(ButtonState::STATE_NULL)
{
}

bool Button::IsState(ButtonState state)
{
	return this->state == state;
}

void Button::Init(Entity * ent)
{
	transform = ent->GetComponent<Transform>();
	graphic = ent->GetComponent<Graphic2D>();
	color = graphic->GetColor();
}

#include "Utility.h"
void Button::Update(double dt)
{
	UpdateState();
}

#include "../../../../SoundEngine.h"

void Button::UpdateState()
{
	switch (state)
	{
	case STATE_NULL:

		graphic->GetColor() = color;

		if (IsHover() && !Input.IsMouseHeld(0))
			state = STATE_HOVER;

		break;
	case STATE_HOVER:

		graphic->GetColor() = GetHoverColor();

		if (!IsHover())
			state = STATE_NULL;
		if (Input.IsMousePress(0))
		{
			Audio.Play2D("click");
			state = STATE_CLICK;
		}

		break;
	case STATE_PRIMED:

		graphic->GetColor() = color;

		if (IsHover())
			state = STATE_CLICK;
		else if (Input.IsMouseRelease(0))
			state = STATE_NULL;

		break;
	case STATE_CLICK:

		graphic->GetColor() = GetClickColor();

		if (IsHover())
		{
			if (Input.IsMouseRelease(0))
				state = STATE_RELEASE;
		}
		else
			state = STATE_PRIMED;

		break;
	case STATE_RELEASE:

		graphic->GetColor() = color;
		state = STATE_NULL;

		break;
	}
}
